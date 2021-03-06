/*
** mrb_ss.c - SS class
**
** Copyright (c) dojineko 2016
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mrb_ss.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  char *str;
  int len;
} mrb_ss_data;

static const struct mrb_data_type mrb_ss_data_type = {
  "mrb_ss_data", mrb_free,
};

static mrb_value mrb_ss_init(mrb_state *mrb, mrb_value self)
{
  mrb_ss_data *data;
  char *str;
  int len;

  data = (mrb_ss_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_ss_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "s", &str, &len);
  data = (mrb_ss_data *)mrb_malloc(mrb, sizeof(mrb_ss_data));
  data->str = str;
  data->len = len;
  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_ss_hello(mrb_state *mrb, mrb_value self)
{
  mrb_ss_data *data = DATA_PTR(self);

  return mrb_str_new(mrb, data->str, data->len);
}

static mrb_value mrb_ss_hi(mrb_state *mrb, mrb_value self)
{
  return mrb_str_new_cstr(mrb, "hi!!");
}

void mrb_mruby_ss_gem_init(mrb_state *mrb)
{
  struct RClass *ss;
  ss = mrb_define_class(mrb, "SS", mrb->object_class);
  mrb_define_method(mrb, ss, "initialize", mrb_ss_init, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ss, "hello", mrb_ss_hello, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, ss, "hi", mrb_ss_hi, MRB_ARGS_NONE());
  DONE;
}

void mrb_mruby_ss_gem_final(mrb_state *mrb)
{
}

