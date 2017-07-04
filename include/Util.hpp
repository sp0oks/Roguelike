#ifndef UTIL_HPP
#define UTIL_HPP

enum class TILE {
  WALL_SINGLE,
	WALL_TOP_END,
	WALL_SIDE_RIGHT_END,
	WALL_BOTTOM_LEFT,
	WALL_BOTTOM_END,
	WALL_SIDE,
	WALL_TOP_LEFT,
	WALL_SIDE_LEFT_T,
	WALL_SIDE_LEFT_END,
	WALL_BOTTOM_RIGHT,
	WALL_TOP,
	WALL_BOTTOM_T,
	WALL_TOP_RIGHT,
	WALL_SIDE_RIGHT_T,
	WALL_TOP_T,
	WALL_INTERSECTION,
	FLOOR,
	FLOOR_ALT,
	EMPTY,
	COUNT
};

enum class GAME_STATE {
  MAIN_MENU,
  GAME_RUN,
  GAME_END,
  COUNT
};

enum class ANIMATION_STATE {
	WALK_UP,
	WALK_DOWN,
	WALK_LEFT,
  WALK_RIGHT,
	IDLE_UP,
	IDLE_DOWN,
	IDLE_LEFT,
  IDLE_RIGHT,
	COUNT
};

enum class HERO_CLASS{
  WARRIOR,
  MAGE,
  ARCHER,
  THIEF,
  PALADIN,
  VALKYRIE,
  COUNT
};

// Player traits.
enum class PLAYER_TRAIT {
	ATTACK,
	DEFENSE,
	STRENGTH,
	DEXTERITY,
	STAMINA,
	COUNT
};

#endif
