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
static WorkspaceData* hovered_workspace;
static WorkspaceData* last_clicked_workspace;

static vector(char) input_string;
static bool typing_state;
static bool cursor_state = true;
static f64 last_cursor_change;
static bool name_conflict_error;
static bool hovered_confirm_button;

static f32 workspace_list_offset;
static bool is_dragging_scrollbar;
static f64 last_workspace_click_time;

#define ENN_WORKSPACES_BOX_X                            -0.205
#define ENN_WORKSPACES_BOX_Y                            -0.4
#define ENN_WORKSPACES_BOX_Z                            0.8
#define ENN_WORKSPACES_BOX_W                            0.5

#define ENN_WORKSPACE_LIST_SCROLL_CHANGE                0.035

#define ENN_CREATE_WORKSPACE_BUTTON_ID                  0x001
#define ENN_DELETE_WORKSPACE_BUTTON_ID                  0x002
#define ENN_OPEN_WORKSPACE_BUTTON_ID                    0x003
#define ENN_BACK_BUTTON_ID                              0x004

#define ENN_BKG_COLOR                                   0x101214FF
#define ENN_WORKSPACES_BOX_COLOR                        0x151819FF
#define ENN_BUTTON_LIST_COLOR                           0x505050FF
#define ENN_TEXT_COLOR_WHITE                            0xFFFFFFFF
#define ENN_TEXT_COLOR_RED                              0xd75f5fFF
#define ENN_TEXT_COLOR_MUTED                            0x505050FF
#define ENN_SELECTED_WORKSPACE_COLOR                    0xFFFFFF30
#define ENN_HOVERED_WORKSPACE_COLOR                     0xFFFFFF15
#define ENN_SCROLLBAR_BG_COLOR                          0x202020FF
#define ENN_SCROLLBAR_DRAG_COLOR                        0x808080FF
#define ENN_SCROLLBAR_HANDLE_COLOR                      0x505050FF
#define ENN_TYPING_OVERLAY_COLOR                        0x00000080
#define ENN_PLACEHOLDER_TEXT_COLOR                      0x80808080

#define ENN_SAVE_DATA_FMT                               "LAST SAVE: %Y.%m.%d|%H:%M:%S"
#define ENN_SAVE_DATA_TEXT_HEIGHT                       0.035

#define ENN_INPUT_STRING_TEXT_HEIGHT                    0.2
#define ENN_CURSOR_CHANGE_TIME                          0.5

#define ENN_MAIN_BUTTON_COUNT                           4
#define ENN_BUTTON_TEXT_HEIGHT                          0.075
#define ENN_BUTTON_POS_X                                -0.85
#define ENN_BUTTON_SPACING                              0.1

#define ENN_WORKSPACE_ITEM_DIM_Y                        0.05
#define ENN_WORKSPACE_ITEM_SPACING                      0.11
#define ENN_WORKSPACE_ITEM_TEXT_HEIGHT                  0.05

#define ENN_WORKSPACES_BORDER_WIDTH                     0.015
#define ENN_SCROLLBAR_WIDTH                             0.03

#define ENN_SCREEN_MIN_COORD                            -1.0
#define ENN_SCREEN_MAX_COORD                            1.0

#define ENN_TITLE_TEXT_POS_X1                           -0.475
#define ENN_TITLE_TEXT_POS_Y1                           -0.75
#define ENN_TITLE_TEXT_POS_X2                           0.475
#define ENN_TITLE_TEXT_POS_Y2                           -0.65
#define ENN_TITLE_TEXT_HEIGHT                           0.1
#define ENN_TITLE_TEXT_STRING                           "SELECT A WORKSPACE"

#define ENN_ERROR_TEXT_HEIGHT                           0.05
#define ENN_ERROR_TEXT_POS_Y1                           0.4
#define ENN_ERROR_TEXT_POS_Y2                           0.5
#define ENN_ERROR_TEXT_STRING                           "ERROR: A WORKSPACE WITH THAT NAME ALREADY EXISTS"

#define ENN_PLACEHOLDER_TEXT_STRING                     ""

#define ENN_DOUBLE_CLICK_TIME                           0.3

