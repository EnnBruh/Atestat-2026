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
                .has_vsync = false
        });

        render_init();

        window_push_layer(&(Layer) {
                .active = true,
                .priority = 10,
                LAYER_ASSIGN(void)
        });

        window_push_layer(&(Layer) {
                .active = true,
                .priority = 100,
                LAYER_ASSIGN(debug)
        });

        window_push_layer(&(Layer) {
                .active = true,
                .priority = 2,
                LAYER_ASSIGN(game)
        });
        window_push_layer(&(Layer) {
                .active = true,
                .priority = 1,
                LAYER_ASSIGN(map)
        });

        core_run();

        core_term();
        DEBUG_UNTRACE();
        return 0;
}