dirname = path.dirname (__file__)

tribes:new_productionsite_type {
   msgctxt = "frisians_building",
   name = "frisians_drinking_hall",
   -- TRANSLATORS: This is a building name used in lists of buildings
   descname = pgettext ("frisians_building", "Drinking Hall"),
   helptext_script = dirname .. "helptexts.lua",
   icon = dirname .. "menu.png",
   size = "medium",

   enhancement_cost = {
      brick = 2,
      granite = 2,
      log = 1,
      thatch_reed = 1
   },
   return_on_dismantle_on_enhanced = {
      brick = 1,
      granite = 1,
      thatch_reed = 1
   },

   animations = {
      idle = {
         pictures = path.list_files (dirname .. "idle_??.png"),
         hotspot = {56, 80},
         fps = 10,
      },
      working = {
         pictures = path.list_files (dirname .. "working_??.png"),
         hotspot = {56, 80},
         fps = 10,
      },
      unoccupied = {
         pictures = path.list_files (dirname .. "unoccupied_?.png"),
         hotspot = {56, 80},
      },
   },

   aihints = {
      prohibited_till = 930
   },

   working_positions = {
      frisians_landlady = 1
   },

   inputs = {
      { name = "fruit", amount = 4 },
      { name = "honey_bread", amount = 4 },
      { name = "beer", amount = 4 },
      { name = "smoked_fish", amount = 4 },
      { name = "smoked_meat", amount = 4 },
   },
   outputs = {
      "ration",
      "meal"
   },

   programs = {
      work = {
         -- TRANSLATORS: Completed/Skipped/Did not start working because ...
         descname = _"working",
         actions = {
            "call=produce_ration",
            "call=produce_meal",
            "return=skipped"
         }
      },
      produce_ration = {
         -- TRANSLATORS: Completed/Skipped/Did not start preparing a ration because ...
         descname = _"preparing a ration",
         actions = {
            "return=skipped unless economy needs ration",
            "sleep=14000",
            "consume=fruit,smoked_fish,smoked_meat",
            "animate=working 19000",
            "produce=ration"
         }
      },
      produce_meal = {
         -- TRANSLATORS: Completed/Skipped/Did not start preparing a meal because ...
         descname = _"preparing a meal",
         actions = {
            "return=skipped unless economy needs meal",
            "sleep=10000",
            "consume=beer honey_bread smoked_fish,smoked_meat",
            "animate=working 30000",
            "produce=meal"
         }
      },
   },
}
