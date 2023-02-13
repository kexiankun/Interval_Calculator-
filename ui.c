

typedef struct {

  float tot_length;

  float railing_width;

  float railing_root;

  float interval;

} railings_data;

railings_data data;
char buf0[256] = "";
char buf[256] = "软件用途说明：\0";
char buf1[256] = "(1)：石材护栏花瓶间隔计算，石材栏板间隔计算\0";
char buf2[256] = "(2)：石材斜护栏花瓶间隔计算，石材栏板等分计算\0";
char buf3[256] = "(3)：软件用途比较全面，包括(石，铁，木) \0";
char buf4[256] = "(4)：更多用途可以自己摸索发现 \0";

char buf_tot_length[256];
char buf_railing_width[256];
char buf_railing_root[256];
char buf_interval[256];
static double  a = 0, b = 0, c = 0;
static double *current  = &a;
static double *current1 = &b;
static double *current2 = &c;
int            len;

void
add_d(railings_data *d) {

  d->interval = (d->tot_length - (d->railing_width * d->railing_root)) /
                (d->railing_root + 1);
}

void
add_y(railings_data *y) {

  y->interval = (y->tot_length - (y->railing_width * y->railing_root)) /
                (y->railing_root - 1);
}

void
add_b(railings_data *b) {

  b->interval = (b->tot_length - (b->railing_width * b->railing_root)) /
                (b->railing_root - 1 / 2);
}

void
add_dd(railings_data *b) {

  b->interval = (b->tot_length - (b->railing_width * b->railing_root)) /
                (b->railing_root + 0.5f);
}

