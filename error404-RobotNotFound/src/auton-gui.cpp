// selector.cpp
// 2915X
// 2020-2021 VRC Change Up

#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_btn.h"
#include "main.h"

int count;

void displayImage() {
	
}

namespace autoSelection {
	// helper function which handles button events
	static lv_res_t EventHelper(lv_obj_t * btn)
	{
			lv_btn_toggle(btn);

            if(lv_btn_get_state(btn)) {
                count = lv_obj_get_free_num(btn);
            }
            else if(!lv_btn_get_state(btn)) {
                count = 0;
            }

		printf("%d\n", count);	// print that buttons state for debug purposes
	    return LV_RES_OK; // return that button wasn't deleted (because lvgl 5.3)
	}

	void autoGUI(void) {

		// title label
		lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);
		lv_label_set_text(label, "2915X Nationals Auton Selector");
		lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 2); // lv_obj_align(, const lv_obj_t *base, lv_align_t align, lv_coord_t x_mod, lv_coord_t y_mod);

		// button objects
		lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);	// no auton
		lv_obj_t * btn2 = lv_btn_create(lv_scr_act(), NULL);	// left 1 ball

		// set size for 1 and 2 (they are template buttons)
		lv_obj_set_size(btn1, 460, 45);
		lv_obj_set_size(btn2, 225, 45);

		lv_obj_t * btn3 = lv_btn_create(lv_scr_act(), btn2);	// left 2 ball
		lv_obj_t * btn4 = lv_btn_create(lv_scr_act(), btn2);	// right 1 ball
		lv_obj_t * btn5 = lv_btn_create(lv_scr_act(), btn2);	// right 2 ball


		// set numerical id
		lv_obj_set_free_num(btn1, 1);
		lv_obj_set_free_num(btn2, 2);
		lv_obj_set_free_num(btn3, 3);
		lv_obj_set_free_num(btn4, 4);
		lv_obj_set_free_num(btn5, 5);

        // button labels
		label = lv_label_create(btn1, NULL);						// create the label
		lv_label_set_text(label, "No auton - you're useless >:)");	// set the label text
		label = lv_label_create(btn2, NULL);
		lv_label_set_text(label, "Left 1 Ball");
		label = lv_label_create(btn3, NULL);
		lv_label_set_text(label, "Left 2 Ball");
		label = lv_label_create(btn4, NULL);
		lv_label_set_text(label, "Right 1 Ball");
		label = lv_label_create(btn5, NULL);
		lv_label_set_text(label, "Right 2 Ball");

		// set button positions
		// horizton pos (px), vertical pos (px)
		lv_obj_set_pos(btn1, 10, 45);
		lv_obj_set_pos(btn2, 10, 100);
		lv_obj_set_pos(btn3, 245, 100);
		lv_obj_set_pos(btn4, 10, 155);
		lv_obj_set_pos(btn5, 245, 155);

		// button actions
		lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, EventHelper);
		lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, EventHelper);
		lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, EventHelper);
		lv_btn_set_action(btn4, LV_BTN_ACTION_CLICK, EventHelper);
		lv_btn_set_action(btn5, LV_BTN_ACTION_CLICK, EventHelper);
	}
}