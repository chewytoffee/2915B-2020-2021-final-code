#include "main.h"
#include "custom\auton-gui.h"

	bool buttons[4];

	static lv_res_t EventHelper(lv_obj_t * btn)
	{
		// store button index as int
	    uint8_t id = lv_obj_get_free_num(btn);
			lv_btn_toggle(btn);

			// update the state of the button in bool array
			buttons[id-1] = lv_btn_get_state(btn);
			printf("%d\n",buttons[id-1]);	// print that buttons state for debug purposes
	    return LV_RES_OK; // return that button wasn't deleted (because lvgl 5.3)
	}

	void autoSelection::autoGUI(void) {

		/*
		 *	TITLE LABEL
		 */
		lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);
		lv_label_set_text(label, "Auton Selector");
		lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 2); // lv_obj_align(, const lv_obj_t *base, lv_align_t align, lv_coord_t x_mod, lv_coord_t y_mod);

		/*
		 *	Button One
		 */
		lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
		lv_obj_set_size(btn1, 150, 45);
		lv_obj_set_pos(btn1, 165, 45);
		lv_obj_set_free_num(btn1, 1);   /*Set a unique number for the button*/
		lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, EventHelper);
		// make the button text
		label = lv_label_create(btn1, NULL);
		lv_label_set_text(label, "Middle Center");

		/*
		 *	Create a new button using Button One as the template
		 */
		lv_obj_t * btn2 = lv_btn_create(lv_scr_act(), btn1);
		lv_obj_set_pos(btn2, 5, 100);
		lv_obj_set_free_num(btn2, 2);
		// make button text
		label = lv_label_create(btn2, NULL);
		lv_label_set_text(label, "Left Home Row");
		//
		// button 3
		//
		lv_obj_t * btn3 = lv_btn_create(lv_scr_act(), btn1);
		lv_obj_set_pos(btn3, 165, 100);
		lv_obj_set_free_num(btn3, 3);
		// make button text
		label = lv_label_create(btn3, NULL);
		lv_label_set_text(label, "Mid Home Row");
		//
		// button 4
		//
		lv_obj_t * btn4 = lv_btn_create(lv_scr_act(), btn1);
		lv_obj_set_pos(btn4, 325, 100);
		lv_obj_set_free_num(btn4, 4);
		// make button text
		label = lv_label_create(btn4, NULL);
		lv_label_set_text(label, "Right Home Row");
	}
