/*
 * Copyright (C) 2008-2023 by the Widelands Development Team
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

#ifndef WL_LOGIC_PLAYER_END_RESULT_H
#define WL_LOGIC_PLAYER_END_RESULT_H

namespace Widelands {
enum class PlayerEndResult : uint8_t { kLost = 0, kWon = 1, kResigned = 2, kUndefined = 255 };
}  // namespace Widelands

#endif  // end of include guard: WL_LOGIC_PLAYER_END_RESULT_H