#define ENN_WORKSPACE_BKG_COLOR                   0x000000B0
#define ENN_WORKSPACE_PANEL_COLOR                 0x101214FF
#define ENN_WORKSPACE_BORDER_COLOR                0x7a7c7e80
#define ENN_WORKSPACE_MUTED_TEXT_COLOR            0x80808080
#define ENN_WORKSPACE_PANEL_X1                   -0.55
#define ENN_WORKSPACE_PANEL_Y1                   -0.32
#define ENN_WORKSPACE_PANEL_X2                    0.55
#define ENN_WORKSPACE_PANEL_Y2                    0.32
#define ENN_WORKSPACE_TITLE_TEXT                  "NEW WORKSPACE"
#define ENN_WORKSPACE_CONFIRM_TEXT                "CREATE WORKSPACE"
#define ENN_WORKSPACE_BORDER_WIDTH                0.01
#define ENN_WORKSPACE_TITLE_HEIGHT                0.075
#define ENN_WORKSPACE_INPUT_HEIGHT                0.13
#define ENN_WORKSPACE_CONFIRM_X1                 -0.26
#define ENN_WORKSPACE_CONFIRM_Y1                  0.18
#define ENN_WORKSPACE_CONFIRM_X2                  0.26
#define ENN_WORKSPACE_CONFIRM_Y2                  0.245
#define ENN_WORKSPACE_CONFIRM_TEXT_HEIGHT         0.04
#define ENN_WORKSPACE_CONFIRM_HOVER_COLOR         0xFFFFFF20

static const f32vec4 workspaces_box = {
        .x = ENN_WORKSPACES_BOX_X,
        .y = ENN_WORKSPACES_BOX_Y,
        .z = ENN_WORKSPACES_BOX_Z,
        .w = ENN_WORKSPACES_BOX_W
};

