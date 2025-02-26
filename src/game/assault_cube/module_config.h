#ifndef EVIL_CAT_GAME_ASSAULT_CUBE_MODULE_CONFIG_H
#define EVIL_CAT_GAME_ASSAULT_CUBE_MODULE_CONFIG_H

#include "mem/process_memory_external.h"
#include "proc/process_info_external.h"
#include "view/imgui_d3d9_external/view.h"
#include "game.h"
#include "player.h"
#include "menu.h"
#include "services_chooser.h"

using ProcessMemoryImpl = ProcessMemoryExternal;
using ProcessInfoImpl = ProcessInfoExternal;
using ViewImpl = ImGuiD3D9ExternalView;

using GameImpl = Game;
using MenuImpl = Menu;
using ServicesChooserImpl = ServicesChooser;

#endif //EVIL_CAT_GAME_ASSAULT_CUBE_MODULE_CONFIG_H
