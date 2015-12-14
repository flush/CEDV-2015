#ifndef _CONST_H
#define _CONST_H
enum QueryFlags
{
  SHIP = 1 << 0,
  BOARD_POS = 1 << 1,
  PLANE_DRAG_DROP = 1 << 2,
  BOARD_BOX = 1 << 3,
  SHOOT_BOX = 1 << 4,
  USED_SHOOT_BOX = 1 << 5,
  BACKGROUND = 1 << 6
};
#endif