ENNDEF_PUBLIC void workspace_layer_update_scroll_and_positions(void) {
        DEBUG_TRACE();
        f32 box_h = workspaces_box.w - workspaces_box.y;
        f32 visible_h = box_h - ENN_WORKSPACES_BORDER_WIDTH * 2.0;
        f32 content_h = vector_size(workspaces) * ENN_WORKSPACE_ITEM_SPACING;
        f32 min_offset = (content_h > visible_h) ? visible_h - content_h : 0.0;
        
        if (workspace_list_offset < min_offset) workspace_list_offset = min_offset;
        if (workspace_list_offset > 0.0) workspace_list_offset = 0.0;

        for (i32 i = workspaces.start; i < workspaces.end; ++i) {
                workspaces.data[i].pos = (f32vec2) {
                        .x = workspaces_box.x + ENN_WORKSPACES_BORDER_WIDTH,
                        .y = workspaces_box.y + ENN_WORKSPACES_BORDER_WIDTH + ENN_WORKSPACE_ITEM_SPACING * (i - workspaces.start) + workspace_list_offset
                };
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void workspace_layer_exit_typing_state(void) {
        DEBUG_TRACE();
        typing_state = false;
        vector_clear(input_string);
        name_conflict_error = false;
        hovered_confirm_button = false;
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC f32vec4 workspace_layer_confirm_rect(void) {
        return (f32vec4) {
                .x = ENN_WORKSPACE_CONFIRM_X1,
                .y = ENN_WORKSPACE_CONFIRM_Y1,
                .z = ENN_WORKSPACE_CONFIRM_X2 - ENN_WORKSPACE_CONFIRM_X1,
                .w = ENN_WORKSPACE_CONFIRM_Y2 - ENN_WORKSPACE_CONFIRM_Y1
        };
}

ENNDEF_PUBLIC void workspace_layer_start_typing_state(void) {
        DEBUG_TRACE();
        typing_state = true;
        input_string.end = input_string.start;
        if (input_string.capacity > 0) input_string.data[input_string.end] = 0;
        cursor_state = true;
        last_cursor_change = glfwGetTime();
        name_conflict_error = false;
        hovered_confirm_button = false;
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void workspace_layer_create_current_workspace(void) {
        DEBUG_TRACE();
        if (vector_size(input_string) == 0) {
                workspace_layer_exit_typing_state();
                DEBUG_UNTRACE();
                return;
        }

        bool conflict = false;
        for (i32 i = workspaces.start; i < workspaces.end; ++i) {
                if (strcmp(workspaces.data[i].workspace_name, input_string.data + input_string.start) == 0) {
                        conflict = true;
                        break;
                }
        }

        if (conflict) {
                name_conflict_error = true;
                DEBUG_UNTRACE();
                return;
        }

        name_conflict_error = false;
        char* path = calloc(strlen(ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits/") + strlen(input_string.data + input_string.start) + strlen(ENN_DATAFILE_FILE_EXTENSION) + 1, (sizeof (char)));
        sprintf(path, ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits/%s%s", input_string.data + input_string.start, ENN_DATAFILE_FILE_EXTENSION);

        file_write_cstring(path, "", 0);

        WorkspaceData new_ws;
        new_ws.dim = (f32vec2) { 0.0, ENN_WORKSPACE_ITEM_DIM_Y };
        new_ws.pos = (f32vec2) { 0.0, 0.0 };

        new_ws.workspace_name = calloc(strlen(input_string.data + input_string.start) + 1, (sizeof (char)));
        strcpy(new_ws.workspace_name, input_string.data + input_string.start);

        struct tm last_modified = *localtime(&(time_t) { file_get_date(path) } );
        new_ws.workspace_last_modified = calloc((sizeof ENN_SAVE_DATA_FMT) * 2, (sizeof (char)));
        strftime(new_ws.workspace_last_modified, (sizeof ENN_SAVE_DATA_FMT) * 2, ENN_SAVE_DATA_FMT, &last_modified);

        vector_push_back(workspaces, new_ws);
        vector_sort(workspaces, workspace_cmp, workspaces.start, workspaces.end);

        selected_workspace = NULL;
        hovered_workspace = NULL;

        workspace_layer_update_scroll_and_positions();

        free(path);
        workspace_layer_exit_typing_state();
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void workspace_layer_delete_selected(void) {
        DEBUG_TRACE();
        if (selected_workspace != NULL) {
                char* path = calloc(strlen(ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits/") + strlen(selected_workspace -> workspace_name) + strlen(ENN_DATAFILE_FILE_EXTENSION) + 1, (sizeof (char)));
                sprintf(path, ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits/%s%s", selected_workspace -> workspace_name, ENN_DATAFILE_FILE_EXTENSION);
                file_remove(path);
                free(path);

                free(selected_workspace -> workspace_name);
                free(selected_workspace -> workspace_last_modified);
                
                if (selected_workspace == last_clicked_workspace) {
                        last_clicked_workspace = NULL;
                }

                vector_remove_at_address_keep_order(workspaces, selected_workspace);
                selected_workspace = NULL;
                hovered_workspace = NULL;

                workspace_layer_update_scroll_and_positions();
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void workspace_layer_open_selected(void) {
        DEBUG_TRACE();
        if (selected_workspace != NULL) {
                char* path = calloc(strlen(ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits/") + strlen(selected_workspace -> workspace_name) + strlen(ENN_DATAFILE_FILE_EXTENSION) + 1, (sizeof (char)));
                sprintf(path, ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits/%s%s", selected_workspace -> workspace_name, ENN_DATAFILE_FILE_EXTENSION);
                game_start(path);
                free(path);
                layer_set_inactive(workspace_layer_id);
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC WorkspaceData* workspace_layer_get_workspace_at(f32vec2 ndc) {
        DEBUG_TRACE();
        if (ndc.y >= workspaces_box.y + ENN_WORKSPACES_BORDER_WIDTH && ndc.y <= workspaces_box.w - ENN_WORKSPACES_BORDER_WIDTH) {
                for (i32 i = workspaces.start; i < workspaces.end; ++i) {
                        if (is_inside_rectangle(
                                ndc,
                                (f32vec4){
                                    workspaces_box.x + ENN_WORKSPACES_BORDER_WIDTH,
                                    workspaces.data[i].pos.y,
                                    (workspaces_box.z - ENN_WORKSPACES_BORDER_WIDTH - ENN_SCROLLBAR_WIDTH) - (workspaces_box.x + ENN_WORKSPACES_BORDER_WIDTH),
                                    workspaces.data[i].dim.y + ENN_SAVE_DATA_TEXT_HEIGHT}))
                        {
                                DEBUG_UNTRACE();
                                return &workspaces.data[i];
                        }
                }
        }
        DEBUG_UNTRACE();
        return NULL;
}

void workspace_layer_init(void) {
        DEBUG_TRACE();
        
        selected_workspace = NULL;
        hovered_workspace = NULL;
        last_clicked_workspace = NULL;
        last_workspace_click_time = 0.0;

        ui_text_button_list_init(
                &buttons, ENN_LEFT_ALIGN, ENN_BUTTON_LIST_COLOR,
                (UITextButtonData[]) {
                        (UITextButtonData) { 
                                .id             = ENN_CREATE_WORKSPACE_BUTTON_ID,
                                .pos            = { ENN_BUTTON_POS_X, workspaces_box.y + ENN_BUTTON_SPACING * 1 },
                                .color          = ENN_TEXT_COLOR_WHITE,
                                .text           = "NEW WORKSPACE",
                                .text_height    = ENN_BUTTON_TEXT_HEIGHT
                        },
                        (UITextButtonData) {
                                .id             = ENN_DELETE_WORKSPACE_BUTTON_ID,
                                .pos            = { ENN_BUTTON_POS_X, workspaces_box.y + ENN_BUTTON_SPACING * 2},
                                .color          = ENN_TEXT_COLOR_WHITE,
                                .text           = "DELETE WORKSPACE",
                                .text_height    = ENN_BUTTON_TEXT_HEIGHT
                        },
                        (UITextButtonData) {
                                .id             = ENN_OPEN_WORKSPACE_BUTTON_ID,
                                .pos            = { ENN_BUTTON_POS_X, workspaces_box.y + ENN_BUTTON_SPACING * 3 },
                                .color          = ENN_TEXT_COLOR_WHITE,
                                .text           = "OPEN WORKSPACE",
                                .text_height    = ENN_BUTTON_TEXT_HEIGHT
                        },
                        (UITextButtonData) {
                                .id             = ENN_BACK_BUTTON_ID,
                                .pos            = { ENN_BUTTON_POS_X, workspaces_box.y + ENN_BUTTON_SPACING * 4 },
                                .color          = ENN_TEXT_COLOR_RED,
                                .text           = "BACK",
                                .text_height    = ENN_BUTTON_TEXT_HEIGHT
                        }
                },
                ENN_MAIN_BUTTON_COUNT
        );

        directory_create(ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits");

        DIR* workspace_dir = directory_open(ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits");
        DirEntry* workspace_entry = NULL;
        while ((workspace_entry = directory_read(workspace_dir))) {
                WorkspaceData data;
                char* name = workspace_entry -> d_name;
                char* extension = strstr(name, ENN_DATAFILE_FILE_EXTENSION);

                if (extension == 0) continue ;

                data.dim = (f32vec2) { 0.0, ENN_WORKSPACE_ITEM_DIM_Y };

                char* full_path = calloc((sizeof (ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits/")) + workspace_entry ->d_namlen, (sizeof (char)));
                sprintf(full_path, ENN_APP_DIRECTORY ENN_DATA_PATH "/Circuits/%s", workspace_entry -> d_name);
                struct tm last_modified = *localtime(&(time_t) { file_get_date(full_path) } );
                free(full_path);

                data.workspace_name = calloc(extension - workspace_entry -> d_name + 1, (sizeof (char)));
                memcpy(data.workspace_name, (char*)workspace_entry -> d_name, (sizeof (char)) * (extension - workspace_entry -> d_name));

                data.workspace_last_modified = calloc((sizeof ENN_SAVE_DATA_FMT) * 2, (sizeof (char)));
                strftime(data.workspace_last_modified, (sizeof ENN_SAVE_DATA_FMT) * 2, ENN_SAVE_DATA_FMT, &last_modified);

                vector_push_back(workspaces, data);
        }
        directory_close(workspace_dir);

        vector_sort(workspaces, workspace_cmp, workspaces.start, workspaces.end);
        workspace_layer_update_scroll_and_positions();

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
        selected_workspace = NULL;
        hovered_workspace = NULL;
        last_clicked_workspace = NULL;
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
                (f32vec2) { ENN_SCREEN_MIN_COORD, ENN_SCREEN_MIN_COORD },
                (f32vec2) { ENN_SCREEN_MAX_COORD, ENN_SCREEN_MAX_COORD },
                ENN_BKG_COLOR
        );

        render_rectangle_push(
                (f32vec2) { workspaces_box.x, workspaces_box.y },
                (f32vec2) { workspaces_box.z, workspaces_box.w },
                ENN_WORKSPACES_BOX_COLOR
        );

        for (i32 i = workspaces.start; i < workspaces.end; ++i) {
                render_text_push(
                        workspaces.data[i].pos,
                        workspaces.data[i].pos,
                        workspaces.data[i].workspace_name, ENN_TEXT_COLOR_WHITE, ENN_WORKSPACE_ITEM_TEXT_HEIGHT, ENN_LEFT_ALIGN
                );

                render_text_push(
                        (f32vec2) { workspaces.data[i].pos.x, workspaces.data[i].pos.y + workspaces.data[i].dim.y },
                        (f32vec2) { workspaces.data[i].pos.x, workspaces.data[i].pos.y + workspaces.data[i].dim.y },
                        workspaces.data[i].workspace_last_modified, ENN_TEXT_COLOR_MUTED, ENN_SAVE_DATA_TEXT_HEIGHT, ENN_LEFT_ALIGN
                );
        }

        if (hovered_workspace != NULL && hovered_workspace != selected_workspace) {
                render_rectangle_push(
                        (f32vec2) { workspaces_box.x + ENN_WORKSPACES_BORDER_WIDTH, hovered_workspace -> pos.y },
                        (f32vec2) { workspaces_box.z - ENN_WORKSPACES_BORDER_WIDTH - ENN_SCROLLBAR_WIDTH, hovered_workspace -> pos.y + hovered_workspace -> dim.y + ENN_SAVE_DATA_TEXT_HEIGHT },
                        ENN_HOVERED_WORKSPACE_COLOR
                );
        }

        if (selected_workspace != NULL) {
                render_rectangle_push(
                        (f32vec2) { workspaces_box.x + ENN_WORKSPACES_BORDER_WIDTH, selected_workspace -> pos.y },
                        (f32vec2) { workspaces_box.z - ENN_WORKSPACES_BORDER_WIDTH - ENN_SCROLLBAR_WIDTH, selected_workspace -> pos.y + selected_workspace -> dim.y + ENN_SAVE_DATA_TEXT_HEIGHT },
                        ENN_SELECTED_WORKSPACE_COLOR
                );
        }

        render_rectangle_push(
                (f32vec2) { workspaces_box.x, workspaces_box.y },
                (f32vec2) { workspaces_box.z, workspaces_box.y + ENN_WORKSPACES_BORDER_WIDTH * ENN_FRAMEBUFF_ASPECT_RATIO },
                ENN_WORKSPACES_BOX_COLOR
        );
        render_rectangle_push(
                (f32vec2) { workspaces_box.x, workspaces_box.w - ENN_WORKSPACES_BORDER_WIDTH * ENN_FRAMEBUFF_ASPECT_RATIO },
                (f32vec2) { workspaces_box.z, workspaces_box.w },
                ENN_WORKSPACES_BOX_COLOR
        );
        render_rectangle_push(
                (f32vec2) { workspaces_box.x, workspaces_box.y },
                (f32vec2) { workspaces_box.x + ENN_WORKSPACES_BORDER_WIDTH, workspaces_box.w },
                ENN_WORKSPACES_BOX_COLOR
        );
        render_rectangle_push(
                (f32vec2) { workspaces_box.z - ENN_WORKSPACES_BORDER_WIDTH, workspaces_box.y },
                (f32vec2) { workspaces_box.z, workspaces_box.w },
                ENN_WORKSPACES_BOX_COLOR
        );

        f32 box_h = workspaces_box.w - workspaces_box.y;
        f32 visible_h = box_h - ENN_WORKSPACES_BORDER_WIDTH * 2.0;
        f32 content_h = vector_size(workspaces) * ENN_WORKSPACE_ITEM_SPACING;
        f32 min_offset = (content_h > visible_h) ? visible_h - content_h : 0.0;
        
        f32 handle_ratio = (content_h > 0.0) ? (visible_h / content_h) : 1.0;
        if (handle_ratio > 1.0) handle_ratio = 1.0;
        f32 handle_h = visible_h * handle_ratio;
        f32 scroll_ratio = (min_offset < 0.0) ? (workspace_list_offset / min_offset) : 0.0;
        f32 handle_y = workspaces_box.y + ENN_WORKSPACES_BORDER_WIDTH + scroll_ratio * (visible_h - handle_h);

        render_rectangle_push(
                (f32vec2) { workspaces_box.z - ENN_WORKSPACES_BORDER_WIDTH - ENN_SCROLLBAR_WIDTH, workspaces_box.y + ENN_WORKSPACES_BORDER_WIDTH },
                (f32vec2) { workspaces_box.z - ENN_WORKSPACES_BORDER_WIDTH, workspaces_box.w - ENN_WORKSPACES_BORDER_WIDTH },
                ENN_SCROLLBAR_BG_COLOR
        );

        render_rectangle_push(
                (f32vec2) { workspaces_box.z - ENN_WORKSPACES_BORDER_WIDTH - ENN_SCROLLBAR_WIDTH, handle_y },
                (f32vec2) { workspaces_box.z - ENN_WORKSPACES_BORDER_WIDTH, handle_y + handle_h },
                is_dragging_scrollbar ? ENN_SCROLLBAR_DRAG_COLOR : ENN_SCROLLBAR_HANDLE_COLOR
        );

        render_rectangle_push(
                (f32vec2) { ENN_SCREEN_MIN_COORD, ENN_SCREEN_MIN_COORD },
                (f32vec2) { workspaces_box.x, ENN_SCREEN_MAX_COORD },
                ENN_BKG_COLOR
        );

        render_rectangle_push(
                (f32vec2) { workspaces_box.x, ENN_SCREEN_MIN_COORD },
                (f32vec2) { ENN_SCREEN_MAX_COORD, workspaces_box.y },
                ENN_BKG_COLOR
        );

        render_rectangle_push(
                (f32vec2) { workspaces_box.x, workspaces_box.w },
                (f32vec2) { ENN_SCREEN_MAX_COORD, ENN_SCREEN_MAX_COORD },
                ENN_BKG_COLOR
        );

        render_rectangle_push(
                (f32vec2) { workspaces_box.z, workspaces_box.y },
                (f32vec2) { ENN_SCREEN_MAX_COORD, workspaces_box.w },
                ENN_BKG_COLOR
        );

        ui_text_button_list_render(&buttons);

        render_text_push(
                (f32vec2) { ENN_TITLE_TEXT_POS_X1, ENN_TITLE_TEXT_POS_Y1 },
                (f32vec2) { ENN_TITLE_TEXT_POS_X2, ENN_TITLE_TEXT_POS_Y2 },
                ENN_TITLE_TEXT_STRING, ENN_TEXT_COLOR_WHITE, ENN_TITLE_TEXT_HEIGHT, ENN_CENTER_ALIGN
        );

        if (typing_state) {
                render_rectangle_push(
                        (f32vec2) { ENN_SCREEN_MIN_COORD, ENN_SCREEN_MIN_COORD },
                        (f32vec2) { ENN_SCREEN_MAX_COORD, ENN_SCREEN_MAX_COORD },
                        ENN_WORKSPACE_BKG_COLOR
                );
                render_rectangle_push(
                        (f32vec2) { ENN_WORKSPACE_PANEL_X1 - ENN_WORKSPACE_BORDER_WIDTH, ENN_WORKSPACE_PANEL_Y1 - ENN_WORKSPACE_BORDER_WIDTH * ENN_FRAMEBUFF_ASPECT_RATIO },
                        (f32vec2) { ENN_WORKSPACE_PANEL_X2 + ENN_WORKSPACE_BORDER_WIDTH, ENN_WORKSPACE_PANEL_Y2 + ENN_WORKSPACE_BORDER_WIDTH * ENN_FRAMEBUFF_ASPECT_RATIO },
                        ENN_WORKSPACE_BORDER_COLOR
                );
                render_rectangle_push(
                        (f32vec2) { ENN_WORKSPACE_PANEL_X1, ENN_WORKSPACE_PANEL_Y1 },
                        (f32vec2) { ENN_WORKSPACE_PANEL_X2, ENN_WORKSPACE_PANEL_Y2 },
                        ENN_WORKSPACE_PANEL_COLOR
                );

                render_text_push(
                        (f32vec2) { ENN_WORKSPACE_PANEL_X1, -0.23 },
                        (f32vec2) { ENN_WORKSPACE_PANEL_X2, -0.15 },
                        ENN_WORKSPACE_TITLE_TEXT,
                        ENN_TEXT_COLOR_WHITE,
                        ENN_WORKSPACE_TITLE_HEIGHT,
                        ENN_CENTER_ALIGN
                );

                f64 time = glfwGetTime();
                if (time - last_cursor_change >= ENN_CURSOR_CHANGE_TIME) {
                        cursor_state = !cursor_state;
                        last_cursor_change = time;
                }

                f32 render_text_ratio = ((f32)global_render.font_atlas.char_dim.x / (f32)global_render.font_atlas.char_dim.y);
                f32 text_width = vector_size(input_string) * ENN_WORKSPACE_INPUT_HEIGHT * render_text_ratio;

                f32vec2 text_pos1 = { ENN_WORKSPACE_PANEL_X1 + 0.08, -0.08 };
                f32vec2 text_pos2 = { ENN_WORKSPACE_PANEL_X2 - 0.08, 0.07 };

                if (vector_size(input_string) > 0) {
                        render_text_push(
                                text_pos1,
                                text_pos2,
                                input_string.data + input_string.start,
                                ENN_TEXT_COLOR_WHITE,
                                ENN_WORKSPACE_INPUT_HEIGHT,
                                ENN_CENTER_ALIGN
                        );
                } else {
                        render_text_push(
                                text_pos1,
                                text_pos2,
                                "NAME",
                                ENN_WORKSPACE_MUTED_TEXT_COLOR,
                                ENN_WORKSPACE_INPUT_HEIGHT,
                                ENN_CENTER_ALIGN
                        );
                }

                if (cursor_state) {
                        f32 cursor_x = text_width * 0.5 + ENN_WORKSPACE_INPUT_HEIGHT * render_text_ratio * 0.25;
                        render_rectangle_push(
                                (f32vec2) { cursor_x, text_pos1.y },
                                (f32vec2) { cursor_x + ENN_WORKSPACE_INPUT_HEIGHT * render_text_ratio * 0.25, text_pos2.y },
                                ENN_TEXT_COLOR_WHITE
                        );
                }

                // f32vec4 confirm_rect = workspace_layer_confirm_rect();
                // render_rectangle_push(
                //         (f32vec2) { confirm_rect.x - ENN_WORKSPACE_BORDER_WIDTH, confirm_rect.y - ENN_WORKSPACE_BORDER_WIDTH * ENN_FRAMEBUFF_ASPECT_RATIO },
                //         (f32vec2) { confirm_rect.x + confirm_rect.z + ENN_WORKSPACE_BORDER_WIDTH, confirm_rect.y + confirm_rect.w + ENN_WORKSPACE_BORDER_WIDTH * ENN_FRAMEBUFF_ASPECT_RATIO },
                //         ENN_WORKSPACE_BORDER_COLOR
                // );
                // render_rectangle_push(
                //         (f32vec2) { confirm_rect.x, confirm_rect.y },
                //         (f32vec2) { confirm_rect.x + confirm_rect.z, confirm_rect.y + confirm_rect.w },
                //         hovered_confirm_button ? ENN_WORKSPACE_CONFIRM_HOVER_COLOR : ENN_WORKSPACE_PANEL_COLOR
                // );
                // render_text_push(
                //         (f32vec2) { confirm_rect.x, confirm_rect.y + (confirm_rect.w - ENN_WORKSPACE_CONFIRM_TEXT_HEIGHT) * 0.5 },
                //         (f32vec2) { confirm_rect.x + confirm_rect.z, confirm_rect.y + (confirm_rect.w + ENN_WORKSPACE_CONFIRM_TEXT_HEIGHT) * 0.5 },
                //         ENN_WORKSPACE_CONFIRM_TEXT,
                //         hovered_confirm_button ? ENN_TEXT_COLOR_MUTED : ENN_TEXT_COLOR_WHITE,
                //         ENN_WORKSPACE_CONFIRM_TEXT_HEIGHT,
                //         ENN_CENTER_ALIGN
                // );

                if (name_conflict_error) {
                        render_text_push(
                                (f32vec2) { ENN_WORKSPACE_PANEL_X1, 0.27 },
                                (f32vec2) { ENN_WORKSPACE_PANEL_X2, 0.31 },
                                ENN_ERROR_TEXT_STRING,
                                ENN_TEXT_COLOR_RED,
                                ENN_ERROR_TEXT_HEIGHT,
                                ENN_CENTER_ALIGN
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
                        if (data -> button == GLFW_MOUSE_BUTTON_LEFT) {
                                if (data -> action == GLFW_PRESS) {
                                        f32vec2 ndc = screen_to_ndc((f32vec2) { global_state.mouse_pos.x, global_state.mouse_pos.y });
                                        if (typing_state) {
                                                f32vec4 panel_rect = {
                                                        ENN_WORKSPACE_PANEL_X1,
                                                        ENN_WORKSPACE_PANEL_Y1,
                                                        ENN_WORKSPACE_PANEL_X2 - ENN_WORKSPACE_PANEL_X1,
                                                        ENN_WORKSPACE_PANEL_Y2 - ENN_WORKSPACE_PANEL_Y1
                                                };
                                                if (is_inside_rectangle(ndc, workspace_layer_confirm_rect()))
                                                        workspace_layer_create_current_workspace();
                                                else if (!is_inside_rectangle(ndc, panel_rect))
                                                        workspace_layer_exit_typing_state();
                                                break;
                                        }

                                        f32 box_h = workspaces_box.w - workspaces_box.y;
                                        f32 visible_h = box_h - ENN_WORKSPACES_BORDER_WIDTH * 2.0;
                                        f32 content_h = vector_size(workspaces) * ENN_WORKSPACE_ITEM_SPACING;
                                        f32 min_offset = (content_h > visible_h) ? visible_h - content_h : 0.0;

                                        if (min_offset < 0.0) {
                                                f32 handle_ratio = visible_h / content_h;
                                                if (handle_ratio > 1.0) handle_ratio = 1.0;
                                                f32 handle_h = visible_h * handle_ratio;
                                                f32 scroll_ratio = (workspace_list_offset / min_offset);
                                                f32 handle_y = workspaces_box.y + ENN_WORKSPACES_BORDER_WIDTH + scroll_ratio * (visible_h - handle_h);

                                                if (ndc.x >= workspaces_box.z - ENN_WORKSPACES_BORDER_WIDTH - ENN_SCROLLBAR_WIDTH && ndc.x <= workspaces_box.z - ENN_WORKSPACES_BORDER_WIDTH &&
                                                    ndc.y >= handle_y && ndc.y <= handle_y + handle_h) {
                                                        is_dragging_scrollbar = true;
                                                        break;
                                                }
                                        }

                                        if (buttons.hover != NULL) {
                                                switch (buttons.hover -> id) {
                                                        case ENN_CREATE_WORKSPACE_BUTTON_ID:
                                                        {
                                                                workspace_layer_start_typing_state();
                                                                break;
                                                        }
                                                        case ENN_BACK_BUTTON_ID:
                                                        {
                                                                layer_set_active(menu_layer_id);
                                                                layer_set_inactive(workspace_layer_id);
                                                                break;
                                                        }
                                                        case ENN_DELETE_WORKSPACE_BUTTON_ID:
                                                        {
                                                                workspace_layer_delete_selected();
                                                                break;
                                                        }
                                                        case ENN_OPEN_WORKSPACE_BUTTON_ID:
                                                        {
                                                                workspace_layer_open_selected();
                                                                break;
                                                        }
                                                        default: break;
                                                }
                                        }

                                        WorkspaceData* clicked = workspace_layer_get_workspace_at(ndc);
                                        if (clicked != NULL) {
                                                f64 current_time = glfwGetTime();
                                                if (clicked == last_clicked_workspace && (current_time - last_workspace_click_time) < ENN_DOUBLE_CLICK_TIME) {
                                                        selected_workspace = clicked;
                                                        workspace_layer_open_selected();
                                                } else {
                                                        selected_workspace = clicked;
                                                        last_clicked_workspace = clicked;
                                                        last_workspace_click_time = current_time;
                                                }
                                        }
                                } else if (data -> action == GLFW_RELEASE) {
                                        is_dragging_scrollbar = false;
                                }
                        }
                        break;
                }
                case ENN_INPUT_MOUSE_MOVE_EVENT:
                {
                        f64vec2* data = event -> data;
                        f32vec2 ndc = screen_to_ndc((f32vec2) { data -> x, data -> y });

                        if (typing_state) {
                                hovered_confirm_button = is_inside_rectangle(ndc, workspace_layer_confirm_rect());
                        } else {
                                if (is_dragging_scrollbar) {
                                        f32 box_h = workspaces_box.w - workspaces_box.y;
                                        f32 visible_h = box_h - ENN_WORKSPACES_BORDER_WIDTH * 2.0;
                                        f32 content_h = vector_size(workspaces) * ENN_WORKSPACE_ITEM_SPACING;
                                        f32 min_offset = (content_h > visible_h) ? visible_h - content_h : 0.0;

                                        if (min_offset < 0.0) {
                                                f32 handle_ratio = visible_h / content_h;
                                                if (handle_ratio > 1.0) handle_ratio = 1.0;
                                                f32 handle_h = visible_h * handle_ratio;

                                                f32 top_bound = workspaces_box.y + ENN_WORKSPACES_BORDER_WIDTH;
                                                f32 bottom_bound = workspaces_box.w - ENN_WORKSPACES_BORDER_WIDTH;

                                                f32 handle_y = ndc.y - handle_h / 2.0;
                                                if (handle_y < top_bound) handle_y = top_bound;
                                                if (handle_y > bottom_bound - handle_h) handle_y = bottom_bound - handle_h;

                                                f32 scroll_ratio = (visible_h > handle_h) ? (handle_y - top_bound) / (visible_h - handle_h) : 0.0;
                                                workspace_list_offset = scroll_ratio * min_offset;

                                                workspace_layer_update_scroll_and_positions();
                                        }
                                }

                                ui_text_button_list_check_hover(&buttons, ndc);
                                hovered_workspace = workspace_layer_get_workspace_at(ndc);
                        }
                        break;
                }
                case ENN_INPUT_KEY_EVENT:
                {
                        struct { i32 key, action; }* data = event -> data;
                        if (data -> key == GLFW_KEY_ESCAPE && data -> action == GLFW_PRESS) {
                                if (typing_state) {
                                        workspace_layer_exit_typing_state();
                                } else {
                                        layer_set_active(menu_layer_id);
                                        layer_set_inactive(workspace_layer_id);
                                }
                        }
                        if (data -> key == GLFW_KEY_DELETE && data -> action == GLFW_PRESS) {
                                if (!typing_state) {
                                        workspace_layer_delete_selected();
                                }
                        }
                        if (data -> key == GLFW_KEY_BACKSPACE && (data -> action == GLFW_PRESS || data -> action == GLFW_REPEAT)) {
                                if (typing_state) {
                                        if (vector_size(input_string) > 0) {
                                                vector_pop_back(input_string);
                                                input_string.data[input_string.end] = 0;
                                                cursor_state = true;
                                                last_cursor_change = glfwGetTime();
                                                name_conflict_error = false;
                                        }
                                }
                        }
                        if (data -> key == GLFW_KEY_ENTER && data -> action == GLFW_PRESS) {
                                if (typing_state)
                                        workspace_layer_create_current_workspace();
                        }
                        break;
                }
                case ENN_INPUT_TEXT_EVENT:
                {
                        if (typing_state) {
                                u32* code = event -> data;
                                if (*code >= ENN_FONT_ATLAS_FIRST_CHAR && *code <= ENN_FONT_ATLAS_LAST_CHAR) {
                                        char ch = (char)*code;
                                        vector_push_back(input_string, ch);
                                        input_string.data[input_string.end] = 0;
                                        cursor_state = true;
                                        last_cursor_change = glfwGetTime();
                                        name_conflict_error = false;
                                }
                        }
                        break;
                }
                case ENN_INPUT_MOUSE_SCROLL_EVENT:
                {
                        if (!typing_state) {
                                f32vec2 ndc = screen_to_ndc((f32vec2) { global_state.mouse_pos.x, global_state.mouse_pos.y });
                                if (ndc.x >= workspaces_box.x && ndc.x <= workspaces_box.z &&
                                    ndc.y >= workspaces_box.y && ndc.y <= workspaces_box.w) {
                                        f64* offset = event -> data;
                                        f32 box_h = workspaces_box.w - workspaces_box.y;
                                        f32 visible_h = box_h - ENN_WORKSPACES_BORDER_WIDTH * 2.0;
                                        f32 content_h = vector_size(workspaces) * ENN_WORKSPACE_ITEM_SPACING;
                                        f32 min_offset = (content_h > visible_h) ? visible_h - content_h : 0.0;

                                        if (min_offset < 0.0) {
                                                workspace_list_offset += ENN_WORKSPACE_LIST_SCROLL_CHANGE * (*offset);
                                                workspace_layer_update_scroll_and_positions();
                                        }
                                }
                        }
                        break;
                }
                default: break;
        }
        event -> handled = true;
        DEBUG_UNTRACE();
}
