#ifdef WIN32
#include <windows.h>
#endif

#include "doomstools/libnettool.h"

// define tag communication:
enum
{
  WELCOME = 0,
  HELLOWORLD,
  EXIT
};

#define MAXSELECT ((unsigned int)-1)
#define PORT (4203)
#define MAX_PLAYERS (4)

typedef struct	s_player
{
  char		name[512];
  t_client	*c;
}		t_player;

int		gl_quit = 0;
t_player	players[MAX_PLAYERS];
int		nb_player = 0;

void	process_newclient(t_client *c, const t_trame *t,
			  void *data)
{
  printf("process new\n");
  if (!t)
    printf("very begininng\n");
  else if (is_valid_trame((t_trame*)t, WELCOME))
    {
      if (nb_player >= MAX_PLAYERS)
	{
	  gl_quit = 1;
	  return;
	}

      // change status of client
      authorize_client(c);

      // collect information
      strncpy(players[nb_player].name, t->msg, t->len);
      players[nb_player].name[t->len + 1] = 0;
      players[nb_player].c = c; // for sending message later
      set_data_client(c, (void*)&players[nb_player]); // for receving msg

      printf("client %s say welcome\n", players[nb_player].name);

      nb_player++;
    }
  else
    printf("ERROR: got %d\n", t->tag);
}

void	process_deadclient(t_client *c, const t_trame *t,
			   void *data)
{
  int	i;

  printf("process dead\n");
  for (i = 0; i < MAX_PLAYERS; i++)
    if (players[i].c == c)
      printf("%s is done..\n", players[i].name);
}

void	process_clients(t_client *c, const t_trame *t,
			void *data)
{
  t_player	*p;

  p = (t_player*)c->data;
  printf("process clients\n");
  if (is_valid_trame((t_trame*)t, HELLOWORLD))
    {
      printf("%s: HELLOWORLD\n", p->name);
    }
  else if (is_valid_trame((t_trame*)t, EXIT))
    {
      printf("client %s say to me that he quit!\n", p->name);
    }
  else
    printf("ERROR: got %d\n", t->tag);
}

#ifdef WIN32
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
#else // !WIN32
int	main(int ac, char **av)
#endif // WIN32
{
  int	i = 0;

  init_nettool();
#ifdef WIN32
  if (nCmdShow > 1) // server mode
#else // !WIN32
  if (ac > 1)
#endif // WIN32
    {
      // set handlers
      assign_newclient(process_newclient, NULL);
      assign_deadclient(process_deadclient, NULL);
      assign_clients(process_clients, NULL);

      // open listen connection
      if (init_server_connection(PORT))
	return (1);

      // check messages
      while (!gl_quit)
	check_select(MAXSELECT);

      // close connection
      close_server_connection();
      close_connection();

      // using vars
      for (i = 0; i < MAX_PLAYERS; i++)
	printf("this guy was here : %s (with an old addr: %d)\n",
	       players[i].name, (int)players[i].c);
    }
  else // client mode
    {
      // connect to server
      if (init_connection("localhost", PORT))
	return (1);

      // stock messages to send
      stock_remote_msg(WELCOME, strlen("tata"), (void*)"tata");
      stock_remote_msg(HELLOWORLD, 0, NULL);
      stock_remote_msg(HELLOWORLD, 0, NULL);
      stock_remote_msg(HELLOWORLD, 0, NULL);
      stock_remote_msg(HELLOWORLD, 0, NULL);
      stock_remote_msg(EXIT, 0, NULL);

      // send messages
      while (check_select(MAXSELECT))
	;

      // close connection
      close_connection();
    }
  // free memory, and close connections
  nettool_quit();
  return (0);
}
