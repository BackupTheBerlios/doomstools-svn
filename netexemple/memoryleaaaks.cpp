#include "libnettool.h"
#include <stdio.h>
#include <string.h>

// define tag communication:
enum
{
  WELCOME = 0,
  HELLOWORLD,
  EXIT
};

#define MAXSELECT ((unsigned int)-1)
#define PORT (4203)
#define MAX_PLAYERS (42)

t_client	**players = NULL;
int		nb_player = 0;

void	process_drop(t_client *c, const t_trame *T,
		     void *data)
{
  exit(1);
}

void	process_newclient(t_client *c, const t_trame *t,
			  void *data)
{
  printf("process new %d\n", (int)c);fflush(stdout);
  if (!t)
    {printf("very begininng\n");fflush(stdout);}
  else if (is_valid_trame((t_trame*)t, WELCOME))
    {
      if (!nb_player)
      {
	players = (t_client**)malloc(sizeof(*players) * MAX_PLAYERS);
      	for (int i = 0; i < MAX_PLAYERS; i++)
        	players[i] = NULL;
	}
      if (nb_player >= MAX_PLAYERS)
	  nb_player = 0;

      if (players[nb_player])
      {
	  printf("CLOSE ONE %d\n", (int)players[nb_player]);
	  close_client_connection(players[nb_player]);
	  printf("CLOSED %d\n", players[nb_player]->state);fflush(stdout);
      }

      // change status of client
      authorize_client(c);

      // collect information
      players[nb_player] = c; // for sending message later
      set_data_client(c, (void*)&players[nb_player]); // for receving msg

      nb_player++;
      printf("client %d say welcome\n", c);fflush(stdout);
    }
  else
    printf("ERROR: got %d\n", t->tag);
}

void	process_deadclient(t_client *c, const t_trame *t,
			   void *data)
{
  printf("process dead %d\n", (int)c);fflush(stdout);
}

void	process_clients(t_client *c, const t_trame *t,
			void *data)
{
  printf("process clients %d\n", (int)c);fflush(stdout);
  if (is_valid_trame((t_trame*)t, HELLOWORLD))
    {printf("one client say HELLOWORLD\n");fflush(stdout);}
  else if (is_valid_trame((t_trame*)t, EXIT))
    {printf("one client say quit!\n");fflush(stdout);}
  else
    {printf("ERROR: got %d\n", t->tag);fflush(stdout);}
}

int	main(int ac, char **av)
{
  // doit absolument etre apelle avant d'autres appels a la lib
  init_nettool();
  if (ac > 1) // server mode
    {

      // set handlers
      assign_newclient(process_newclient, NULL);
      assign_deadclient(process_deadclient, NULL);
      assign_clients(process_clients, NULL);

      // open listen connection
      if (init_server_connection(PORT))
	return (1);

      // check messages
      while (1)
	check_select(MAXSELECT);

      // close connection
      close_server_connection();
      close_connection();
    }
  else // client mode
    {
      // connect to server
      if (init_connection("localhost", PORT))
	return (1);

      assign_deadclient(process_drop, NULL);

      printf("step 1\n");fflush(stdout); fflush(stdout);
      // stock messages to send
      stock_remote_msg(WELCOME, strlen("tata"), (void*)"tata");
      printf("step 2\n");fflush(stdout); fflush(stdout);
      stock_remote_msg(HELLOWORLD, 0, NULL);
      printf("step 3\n");fflush(stdout); fflush(stdout);
      stock_remote_msg(HELLOWORLD, 0, NULL);
      printf("step 4\n");fflush(stdout); fflush(stdout);
      stock_remote_msg(HELLOWORLD, 0, NULL);
      printf("step 5\n");fflush(stdout); fflush(stdout);
      stock_remote_msg(HELLOWORLD, 0, NULL);
      printf("step 5\n");fflush(stdout); fflush(stdout);

      printf("step 7\n");fflush(stdout); fflush(stdout);
      // send messages
      while (1)
	check_select(MAXSELECT);

      printf("step 8\n");fflush(stdout); fflush(stdout);
      // close connection
      close_connection();
      printf("step 9\n");fflush(stdout); fflush(stdout);
    }
  // free memory, and close connections
  nettool_quit();
  if (players)
    free(players);
  return (0);
}
