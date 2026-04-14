#include "core.h"

signed main(void) {
        DEBUG_TRACE();
        core_init();
        
        window_create(&(WindowSpecification) {
                .width = 1280,
                .height = 720,
                .name = "Digital Logic Simulation",
                .has_msaa = true,
                .is_resizable = true
        });

        core_run();
        core_term();
        DEBUG_UNTRACE();
        return 0;
}