# include "rotation.h"

double min_double(double array[4])
{
  double min = array[0];
  for(int i = 1; i < 4; i++)
    if(array[i] < min)
      min = array[i];
  return min;
}

double max_double(double array[4])
{
  double max = array[0];
  for(int i = 1; i < 4; i++)
    if(array[i] > max)
      max = array[i];
  return max;
}

UnsignedMatrix *rot_180(UnsignedMatrix *mat)
{
  UnsignedMatrix *dest = new_unsigned_matrix(mat->lines, mat->cols);
  for(size_t i = 0; i < mat->lines; i++)
    for(size_t j = 0; j < mat->cols; j++)
      dest->data[(mat->lines-i)*dest->cols+(mat->cols-j)]
        =mat->data[i*mat->cols+j];
  return dest;
}

UnsignedMatrix *create_dest(UnsignedMatrix *mat, double radian)
{
  double x[4];
  double y[4];
  double midx = mat->lines/2;
  double midy = mat->cols/2;
  double cos_angle = cos(radian);
  double sin_angle = sin(radian);
  x[0] = (0-midx)*cos_angle - (0-midy)*sin_angle + midx;
  x[1] = (mat->lines-midx)*cos_angle - (0-midy)*sin_angle + midx;
  x[2] = (0-midx)*cos_angle - (mat->cols-midy)*sin_angle + midx;
  x[3] = (mat->lines-midx)*cos_angle - (mat->cols-midy)*sin_angle + midx;
  y[0] = (0-midx)*sin_angle + (0-midy)*cos_angle + midy;
  y[1] = (mat->lines-midx)*sin_angle + (0-midy)*cos_angle + midy;
  y[2] = (0-midx)*sin_angle + (mat->cols-1-midy)*cos_angle + midy;
  y[3] = (mat->lines-midx)*sin_angle + (mat->cols-midy)*cos_angle + midy;
  size_t lx = (size_t)abs(max_double(x) - min_double(x));
  size_t ly = (size_t)abs(max_double(y) - min_double(y));
  UnsignedMatrix *dest = new_unsigned_matrix(lx, ly);
  for(size_t i = 0; i < lx; i++)
    for(size_t j = 0; j < ly; j++)
      dest->data[i * ly + j] = 0;
  return dest;
}

UnsignedMatrix *rotation(UnsignedMatrix *mat, double angle)
{
  if(angle >= 180.0)
  {
    mat = rot_180(mat);
    angle -= 180.0;
  }
  double radian = angle * (PI / 180);
  double cos_angle = cos(radian);
  double sin_angle = sin(radian);
  double midx = mat->lines/2;
  double midy = mat->cols/2;
  UnsignedMatrix *dest = create_dest(mat, radian);
  size_t difx = dest->lines - mat->lines;
  size_t dify = dest->cols - mat->cols;
  for(size_t i = 0; i < mat->lines; i++)
  {
    //printf("i : %zu\n", i);
    int distx = i - midx;
    //printf("distx : %d\n", distx);
    for(size_t j = 0; j < mat->cols; j++)
    {
      //printf("j : %zu\n", j);
      int disty = j - midy;
      //printf("disty : %d\n", disty);
      int xx = (distx * cos_angle - disty * sin_angle + midx);
      //printf("x : %d\n", xx);
      size_t x = (size_t)xx + difx/2;
      int yy = (distx * sin_angle + disty * cos_angle + midy);
      //printf("y : %d\n", yy);
      size_t y = (size_t)yy + dify/2;
      dest->data[x * dest->cols + y] = mat->data[i * mat->cols + j];
    }
  }
  dest = supprbord(dest);
  return dest;
}
