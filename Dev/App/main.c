#include "core.h"

#include "layer.h"

signed main(void) {
        DEBUG_TRACE();
        core_init();

        settings_get_init();
        window_create(&(WindowSpecification) {
                .width = settings.resolution.x,
                .height = settings.resolution.y,
                .is_resizable = true,
                .has_msaa = true,
                .has_vsync = settings.vsync,
                .is_fullscreen = settings.fullscreen
        });

        render_init();

        void_layer_id = window_push_layer(&(Layer) {
                .active = true,
                .priority = 10,
                LAYER_ASSIGN(void)
        });

        debug_layer_id = window_push_layer(&(Layer){
            .active = settings.debug_mode,
            .priority = 100,
            LAYER_ASSIGN(debug)
        });

        game_layer_id = window_push_layer(&(Layer) {
                .active = false,
                .priority = 2,
                LAYER_ASSIGN(game)
        });

        map_layer_id = window_push_layer(&(Layer) {
                .active = false,
                .priority = 1,
                LAYER_ASSIGN(map)
        });

        menu_layer_id = window_push_layer(&(Layer) {
                .active = true,
                .priority = 1,
                LAYER_ASSIGN(menu)
        });

        workspace_layer_id = window_push_layer(&(Layer) {
                .active = false,
                .priority = 1,
                LAYER_ASSIGN(workspace)
        });
        
        settings_layer_id = window_push_layer(&(Layer) {
                .active = false,
                .priority = 8,
                LAYER_ASSIGN(settings)
        });

        // blur_layer_id = window_push_layer(&(Layer) {
        //         .active = false,
        //         .priority = 8,
        //         LAYER_ASSIGN(blur)
        // });

        escape_menu_layer_id = window_push_layer(&(Layer) {
                .active = false,
                .priority = 5,
                LAYER_ASSIGN(escape_menu)
        });

        core_run();

        core_term();
        DEBUG_UNTRACE();
        return 0;
}