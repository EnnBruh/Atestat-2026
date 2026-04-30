#include "layer.h"

LayerID workspace_layer_id;

typedef struct {
        f32vec2 pos;
        f32vec2 dim;
        char* workspace_name;
        char* workspace_last_modified;
} WorkspaceData;

ENNDEF_PUBLIC ENN_CMP workspace_cmp(WorkspaceData a, WorkspaceData b) {
        i32 cmp = strcmp(a.workspace_last_modified, b.workspace_last_modified);
        if (cmp > 0) return ENN_SMALLER;
        if (cmp < 0) return ENN_BIGGER;
        return ENN_EQUAL;
}

static UITextButtonList buttons;
static vector(WorkspaceData) workspaces;
static WorkspaceData* selected_workspace;

static vector(char) input_string;
static bool typing_state;
static bool cursor_state = true;
static f64 last_cursor_change;

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

#define BKG_COLOR 0x101214FF

#define SAVE_DATA_FMT "LAST SAVE: %Y.%m.%d|%H:%M:%S"
#define SAVE_DATA_TEXT_HEIGHT 0.035

#define INPUT_STRING_TEXT_HEIGHT 0.2
#define ENN_CURSOR_CHANGE_TIME 0.5

void workspace_layer_init(void) {
        DEBUG_TRACE();
        ui_text_button_list_init(
                &buttons, ENN_LEFT_ALIGN, 0x505050FF,
                (UITextButtonData[]) {
                        (UITextButtonData) { 
                                .id             = CREATE_WORKSPACE_BUTTON_ID,
                                .pos            = { -0.85, workspaces_box.y + 0.1 },
                                .color          = 0xFFFFFFFF,
                                .text           = "NEW WORKSPACE",
                                .text_height    = 0.075
                        },
                        (UITextButtonData) {
                                .id             = DELETE_WORKSPACE_BUTTON_ID,
                                .pos            = { -0.85, workspaces_box.y + 0.1 * 2},
                                .color          = 0xFFFFFFFF,
                                .text           = "DELETE WORKSPACE",
                                .text_height    = 0.075
                        },
                        (UITextButtonData) {
                                .id             = OPEN_WORKSPACE_BUTTON_ID,
                                .pos            = { -0.85, workspaces_box.y + 0.1 * 3 },
                                .color          = 0xFFFFFFFF,
                                .text           = "OPEN WORKSPACE",
                                .text_height    = 0.075
                        },
                        (UITextButtonData) {
                                .id             = BACK_BUTTON_ID,
                                .pos            = { -0.85, workspaces_box.y + 0.1 * 4 },
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
                WorkspaceData data;
                char* name = workspace_entry -> d_name;
                char* extension = strstr(name, ENN_DATAFILE_FILE_EXTENSION);

                if (extension == 0) continue ;

                data.dim = (f32vec2) { 0.0, 0.05 };
                data.pos = (f32vec2) {
                        .x = -0.2,
                        .y = -0.3 + 0.11 * vector_size(workspaces)
                };

                char* full_path = calloc((sizeof (ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits/")) + workspace_entry ->d_namlen, (sizeof (char)));
                sprintf(full_path, ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits/%s", workspace_entry -> d_name);
                struct tm last_modified = *localtime(&(time_t) { file_get_date(full_path) } );
                free(full_path);

                data.workspace_name = calloc(extension - workspace_entry -> d_name + 1, (sizeof (char)));
                memcpy(data.workspace_name, (char*)workspace_entry -> d_name, (sizeof (char)) * (extension - workspace_entry -> d_name));

                data.workspace_last_modified = calloc((sizeof SAVE_DATA_FMT) * 2, (sizeof (char)));
                strftime(data.workspace_last_modified, (sizeof SAVE_DATA_FMT) * 2, SAVE_DATA_FMT, &last_modified);

                vector_push_back(workspaces, data);
        }
        directory_close(workspace_dir);

        vector_sort(workspaces, workspace_cmp, workspaces.start, workspaces.end);
        for (i32 i = workspaces.start; i < workspaces.end; ++i) {
                workspaces.data[i].pos = (f32vec2) {
                        .x = -0.2,
                        .y = -0.3 + 0.11 * (i - workspaces.start)
                };
        }

        DEBUG_UNTRACE();
}

void workspace_layer_term(void) {
        DEBUG_TRACE();
        ui_text_button_list_term(&buttons);
        for (i32 i = workspaces.start; i < workspaces.end; ++i) {
                free(workspaces.data[i].workspace_name);
                free(workspaces.data[i].workspace_last_modified);
        }
        vector_destroy(workspaces);
        vector_destroy(input_string);
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

        for (i32 i = workspaces.start; i < workspaces.end; ++i) {
                render_text_push(
                        workspaces.data[i].pos,
                        workspaces.data[i].pos,
                        workspaces.data[i].workspace_name, 0xFFFFFFFF, 0.05, ENN_LEFT_ALIGN
                );

                render_text_push(
                        (f32vec2) { workspaces.data[i].pos.x, workspaces.data[i].pos.y + workspaces.data[i].dim.y },
                        (f32vec2) { workspaces.data[i].pos.x, workspaces.data[i].pos.y + workspaces.data[i].dim.y },
                        workspaces.data[i].workspace_last_modified, 0x505050FF, SAVE_DATA_TEXT_HEIGHT, ENN_LEFT_ALIGN
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

        if (typing_state) {
                render_rectangle_push(
                        (f32vec2) { -1.0, -1.0 },
                        (f32vec2) { 1.0, 1.0 },
                        0x00000050
                );

                f64 time = glfwGetTime();
                if (time - last_cursor_change >= ENN_CURSOR_CHANGE_TIME) {
                        cursor_state = !cursor_state;
                        last_cursor_change = time;
                }

                f32 render_text_ratio = ((f32)global_render.font_atlas.char_dim.x / (f32)global_render.font_atlas.char_dim.y);
                f32 text_width = vector_size(input_string) * INPUT_STRING_TEXT_HEIGHT * render_text_ratio;

                f32vec2 text_pos1 = { -1.0, -INPUT_STRING_TEXT_HEIGHT / 2.0 };
                f32vec2 text_pos2 = { 1.0, INPUT_STRING_TEXT_HEIGHT / 2.0 };

                if (vector_size(input_string) > 0) {
                        render_text_push(
                                text_pos1,
                                text_pos2,
                                input_string.data + input_string.start,
                                0xFFFFFFFF,
                                INPUT_STRING_TEXT_HEIGHT,
                                ENN_CENTER_ALIGN
                        );
                }

                if (cursor_state) {
                        render_rectangle_push(
                                (f32vec2) { text_width / 2.0, text_pos1.y },
                                (f32vec2) { text_width / 2.0 + INPUT_STRING_TEXT_HEIGHT * render_text_ratio / 2.0, text_pos2.y },
                                0xFFFFFFFF
                        );
                }
        }

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
                                if (typing_state) {
                                        typing_state = false;
                                        vector_clear(input_string);
                                        break;
                                }

                                if (buttons.hover != NULL) {
                                        switch (buttons.hover -> id) {
                                                case CREATE_WORKSPACE_BUTTON_ID:
                                                {
                                                        typing_state = true;
                                                        input_string.end = input_string.start;
                                                        if (input_string.capacity > 0) input_string.data[input_string.end] = 0;
                                                        cursor_state = true;
                                                        last_cursor_change = glfwGetTime();
                                                        break;
                                                }
                                                case BACK_BUTTON_ID:
                                                {
                                                        layer_set_active(menu_layer_id);
                                                        layer_set_inactive(workspace_layer_id);
                                                        break;
                                                }
                                                case DELETE_WORKSPACE_BUTTON_ID:
                                                {
                                                        if (selected_workspace != NULL) {
                                                                char* path = calloc(strlen(ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits/") + strlen(selected_workspace -> workspace_name) + strlen(ENN_DATAFILE_FILE_EXTENSION) + 1, (sizeof (char)));
                                                                sprintf(path, ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits/%s%s", selected_workspace -> workspace_name, ENN_DATAFILE_FILE_EXTENSION);
                                                                file_remove(path);
                                                                free(path);

                                                                free(selected_workspace -> workspace_name);
                                                                free(selected_workspace -> workspace_last_modified);
                                                                
                                                                f32 current_scroll = (vector_size(workspaces) > 0) ? workspaces.data[workspaces.start].pos.y + 0.3 : 0.0;
                                                                vector_remove_at_address_keep_order(workspaces, selected_workspace);
                                                                selected_workspace = NULL;

                                                                for (i32 i = workspaces.start; i < workspaces.end; ++i) {
                                                                        workspaces.data[i].pos = (f32vec2) {
                                                                                .x = -0.2,
                                                                                .y = -0.3 + 0.11 * (i - workspaces.start) + current_scroll
                                                                        };
                                                                }
                                                        }
                                                        break;
                                                }
                                                default: break;
                                        }
                                }

                                f32vec2 ndc = screen_to_ndc((f32vec2) { global_state.mouse_pos.x, global_state.mouse_pos.y });
                                for (i32 i = workspaces.start; i < workspaces.end; ++i) {
                                        if (is_inside_rectangle(
                                                ndc,
                                                (f32vec4){
                                                    workspaces_box.x,
                                                    workspaces.data[i].pos.y,
                                                    workspaces_box.z - workspaces_box.x,
                                                    workspaces.data[i].dim.y + SAVE_DATA_TEXT_HEIGHT}))
                                        {
                                                selected_workspace = &workspaces.data[i];
                                                break;
                                        }
                                }
                        }
                        break;
                }
                case ENN_INPUT_MOUSE_MOVE_EVENT:
                {
                        if (!typing_state) {
                                f64vec2* data = event -> data;
                                f32vec2 ndc = screen_to_ndc((f32vec2) { data -> x, data -> y });
                                ui_text_button_list_check_hover(&buttons, ndc);
                        }
                        break;
                }
                case ENN_INPUT_KEY_EVENT:
                {
                        struct { i32 key, action; }* data = event -> data;
                        if (data -> key == GLFW_KEY_ESCAPE && data -> action == GLFW_PRESS) {
                                if (typing_state) {
                                        typing_state = false;
                                        vector_clear(input_string);
                                } else {
                                        layer_set_active(menu_layer_id);
                                        layer_set_inactive(workspace_layer_id);
                                }
                        }
                        if (data -> key == GLFW_KEY_DELETE && data -> action == GLFW_PRESS) {
                                if (!typing_state) {
                                        if (selected_workspace != NULL) {
                                                char* path = calloc(strlen(ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits/") + strlen(selected_workspace -> workspace_name) + strlen(ENN_DATAFILE_FILE_EXTENSION) + 1, (sizeof (char)));
                                                sprintf(path, ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits/%s%s", selected_workspace -> workspace_name, ENN_DATAFILE_FILE_EXTENSION);
                                                file_remove(path);
                                                free(path);

                                                free(selected_workspace -> workspace_name);
                                                free(selected_workspace -> workspace_last_modified);
                                                
                                                f32 current_scroll = (vector_size(workspaces) > 0) ? workspaces.data[workspaces.start].pos.y + 0.3 : 0.0;
                                                vector_remove_at_address_keep_order(workspaces, selected_workspace);
                                                selected_workspace = NULL;

                                                for (i32 i = workspaces.start; i < workspaces.end; ++i) {
                                                        workspaces.data[i].pos = (f32vec2) {
                                                                .x = -0.2,
                                                                .y = -0.3 + 0.11 * (i - workspaces.start) + current_scroll
                                                        };
                                                }
                                        }
                                }
                        }
                        if (data -> key == GLFW_KEY_BACKSPACE && (data -> action == GLFW_PRESS || data -> action == GLFW_REPEAT)) {
                                if (typing_state) {
                                        if (vector_size(input_string) <= 0) break;
                                        vector_pop_back(input_string);
                                        input_string.data[input_string.end] = 0;
                                        cursor_state = true;
                                        last_cursor_change = glfwGetTime();
                                }
                        }
                        if (data -> key == GLFW_KEY_ENTER && data -> action == GLFW_PRESS) {
                                if (typing_state) {
                                        if (vector_size(input_string) > 0) {
                                                char* path = calloc(strlen(ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits/") + strlen(input_string.data + input_string.start) + strlen(ENN_DATAFILE_FILE_EXTENSION) + 1, (sizeof (char)));
                                                sprintf(path, ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits/%s%s", input_string.data + input_string.start, ENN_DATAFILE_FILE_EXTENSION);
                                                
                                                file_write_cstring(path, "", 0);

                                                WorkspaceData new_ws;
                                                new_ws.dim = (f32vec2) { 0.0, 0.05 };
                                                new_ws.pos = (f32vec2) { 0.0, 0.0 };

                                                new_ws.workspace_name = calloc(strlen(input_string.data + input_string.start) + 1, (sizeof (char)));
                                                strcpy(new_ws.workspace_name, input_string.data + input_string.start);

                                                struct tm last_modified = *localtime(&(time_t) { file_get_date(path) } );
                                                new_ws.workspace_last_modified = calloc((sizeof SAVE_DATA_FMT) * 2, (sizeof (char)));
                                                strftime(new_ws.workspace_last_modified, (sizeof SAVE_DATA_FMT) * 2, SAVE_DATA_FMT, &last_modified);

                                                f32 current_scroll = (vector_size(workspaces) > 0) ? workspaces.data[workspaces.start].pos.y + 0.3 : 0.0;
                                                
                                                vector_push_back(workspaces, new_ws);
                                                vector_sort(workspaces, workspace_cmp, workspaces.start, workspaces.end);
                                                
                                                for (i32 i = workspaces.start; i < workspaces.end; ++i) {
                                                        workspaces.data[i].pos = (f32vec2) {
                                                                .x = -0.2,
                                                                .y = -0.3 + 0.11 * (i - workspaces.start) + current_scroll
                                                        };
                                                }
                                                
                                                free(path);
                                        }
                                        typing_state = false;
                                        vector_clear(input_string);
                                }
                        }
                        break;
                }
                case ENN_INPUT_TEXT_EVENT:
                {
                        if (typing_state) {
                                u32* code = event -> data;
                                if (*code < ENN_FONT_ATLAS_FIRST_CHAR || *code > ENN_FONT_ATLAS_LAST_CHAR) break;
                                char ch = (char)*code;
                                vector_push_back(input_string, ch);
                                input_string.data[input_string.end] = 0;
                                cursor_state = true;
                                last_cursor_change = glfwGetTime();
                        }
                        break;
                }
                case ENN_INPUT_MOUSE_SCROLL_EVENT:
                {
                        if (!typing_state) {
                                f64* offset = event -> data;
                                for (i32 i = workspaces.start; i < workspaces.end; ++i)
                                        workspaces.data[i].pos.y += WORKSPACE_LIST_SCROLL_CHANGE * *offset;
                        }
                        break;
                }
                default: break;
        }
        DEBUG_UNTRACE();
}