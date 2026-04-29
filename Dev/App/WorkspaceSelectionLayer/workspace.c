#include "layer.h"

LayerID workspace_layer_id;

static UITextButtonList buttons;
static UITextButtonList workspaces;
static UITextButton* selected_workspace;
static vector(struct { 
        char* name;
        char* last_modif; 
}) workspace_names;
// static f32 workspace_list_offset;

static const f32vec4 workspaces_box = {
        .x = -0.205,
        .y = -0.4,
        .z = 0.8,
        .w = 0.5
};

#define WORKSPACE_LIST_SCROLL_CHANGE  0.035

#define CREATE_WORKSPACE_BUTTON_ID 0x001
#define DELETE_WORKSPACE_BUTTON_ID 0x002
#define OPEN_WORKSPACE_BUTTON_ID   0x003
#define BACK_BUTTON_ID 0x004
#define WORKSPACE_BUTTON_ID 0x005

#define BKG_COLOR 0x101214FF

#define SAVE_DATA_FMT "LAST SAVE: %Y.%m.%d|%H:%M:%S"
#define SAVE_DATA_TEXT_HEIGHT 0.035


void workspace_layer_init(void) {
        DEBUG_TRACE();
        ui_text_button_list_init(
                &buttons, ENN_LEFT_ALIGN, 0x505050FF,
                (UITextButtonData[]) {
                        (UITextButtonData) { 
                                .id             = CREATE_WORKSPACE_BUTTON_ID,
                                .pos            = { -0.85, -0.2 },
                                .color          = 0xFFFFFFFF,
                                .text           = "NEW WORKSPACE",
                                .text_height    = 0.075
                        },
                        (UITextButtonData) {
                                .id             = DELETE_WORKSPACE_BUTTON_ID,
                                .pos            = { -0.85, -0.1 },
                                .color          = 0xFFFFFFFF,
                                .text           = "DELETE WORKSPACE",
                                .text_height    = 0.075
                        },
                        (UITextButtonData) {
                                .id             = OPEN_WORKSPACE_BUTTON_ID,
                                .pos            = { -0.85, 0.0 },
                                .color          = 0xFFFFFFFF,
                                .text           = "OPEN WORKSPACE",
                                .text_height    = 0.075
                        },
                        (UITextButtonData) {
                                .id             = BACK_BUTTON_ID,
                                .pos            = { -0.85, 0.1 },
                                .color          = 0xd75f5fFF,
                                .text           = "BACK",
                                .text_height    = 0.075
                        }
                },
                4
        );

        directory_create(ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits");

        DIR* workspace_dir = directory_open(ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits");
        DirEntry* workspace_entry = NULL;
        while ((workspace_entry = directory_read(workspace_dir))) {
                struct { char* name, *last_modif; } data;
                char* name = workspace_entry -> d_name;
                char* extension = strstr(name, ENN_DATAFILE_FILE_EXTENSION);

                if (extension == 0) continue ;

                data.name = calloc((sizeof (ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits/")) + workspace_entry ->d_namlen, (sizeof (char)));
                sprintf(data.name, ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits/%s", workspace_entry -> d_name);
                struct tm last_modified = *localtime(&(time_t) { file_get_date(data.name) } );
                free(data.name);

                data.name = calloc(extension - workspace_entry -> d_name+ 1, (sizeof (char)));
                memcpy(data.name, (char*)workspace_entry -> d_name, (sizeof (char)) * (extension - workspace_entry -> d_name));

                data.last_modif = calloc((sizeof SAVE_DATA_FMT) * 2, (sizeof (char)));
                strftime(data.last_modif, (sizeof SAVE_DATA_FMT) * 2, SAVE_DATA_FMT, &last_modified);

                vector_push_back(workspace_names, data);
        }
        directory_close(workspace_dir);

        vector(UITextButtonData) workspace_buttons = vector_new();
        for (i32 i = workspace_names.start; i < workspace_names.end; ++i) {
                UITextButtonData data = {
                        .id     = WORKSPACE_BUTTON_ID,
                        .color  = 0xFFFFFFFF,
                        .pos    = (f32vec2) {
                                .x = -0.2,
                                .y = -0.3 + 0.11 * (i - workspace_names.start)
                        },
                        .text = workspace_names.data[i].name,
                        .text_height = 0.05
                };
                vector_push_back(workspace_buttons, data);
        }

        ui_text_button_list_init(
                &workspaces, ENN_LEFT_ALIGN, 0x505050FF,
                workspace_buttons.data + workspace_buttons.start, vector_size(workspace_buttons)
        );
        vector_destroy(workspace_buttons);

        DEBUG_UNTRACE();
}

void workspace_layer_term(void) {
        DEBUG_TRACE();
        ui_text_button_list_term(&buttons);
        for (i32 i = workspace_names.start; i < workspace_names.end; ++i) {
                free(workspace_names.data[i].name);
                free(workspace_names.data[i].last_modif);
        }
        vector_destroy(workspace_names);
        DEBUG_UNTRACE();
}

void workspace_layer_on_render(void) {
        DEBUG_TRACE();
        render_proj_set((f32mat4) {
                1, 0, 0, 0,
                0, -1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        });

        render_rectangle_push(
                (f32vec2) { -1.0, -1.0 },
                (f32vec2) { 1.0, 1.0 },
                BKG_COLOR
        );

        ui_text_button_list_render(&buttons);

        render_rectangle_push(
                (f32vec2) { workspaces_box.x, workspaces_box.y },
                (f32vec2) { workspaces_box.z, workspaces_box.w },
                0x151819FF
        );
        ui_text_button_list_render(&workspaces);
        for (i32 i = workspace_names.start; i < workspace_names.end; ++i) {
                i32 idx = i - workspace_names.start + workspaces.list.start;
                render_text_push(
                        (f32vec2) { workspaces.list.data[idx].pos.x, workspaces.list.data[idx].pos.y + workspaces.list.data[idx].dim.y },
                        (f32vec2) { workspaces.list.data[idx].pos.x, workspaces.list.data[idx].pos.y + workspaces.list.data[idx].dim.y },
                        workspace_names.data[i].last_modif, 0x505050FF, SAVE_DATA_TEXT_HEIGHT, ENN_LEFT_ALIGN
                );
        }

        if (selected_workspace != NULL) {
                render_rectangle_push(
                        (f32vec2) { workspaces_box.x, selected_workspace -> pos.y },
                        (f32vec2) { workspaces_box.z, selected_workspace -> pos.y + selected_workspace -> dim.y + SAVE_DATA_TEXT_HEIGHT },
                        0xFFFFFF30
                );
        }


        render_rectangle_push(
                (f32vec2) { workspaces_box.x, workspaces_box.y },
                (f32vec2) { 1.0, -1.0 },
                BKG_COLOR
        );

        render_rectangle_push(
                (f32vec2) { workspaces_box.z, -1.0 },
                (f32vec2) { 1.0, 1.0 },
                BKG_COLOR
        );

        render_rectangle_push(
                (f32vec2) { workspaces_box.x, workspaces_box.w },
                (f32vec2) { 1.0, 1.0 },
                BKG_COLOR
        );

        render_text_push(
                (f32vec2) { -0.475, -0.75 },
                (f32vec2) { 0.475, -0.65 },
                "SELECT A WORKSPACE", 0xFFFFFFFF, 0.1, ENN_CENTER_ALIGN
        );
        DEBUG_UNTRACE();
}

void workspace_layer_on_update(f64 dt) {
}

void workspace_layer_on_event(Event* event) {
        DEBUG_TRACE();
        switch (event -> type) {
                case ENN_INPUT_MOUSE_BUTTON_EVENT:
                {
                        struct { i32 button, action; }* data = event -> data;
                        if (data -> button == GLFW_MOUSE_BUTTON_LEFT && data -> action == GLFW_PRESS) {
                                if (buttons.hover != NULL) {
                                        switch (buttons.hover -> id) {
                                                case BACK_BUTTON_ID:
                                                {
                                                        layer_set_active(menu_layer_id);
                                                        layer_set_inactive(workspace_layer_id);
                                                        break;
                                                }
                                                case DELETE_WORKSPACE_BUTTON_ID:
                                                {
                                                        if (selected_workspace != NULL) {
                                                                vector_remove_at_address(workspaces.list, selected_workspace);
                                                        }
                                                        break;
                                                }
                                                default: break;
                                        }
                                }

                                if (workspaces.hover != NULL) {
                                        selected_workspace = workspaces.hover;
                                } else {
                                        f32vec2 ndc = screen_to_ndc((f32vec2) { global_state.mouse_pos.x, global_state.mouse_pos.y });
                                        for (i32 i = workspaces.list.start; i < workspaces.list.end; ++i) {
                                                if (is_inside_rectangle(
                                                        ndc,
                                                        (f32vec4){
                                                            workspaces_box.x,
                                                            workspaces.list.data[i].pos.y,
                                                            workspaces_box.z - workspaces_box.x,
                                                            workspaces.list.data[i].dim.y + SAVE_DATA_TEXT_HEIGHT}))
                                                {
                                                        selected_workspace = &workspaces.list.data[i];
                                                        break;
                                                }
                                        }
                                }
                        }
                        break;
                }
                case ENN_INPUT_MOUSE_MOVE_EVENT:
                {
                        f64vec2* data = event -> data;
                        f32vec2 ndc = screen_to_ndc((f32vec2) { data -> x, data -> y });
                        ui_text_button_list_check_hover(&buttons, ndc);
                        ui_text_button_list_check_hover(&workspaces, ndc);
                        break;
                }
                case ENN_INPUT_KEY_EVENT:
                {
                        struct { i32 key, action; }* data = event -> data;
                        if (data -> key == GLFW_KEY_ESCAPE && data -> action == GLFW_PRESS) {
                                layer_set_active(menu_layer_id);
                                layer_set_inactive(workspace_layer_id);
                        }
                        if (data -> key == GLFW_KEY_DELETE && data -> action == GLFW_PRESS) {
                        }
                        break;
                }
                case ENN_INPUT_MOUSE_SCROLL_EVENT:
                {
                        f64* offset = event -> data;
                        for (i32 i = workspaces.list.start; i < workspaces.list.end; ++i)
                                workspaces.list.data[i].pos.y += WORKSPACE_LIST_SCROLL_CHANGE * *offset;
                        break;
                }
                default: break;
        }
        DEBUG_UNTRACE();
}