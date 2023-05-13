struct {
  int min;
  int max;
} typedef range_t;

#define LEFT -1
#define RIGHT 1

void turn(int degrees);
void fix_range(range_t *range);
bool check_range(range_t *range, int azimuth);
void dump();
void pickup();
void pickup_2();

