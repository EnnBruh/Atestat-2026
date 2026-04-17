#include "core.h"

#include "Layers/layer.h"

signed main(void) {
        DEBUG_TRACE();
        core_init();

        window_create(&(WindowSpecification) {
                .width = 800,
                .height = 600,
                .is_resizable = true,
                .has_msaa = true,
                .has_vsync = true 
        });

        render_init();

        window_push_layer(&(Layer) {
                .active = true,
                .priority = 0,
                LAYER_ASSIGN(void)
        });

        window_push_layer(&(Layer) {
                .active = true,
                .priority = 1,
                LAYER_ASSIGN(game)
        });

        core_run();

        core_term();
        DEBUG_UNTRACE();
        return 0;
}