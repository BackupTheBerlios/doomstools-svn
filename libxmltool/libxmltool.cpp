// Copyright (C) 2004 Doomsday <doomsday@mailclub.net>

// This file is part of libxmltool.

// libxmltool is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.

// libxmltool is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser Public License for more details.

// You should have received a copy of the GNU Lesser Public License
// along with ligxmltool; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#include "libxmltool.h"

#define XML_MAX_LEVELS (20)

typedef struct		s_xml
{
  int			depth;
  TiXmlElement		*elm[XML_MAX_LEVELS];
  char			*last[XML_MAX_LEVELS];
  bool			last_is_next;
}			t_xml;

t_xml			*gl_xml;
TiXmlDocument		doc;

int		xml_init(char *db)
{
  static int	first = 1;

  if (first)
    {
      first = 0;
      gl_xml = (t_xml*)xmalloc(sizeof(t_xml));
    }
  if (doc.LoadFile(db) == false)
    {
      fprintf(fd_log, "error loading BDD (%s)..\n", db);
      return (1);
    } 
  gl_xml->depth = 0;
  gl_xml->elm[gl_xml->depth] = doc.FirstChildElement("root");
  if (!gl_xml->elm[gl_xml->depth])
    {
      fprintf(fd_log, "XML avec les pieds\n");
      return (1);
    }
  gl_xml->last[gl_xml->depth] = 0;
  gl_xml->depth++;
  gl_xml->last_is_next = 0;
  return (0);
}

int		xml_getint(char *str)
{
  int		buf;

  if (gl_xml->elm[gl_xml->depth - 1])
    {
      if ((gl_xml->elm[gl_xml->depth - 1]->QueryIntAttribute((const char*)str, &buf))
	  == TIXML_SUCCESS)
	return (buf);
    }
  return (0);
}

double		xml_getfloat(char *str)
{
  double	buf;

  if (gl_xml->elm[gl_xml->depth - 1])
    {
      if ((gl_xml->elm[gl_xml->depth - 1]->QueryDoubleAttribute((const char*)str, &buf))
	  == TIXML_SUCCESS)
	return (buf);
    }
  return (0);
}

char		*xml_getstr(char *str)
{
  char		*buf;

  if (gl_xml->elm[gl_xml->depth - 1])
    {
      if ((buf = (char*)gl_xml->elm[gl_xml->depth - 1]->Attribute((const char*)str)))
	return (xstrdup((char*)buf));
    }
  return (0);
}

int		xml_next(char *str)
{
  if (gl_xml->last[gl_xml->depth - 1] &&
      !strcmp(gl_xml->last[gl_xml->depth - 1], str)) 
    { // next
      gl_xml->elm[gl_xml->depth] =  gl_xml->elm[gl_xml->depth]->NextSiblingElement(str);
      if (!gl_xml->elm[gl_xml->depth])
	return (0);
    }
  else // first
    {
      gl_xml->elm[gl_xml->depth] =  gl_xml->elm[gl_xml->depth - 1]->FirstChildElement(str);
      if (!gl_xml->elm[gl_xml->depth])
	return (0);
      if (gl_xml->last[gl_xml->depth - 1])
	xfree(gl_xml->last[gl_xml->depth - 1]);
      gl_xml->last[gl_xml->depth - 1] = xstrdup(str);
    }
  gl_xml->last[gl_xml->depth] = 0;
  gl_xml->depth++;
  return (1);
}

void		xml_out()
{
  gl_xml->depth--;
}
