#include <string>
#include <unordered_map>
#include "LuaStringToEnum.hpp"

using namespace Xrysnow;

static const int HASH_OFFSET = -2; //hash值在TString结构中的偏移，相对的是const char*指针的偏移

static std::unordered_map<std::string, GameObjectProperty> prop_map = {
	// object
	{ "status",	GameObjectProperty::STATUS	},
	{ "class",	GameObjectProperty::CLASS	},
	// user
	{ "timer",	GameObjectProperty::TIMER	},
	// position
	{ "x",		GameObjectProperty::X		},
	{ "y",		GameObjectProperty::Y		},
	{ "dx",		GameObjectProperty::DX		},
	{ "dy",		GameObjectProperty::DY		},
	// movement
	{ "ax",		GameObjectProperty::AX		},
	{ "ay",		GameObjectProperty::AY		},
	{ "ag",		GameObjectProperty::AG		},
	{ "vx",		GameObjectProperty::VX		},
	{ "vy",		GameObjectProperty::VY		},
	{ "maxv",	GameObjectProperty::MAXV	},
	{ "maxvx",	GameObjectProperty::MAXVX	},
	{ "maxvy",	GameObjectProperty::MAXVY	},
	// render
	{ "img",	GameObjectProperty::IMG		},
	{ "ani",	GameObjectProperty::ANI		},
	{ "rot",	GameObjectProperty::ROT		},
	{ "omiga",	GameObjectProperty::OMEGA	},
	{ "layer",	GameObjectProperty::LAYER	},
	{ "hide",	GameObjectProperty::HIDE	},
	{ "navi",	GameObjectProperty::NAVI	},
	{ "hscale",	GameObjectProperty::HSCALE	},
	{ "vscale",	GameObjectProperty::VSCALE	},
	{ "_blend",	GameObjectProperty::_BLEND	},
	{ "_color",	GameObjectProperty::_COLOR	},
	{ "_a",		GameObjectProperty::_A		},
	{ "_r",		GameObjectProperty::_R		},
	{ "_g",		GameObjectProperty::_G		},
	{ "_b",		GameObjectProperty::_B		},
	// collision
	{ "bound",		GameObjectProperty::BOUND	},
	{ "colli",		GameObjectProperty::COLLI	},
	{ "group",		GameObjectProperty::GROUP	},
	{ "a",			GameObjectProperty::A		},
	{ "b",			GameObjectProperty::B		},
	{ "rect",		GameObjectProperty::RECT	},
	{ "collider",	GameObjectProperty::COLLIDER	},
	// ex+
	{ "_angle",		GameObjectProperty::VANGLE				},
	{ "_speed",		GameObjectProperty::VSPEED				},
	{ "pause",		GameObjectProperty::PAUSE				},
	{ "nopause",	GameObjectProperty::IGNORESUPERPAUSE	},
	{ "rmove",		GameObjectProperty::RESOLVEMOVE			},
	{ "world",		GameObjectProperty::WORLD				},
};
static std::unordered_map<uint32_t, GameObjectProperty> prop_hash_map;
void init_prop_hash_map(lua_State* L) {
	prop_hash_map.clear();
	for (auto it : prop_map)
	{
		lua_pushstring(L, it.first.c_str());
		const auto hash = ((uint32_t*)lua_tolstring(L, -1, nullptr))[HASH_OFFSET];
		lua_pop(L, 1);
		prop_hash_map[hash] = it.second;
	}
}

static std::unordered_map<std::string, SPFbase::BlendMode> blendmode_map = {
	{ "mul+alpha",	SPFbase::BlendMode::MulAlpha		},
	{ "mul+add",	SPFbase::BlendMode::MulAdd		},
	{ "mul+rev",	SPFbase::BlendMode::MulRev		},
	{ "mul+sub",	SPFbase::BlendMode::MulSub		},
	{ "add+alpha",	SPFbase::BlendMode::AddAlpha		},
	{ "add+add",	SPFbase::BlendMode::AddAdd		},
	{ "add+rev",	SPFbase::BlendMode::AddRev		},
	{ "add+sub",	SPFbase::BlendMode::AddSub		},
	{ "alpha+bal",	SPFbase::BlendMode::AlphaBal		},
	{ "mul+min",	SPFbase::BlendMode::MulMin		},
	{ "mul+max",	SPFbase::BlendMode::MulMax		},
	{ "mul+mul",	SPFbase::BlendMode::MulMutiply	},
	{ "mul+screen",	SPFbase::BlendMode::MulScreen	},
	{ "add+min",	SPFbase::BlendMode::AddMin		},
	{ "add+max",	SPFbase::BlendMode::AddMax		},
	{ "add+mul",	SPFbase::BlendMode::AddMutiply	},
	{ "add+screen",	SPFbase::BlendMode::AddScreen	},
	{ "one",		SPFbase::BlendMode::One			},
};
static std::unordered_map<uint32_t, SPFbase::BlendMode> blendmode_hash_map;
void init_blendmode_hash_map(lua_State* L) {
	blendmode_hash_map.clear();
	for (auto it : blendmode_map)
	{
		lua_pushstring(L, it.first.c_str());
		const auto hash = ((uint32_t*)lua_tolstring(L, -1, nullptr))[HASH_OFFSET];
		lua_pop(L, 1);
		blendmode_hash_map[hash] = it.second;
	}
}

