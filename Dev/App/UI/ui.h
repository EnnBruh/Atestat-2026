#ifndef UI_H
#define UI_H

#include "Rendering/render.h"

typedef i32 UITextButtonID;
typedef struct UITextButton {
        UITextButtonID  id;
        f32vec2         pos;
        f32vec2         dim;
        char*           text;
        u32             color;
} UITextButton;

ENNDEF_PUBLIC bool ui_text_button_under_pos(UITextButton* button, f32vec2 pos) {
        DEBUG_TRACE();
        DEBUG_ASSERT(button != NULL);
        DEBUG_UNTRACE();
        return button -> pos.x <= pos.x && button -> pos.x + button -> dim.x >= pos.x &&
               button -> pos.y <= pos.y && button -> pos.y + button -> dim.y >= pos.y;
}

typedef struct UITextButtonList {
        vector(UITextButton)    list;
        UITextButton*           hover;
        u32                     button_hover_color;
        ENN_TEXT_ALIGN          align;
} UITextButtonList;

ENNDEF_PUBLIC void ui_text_button_list_render(UITextButtonList* list) {
        DEBUG_TRACE();
        DEBUG_ASSERT(list != NULL);

        for (i32 i = list -> list.start; i < list -> list.end; ++i) 
                if (&list -> list.data[i] != list -> hover) render_text_push(list -> list.data[i].pos, (f32vec2) { list -> list.data[i].pos.x + list -> list.data[i].dim.x, list -> list.data[i].pos.y + list -> list.data[i].dim.y }, list -> list.data[i].text, list -> list.data[i].color, list -> list.data[i].dim.y, list -> align);
                else render_text_push(list -> list.data[i].pos, (f32vec2) { list -> list.data[i].pos.x + list -> list.data[i].dim.x, list -> list.data[i].pos.y + list -> list.data[i].dim.y }, list -> list.data[i].text, list -> button_hover_color, list -> list.data[i].dim.y, list -> align);


        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void ui_text_button_list_check_hover(UITextButtonList* list, f32vec2 pos) {
        DEBUG_TRACE();
        DEBUG_ASSERT(list != NULL);

        list -> hover = NULL;
        for (i32 i = list -> list.start; i < list -> list.end; ++i)
                if (ui_text_button_under_pos(&list -> list.data[i], pos)) {
                        list -> hover = &list -> list.data[i];
                        DEBUG_UNTRACE();
                        return ;
                }


        DEBUG_UNTRACE();
}

typedef struct UITextButtonData {
        UITextButtonID  id;
        f32vec2         pos;
        u32             color;
        char*           text;
        f32             text_height;
} UITextButtonData;

ENNDEF_PUBLIC void ui_text_button_list_init(UITextButtonList* list, ENN_TEXT_ALIGN text_align, u32 button_hover_color, UITextButtonData buttons[], i32 num_buttons) {
        DEBUG_TRACE();
        DEBUG_ASSERT(list != NULL);
        list -> align = text_align;
        list -> button_hover_color = button_hover_color;
        vector_reserve(list -> list, num_buttons);

        UITextButton button; 
        i32 button_text_len = 0;


        f32 render_text_ratio = ((f32)global_render.font_atlas.char_dim.x / (f32)global_render.font_atlas.char_dim.y);
        for (i32 i = 0; i < num_buttons; ++i) {
                button.id    = buttons[i].id;
                button.color = buttons[i].color;

                button_text_len = strlen(buttons[i].text);
                button.text = calloc(button_text_len + 1, (sizeof (char)));
                memcpy(button.text, buttons[i].text, button_text_len * (sizeof (char)));
                
                switch (text_align) {
                        case ENN_LEFT_ALIGN: 
                        {
                                button.pos = buttons[i].pos;
                                button.dim.y = buttons[i].text_height;
                                button.dim.x = button_text_len * buttons[i].text_height * render_text_ratio;
                                break;
                        }
                        case ENN_RIGHT_ALIGN: 
                        {
                                button.pos.x = buttons[i].pos.x - button_text_len * buttons[i].text_height * render_text_ratio;
                                button.pos.y = buttons[i].pos.y;
                                button.dim.y = buttons[i].text_height;
                                button.dim.x = button_text_len * buttons[i].text_height * render_text_ratio;
                                break;
                        }
                        case ENN_CENTER_ALIGN:
                        {
                                button.pos.x = buttons[i].pos.x - button_text_len * buttons[i].text_height * render_text_ratio * 0.5;
                                button.pos.y = buttons[i].pos.y;
                                button.dim.y = buttons[i].text_height;
                                button.dim.x = button_text_len * buttons[i].text_height * render_text_ratio;
                                break;
                        }
                }
                vector_push_back(list -> list, button);
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void ui_text_button_list_term(UITextButtonList* list) {
        DEBUG_TRACE();
        DEBUG_ASSERT(list != NULL);

        for (i32 i = list -> list.start; i < list -> list.end; ++i) {
                free(list -> list.data[i].text);
        }
        vector_destroy(list -> list);

        memset(list, 0x0, (sizeof (UITextButtonList)));
        DEBUG_UNTRACE();
}

#endif