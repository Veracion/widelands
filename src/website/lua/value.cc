/*
 * Copyright (C) 2018-2023 by the Widelands Development Team
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
 * along with this program; if not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "website/lua/value.h"

#include <sstream>

namespace LuaTree {

Boolean::Boolean(bool value) : bool_value(value) {
}
std::string Boolean::as_string() const {
	return bool_value ? "true" : "false";
}

Double::Double(double value) : double_value(value) {
}
std::string Double::as_string() const {
	std::ostringstream strs;
	strs << double_value;
	return strs.str();
}

Int::Int(int value) : int_value(value) {
}
std::string Int::as_string() const {
	std::ostringstream strs;
	strs << int_value;
	return strs.str();
}

std::string Empty::as_string() const {
	return "nil";
}

String::String(const std::string& value) : string_value(value) {
}
std::string String::as_string() const {
	return "\"" + string_value + "\"";
}

Raw::Raw(const std::string& value) : raw_value(value) {
}
std::string Raw::as_string() const {
	return raw_value;
}

}  // namespace LuaTree