static std::unordered_map<std::string, ColorWrapperProperty> colorprop_map = {
	{ "a",		ColorWrapperProperty::m_a	},
	{ "r",		ColorWrapperProperty::m_r	},
	{ "g",		ColorWrapperProperty::m_g	},
	{ "b",		ColorWrapperProperty::m_b	},
	{ "argb",	ColorWrapperProperty::m_argb},
	{ "h",		ColorWrapperProperty::m_h	},
	{ "s",		ColorWrapperProperty::m_s	},
	{ "v",		ColorWrapperProperty::m_v	},
	{ "ARGB",	ColorWrapperProperty::f_ARGB},
	{ "AHSV",	ColorWrapperProperty::f_AHSV },
};
static std::unordered_map<uint32_t, ColorWrapperProperty> colorprop_hash_map;
void init_colorprop_hash_map(lua_State* L) {
	colorprop_hash_map.clear();
	for (auto it : colorprop_map)
	{
		lua_pushstring(L, it.first.c_str());
		const auto hash = ((uint32_t*)lua_tolstring(L, -1, nullptr))[HASH_OFFSET];
		lua_pop(L, 1);
		colorprop_hash_map[hash] = it.second;
	}
}

namespace Xrysnow {
	// GameObject 属性
	
	GameObjectProperty GameObjectPropertyHash(const char* key) {
		const auto hash = ((uint32_t*)key)[HASH_OFFSET];
		const auto it = prop_hash_map.find(hash);
		if (it != prop_hash_map.end())
			return it->second;
		return GameObjectProperty::_KEY_NOT_FOUND;
	}

	GameObjectProperty GameObjectPropertyHash(lua_State* L, int index) {
		const auto s = lua_tolstring(L, index, nullptr);
		const auto hash = ((uint32_t*)s)[HASH_OFFSET];
		const auto it = prop_hash_map.find(hash);
		if (it != prop_hash_map.end())
			return it->second;
		return GameObjectProperty::_KEY_NOT_FOUND;
	}

	GameObjectProperty GameObjectPropertyHash(lua_State* L, int index, const char** str) {
		const auto s = lua_tolstring(L, index, nullptr);
		if (str)
			* str = s;
		// hack into lua
		const auto hash = ((uint32_t*)s)[HASH_OFFSET];
		const auto it = prop_hash_map.find(hash);
		if (it != prop_hash_map.end())
			return it->second;
		return GameObjectProperty::_KEY_NOT_FOUND;
	}

	// BlendMode 枚举

	SPFbase::BlendMode BlendModeHash(lua_State* L, int index) {
		const auto s = lua_tolstring(L, index, nullptr);
		const auto hash = ((uint32_t*)s)[HASH_OFFSET];
		const auto it = blendmode_hash_map.find(hash);
		if (it != blendmode_hash_map.end())
			return it->second;
		return SPFbase::BlendMode::_KEY_NOT_FOUND;
	}
	
	// Color 包装器

	ColorWrapperProperty ColorWrapperPropertyHash(lua_State* L, int index) {
		const auto s = lua_tolstring(L, index, nullptr);
		const auto hash = ((uint32_t*)s)[HASH_OFFSET];
		const auto it = colorprop_hash_map.find(hash);
		if (it != colorprop_hash_map.end())
			return it->second;
		return ColorWrapperProperty::_KEY_NOT_FOUND;
	}

	// 初始化方法

	void InitStringToEnumHash(lua_State* L) {
		init_prop_hash_map(L);
		init_blendmode_hash_map(L);
		init_colorprop_hash_map(L);
	}
}
