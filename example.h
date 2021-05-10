bool test(int b)
{return b > 5;}

struct List
{
  int id;
  void (* const destroy)(struct List* self, int id);
};

static void
destroyer(struct List *self, int id)
{
  self->id = id;
}

static List newList()
{
  return List{
     0,
      &destroyer
    };
}