/*渲染GUI*/
void*
render_gui(struct nk_context *ctx, SDL_Window *win, int w, int h) {
  int RH = h / 10;

  if (nk_begin(ctx, "    间隔计算器1.0.1.20220503_beta", nk_rect(0, 0, w, h),
             NK_WINDOW_SCROLL_AUTO_HIDE|
          NK_WINDOW_BORDER|NK_WINDOW_NO_SCROLLBAR))
{

    /*enum { One0, Two1, Three2, Four3 };
    static int op = One0;*/

    enum { One, Two, Three, Four, Zz };
    static int lop = Three;

   static int selected_item = 0;

    static int popup_active;
    /*函数：调整控件宽高NK布局行静态*/
    // nk_layout_row_static(ctx, 150, RH, 3);
    /*函数：调整控件宽度NK布局行动态*/
    nk_layout_row_dynamic(ctx, RH / 2, 3);
    if (nk_button_label(ctx, "开始计算")) {
      //结构声明

      *current        = atof(buf_tot_length);
      data.tot_length = *current;

      *current1          = atof(buf_railing_width);
      data.railing_width = *current1;

      *current2         = atof(buf_railing_root);
      data.railing_root = *current2;

     /* if (op == One0) { add_d(&data); }
      if (op == Two1) { add_y(&data); }
      if (op == Three2) { add_b(&data); }
      if (op == Four3) { add_dd(&data); }*/

      if (selected_item == 0) { add_d(&data); }
      if (selected_item == 1) { add_y(&data); }
      if (selected_item == 2) { add_b(&data); }
      if (selected_item == 3) { add_dd(&data); }

      len = snprintf(buf_interval, 256, "%.2f", data.interval);
    }

    if (nk_button_label(ctx, "清空输入")) {
      //清空数组

      nk_memset(buf_tot_length, 0, sizeof(buf_tot_length));
      nk_memset(buf_railing_width, 0, sizeof(buf_railing_width));
      nk_memset(buf_railing_root, 0, sizeof(buf_railing_root));
      nk_memset(buf_interval, 2.0f, sizeof(buf_interval));
    }

    if (nk_button_label(ctx, "使用说明"))
 //     nk_layout_row_push(ctx, RH);
popup_active = 1;
    //nk_layout_row_end(ctx);
    if (popup_active) {
            static struct nk_rect s = {0, 400, 340, 180};
            if (nk_popup_begin(ctx, NK_POPUP_STATIC, "root", 0, s)) {
                    nk_layout_row_dynamic(ctx, RH / 2, 1);
                    nk_label(ctx, "使用说明：看png图解 ", NK_TEXT_LEFT);
                   nk_label(ctx, "1：软件是免费的，可以复制，使用，传播", NK_TEXT_LEFT);
                   nk_label(ctx, "2：软件版权归@ by：jnck所有 WX：snd8899",
                       NK_TEXT_LEFT);
                  // nk_label(ctx, "作者：Jnck   WX：snd8899\0ghjhh ", NK_TEXT_LEFT);

                     nk_layout_row_dynamic(ctx, RH / 3, 1);
                    if (nk_button_label(ctx, "确定")) {
                            popup_active = 0;
                            nk_popup_close(ctx);
                    }
                   if (nk_button_label(ctx, "取消")) {
                      popup_active = 0;
                      nk_popup_close(ctx);
                    }
                    nk_popup_end(ctx);
            } else
              popup_active = nk_false;
    }



    /*函数：调整控件宽度NK布局行动态*/
    nk_layout_row_dynamic(ctx, RH / 2, 5);

    if (nk_option_label(ctx, "灰色", lop == Zz)) {

      lop = Zz;

      set_style(ctx, THEME_DARK);
    }

    //  set_style(ctx, 5);

    if (nk_option_label(ctx, "白色", lop == One)) {
      lop = One;
      /* style.h主题*/
      set_style(ctx, THEME_WHITE);
    }
    if (nk_option_label(ctx, "黑色", lop == Two)) {
      lop = Two;
      /* style.h主题*/
      set_style(ctx, THEME_BLACK);
    }
    if (nk_option_label(ctx, "蓝色", lop == Three)) {
      lop = Three;
      /* style.h主题*/
      set_style(ctx, THEME_BLUE);
    }
    if (nk_option_label(ctx, "红色", lop == Four)) {
      /* style.h主题*/
      lop = Four;
      set_style(ctx, THEME_RED);
    }
    /*函数：调整控件宽度NK布局行动态*/

    nk_layout_row_dynamic(ctx, RH / 2, 1);
    nk_label(ctx, "总长度小数(mm):", NK_TEXT_LEFT);
    nk_flags event = nk_edit_string_zero_terminated(
        ctx, NK_EDIT_SIMPLE, buf_tot_length, 36, nk_filter_float);

    if (event & NK_EDIT_ACTIVATED) { SDL_StartTextInput(); }

    if (event & NK_EDIT_DEACTIVATED) { SDL_StopTextInput(); }

    nk_layout_row_dynamic(ctx, RH / 2, 1);
    nk_label(ctx, "底宽小数(mm):", NK_TEXT_LEFT);

    nk_flags event1 = nk_edit_string_zero_terminated(
        ctx, NK_EDIT_SIMPLE, buf_railing_width, 36, nk_filter_float);

    if (event1 & NK_EDIT_ACTIVATED) { SDL_StartTextInput(); }

    if (event1 & NK_EDIT_DEACTIVATED) { SDL_StopTextInput(); }

    nk_layout_row_dynamic(ctx, RH / 2, 1);
    nk_label(ctx, "数量整数(根):", NK_TEXT_LEFT);
    nk_flags event2 = nk_edit_string_zero_terminated(
        ctx, NK_EDIT_SIMPLE, buf_railing_root, 36, nk_filter_float);

    if (event2 & NK_EDIT_ACTIVATED) { SDL_StartTextInput(); }

    if (event2 & NK_EDIT_DEACTIVATED) { SDL_StopTextInput(); }

    nk_label(ctx, "运算结果:", NK_TEXT_LEFT);

    nk_flags event3 = nk_edit_string(ctx, NK_EDIT_CLIPBOARD, buf_interval, &len, 256, nk_filter_float);
    if (event3& NK_EDIT_ACTIVATED)
        {
            SDL_StartTextInput();
    }
  if (event3& NK_EDIT_DEACTIVATED)
    {
        SDL_StopTextInput();
  }

  /*函数;单选框*/

  /*  nk_layout_row_dynamic(ctx, RH / 2, 3);

    if (nk_option_label(ctx, "两边有间隔", op == One0)) { op = One0; }
    if (nk_option_label(ctx, "两边没有间隔", op == Two1)) { op = Two1; }
    if (nk_option_label(ctx, "单边有间隔", op == Three2)) { op = Three2; }
      if (nk_option_label(ctx, "总长等分", op == Four3)) { op = Four3; }
      */

    static const char *items[] = {"两边有间隔", "两边没有间隔", "单边有间隔"};
    enum { aa, bb, cc, dd,ee,ff,gg,hh };

    nk_layout_row_dynamic(ctx, RH / 2, 1);
    nk_label(ctx, "选择运算模式：{三种模式}", NK_TEXT_LEFT);
    if (nk_combo_begin_label(
            ctx, items[selected_item], nk_vec2(nk_widget_width(ctx), RH*3))) {

      nk_layout_row_dynamic(ctx, RH/2, 1);
      for (int i = 0; i < 3; ++i)

      {
        if (nk_combo_item_symbol_label(ctx, gg, items[i], NK_TEXT_LEFT)) 
        {

          //    if (nk_combo_item_label(ctx, items[i], NK_TEXT_CENTERED))
          selected_item = i;
        }
      }
      nk_combo_end(ctx);
    }


    //static float value = 0.2f;
    /*滚动条*/
    /*nk_layout_row_begin(ctx, NK_STATIC, RH / 2, 2);
    {
            nk_layout_row_push(ctx, 180);
            nk_label(ctx, "调整屏幕亮度:", NK_TEXT_LEFT);
            nk_layout_row_push(ctx, 800);
            nk_slider_float(ctx, 0, &value, 1.0f, 0.1f);
    }*/

    /*函数：文本标签*/
    nk_layout_row_dynamic(ctx, RH / 2, 1);
    nk_text_wrap(ctx, buf0, strlen(buf0));
    nk_layout_row_dynamic(ctx, RH/2, 1);
    nk_text_wrap(ctx, buf, strlen(buf));
    nk_layout_row_dynamic(ctx, RH/2, 1);
    nk_text_wrap(ctx, buf1, strlen(buf1));
    nk_layout_row_dynamic(ctx, RH/2, 1);
    nk_text_wrap(ctx, buf2, strlen(buf2));
    nk_layout_row_dynamic(ctx, RH/2, 1);
    nk_text_wrap(ctx, buf3, strlen(buf3));
       nk_layout_row_dynamic(ctx, RH/2, 1);
       nk_text_wrap(ctx, buf4, strlen(buf4));



  }


  nk_end(ctx);
  return 0;
}

