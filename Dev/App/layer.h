#ifndef LAYERS_H
#define LAYERS_H

#include "core.h"
#include "Rendering/render.h"
#include "UI/ui.h"
#include "state.h"


LAYER_DEFINE(void);
LAYER_DEFINE(debug);
LAYER_DEFINE(menu);
LAYER_DEFINE(workspace);
LAYER_DEFINE(settings);
LAYER_DEFINE(game);
LAYER_DEFINE(game_ui);
LAYER_DEFINE(chip);
LAYER_DEFINE(map);
LAYER_DEFINE(blur);
LAYER_DEFINE(escape_menu);


ENNDEF_PRIVATE void blur_layer_update_texture(void);
ENNDEF_PRIVATE void game_start(const char* save_filepath);
ENNDEF_PRIVATE void game_stop(void);
ENNDEF_PRIVATE void game_save_current_workspace(void);
ENNDEF_PRIVATE void game_ui_save_circuit(void);
ENNDEF_PRIVATE void game_ui_start_compile(void);
ENNDEF_PRIVATE void game_ui_toggle_mode(void);
ENNDEF_PRIVATE void chip_layer_start_compile(void);
#endif
