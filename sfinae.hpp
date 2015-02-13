#ifndef SFINAE_INCLUDED_
#define SFINAE_INCLUDED_

namespace tmpl
{

namespace sfinae
{

typedef struct { char _; } yes;
typedef struct { yes _[2]; } no;

} // namespace sfinae

} // namespace tmpl

#endif
