#include "setup.c"

#ifndef TOOLS_H
#define TOOLS_H 

void printr(dimensions local, dimensions base);

void cover_traces(dimensions now, char write, dimensions last, dimensions start);

void show_around(dimensions selected, dimensions base);

dimensions limite(dimensions in);

dimensions nvg(dimensions start, dimensions base);

dimensions frist_select(dimensions base);
 #endif //TOOLS_H