dirname = path.dirname(__file__)

tribes:new_immovable_type {
   name = "field_harvested",
   -- TRANSLATORS: This is an immovable name used in lists of immovables
   descname = _"Field (harvested)",
   programs = {
		disappear = {
			"animate=idle 500000",
			"remove=remove",
		}
   },
   helptext = {
		default = ""
   },
   animations = {
      idle = {
         pictures = path.list_directory(dirname, "idle_\\d+.png"),
         hotspot = { 15, 18 },
      },
   }
}
