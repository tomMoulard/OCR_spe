# include "rotation.h"

UnsignedMatrix *rotation(UnsignedMatrix *mat, double angle)
{
  double radian = angle * (PI / 180);
  double cos_angle = cos(radian);
  double sin_angle = sin(radian);
  double midx = mat->lines/2;
  double midy = mat->cols/2;
  int x1 = (0-midx)*cos_angle - (mat->cols-1-midy)*sin_angle + midx;
  int x2 = (mat->lines-1-midx)*cos_angle - (0-midy)*sin_angle + midx;
  int y1 = (0-midx)*sin_angle + (0-midy)* cos_angle + midy;
  int y2 = (mat->lines-1-midx)*sin_angle + (mat->cols-1-midy)*cos_angle + midy;
  size_t lx = (size_t)abs(x2-x1);
  size_t ly = (size_t)abs(y2-y1);
  UnsignedMatrix *dest = new_unsigned_matrix(lx, ly);
  for(size_t i = 0; i < lx; i++)
    for(size_t j = 0; j < ly; j++)
      dest->data[i * ly + j] = 0;
  for(size_t i = 0; i < mat->lines; i++)
  {
    size_t distx = i - midx;
    for(size_t j = 0; j < mat->cols; j++)
    {
      size_t disty = j - midy;
      size_t x = distx * cos_angle - disty * sin_angle + midx;
      size_t y = distx * sin_angle + disty * cos_angle + midy;
      dest->data[x * ly + y] = mat->data[i * mat->cols + j];
    }
  }
  free_unsigned_matrix(mat);
  return dest;
}
