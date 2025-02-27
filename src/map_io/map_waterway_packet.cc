/*
 * Copyright (C) 2002-2023 by the Widelands Development Team
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

#include "map_io/map_waterway_packet.h"

#include "base/macros.h"
#include "economy/waterway.h"
#include "io/fileread.h"
#include "io/filewrite.h"
#include "logic/editor_game_base.h"
#include "logic/map.h"
#include "logic/player.h"
#include "map_io/map_object_loader.h"
#include "map_io/map_object_saver.h"

namespace Widelands {

constexpr uint16_t kCurrentPacketVersion = 1;

void MapWaterwayPacket::read(FileSystem& fs,
                             EditorGameBase& egbase,
                             bool const skip,
                             MapObjectLoader& mol) {
	if (skip) {
		return;
	}

	FileRead fr;
	try {
		fr.open(fs, "binary/waterway");
	} catch (...) {
		return;
	}

	try {
		uint16_t const packet_version = fr.unsigned_16();
		if (packet_version == kCurrentPacketVersion) {
			Serial serial;
			while ((serial = fr.unsigned_32()) != 0xffffffff) {
				try {
					//  If this is already known, get it.
					//  Waterway data is read somewhere else
					mol.register_object(serial, *new Waterway()).init(egbase);
				} catch (const WException& e) {
					throw GameDataError("%u: %s", serial, e.what());
				}
			}
		} else {
			throw UnhandledVersionError("MapWaterwayPacket", packet_version, kCurrentPacketVersion);
		}
	} catch (const WException& e) {
		throw GameDataError("waterway: %s", e.what());
	}
}

void MapWaterwayPacket::write(FileSystem& fs, EditorGameBase& egbase, MapObjectSaver& mos) {
	FileWrite fw;

	fw.unsigned_16(kCurrentPacketVersion);

	//  Write waterways. Register this with the map_object_saver so that its data
	//  can be saved later.
	const Map& map = egbase.map();
	Field* field = &map[0];
	Field const* const fields_end = field + map.max_index();
	for (; field < fields_end; ++field) {
		if (upcast(Waterway const, ww, field->get_immovable())) {  // only waterways
			//  Waterways can life on multiple positions.
			if (!mos.is_object_known(*ww)) {
				fw.unsigned_32(mos.register_object(*ww));
			}
		}
	}
	fw.unsigned_32(0xffffffff);

	fw.write(fs, "binary/waterway");
}
}  // namespace Widelands
