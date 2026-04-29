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
LAYER_DEFINE(map);
LAYER_DEFINE(blur);
LAYER_DEFINE(escape_menu);


ENNDEF_PRIVATE void blur_layer_update_texture(void);
#endif