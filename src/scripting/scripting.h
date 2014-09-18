/*
 * Copyright (C) 2006-2010 by the Widelands Development Team
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef WL_SCRIPTING_SCRIPTING_H
#define WL_SCRIPTING_SCRIPTING_H

#include <map>
#include <memory>
#include <string>

#include <stdint.h>

#include "scripting/lua_errors.h"
#include "third_party/eris/lua.hpp"

class FileRead;
class FileWrite;

namespace Widelands {
	class EditorGameBase;
	class Game;
	class MapObjectLoader;
	struct MapObjectSaver;
}

class EditorFactory;
class GameFactory;
class LuaCoroutine;
class LuaTable;

// Provides an interface to call and execute Lua Code.
class LuaInterface {
public:
	LuaInterface();
	virtual ~LuaInterface();

	// Interpret the given string, will throw 'LuaError' on any error.
	void interpret_string(const std::string&);

	std::unique_ptr<LuaTable> run_script(const std::string& script);
	std::unique_ptr<LuaTable> get_hook(const std::string& name);

protected:
	lua_State * m_L;
};

class LuaEditorInterface : public LuaInterface {
public:
	LuaEditorInterface(Widelands::EditorGameBase * g);
	virtual ~LuaEditorInterface();

private:
	std::unique_ptr<EditorFactory> m_factory;
};

class LuaGameInterface : public LuaInterface {
public:
	LuaGameInterface(Widelands::Game * g);
	virtual ~LuaGameInterface();

	// Input/output for coroutines.
	LuaCoroutine* read_coroutine(FileRead&);
	void write_coroutine(FileWrite&, LuaCoroutine*);

	// Input output for the global game state.
	void read_global_env
		(FileRead &, Widelands::MapObjectLoader &, uint32_t);
	uint32_t write_global_env
		(FileWrite &, Widelands::MapObjectSaver &);

private:
	std::unique_ptr<GameFactory> m_factory;
};
#endif  // end of include guard: WL_SCRIPTING_SCRIPTING_H
