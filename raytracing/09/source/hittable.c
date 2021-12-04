#include "hittable.h"

void set_face_normal(t_hit_record *rec, t_ray r, t_vec3 outward_normal)
{
	/** 광선과 법선 벡터의 내적 값으로 양수이면 카메라가 물체의 내부, 음수이면 카메라가 물체의 외부에 있음을 알 수 있다.
	 * 즉, front_face가 1 이라는 것은 카메라가 물체의 외부에 있다는 의미이고
	 * front_face가 0 이라는 것은 카메라가 물체의 내부에 있다는 의미가 된다. */
	rec->front_face = dot(r.direction, outward_normal) < 0;

	// 물체의 내부에 카메라가 있다면 법선벡터를 물체의 안쪽으로 향하도록 하기위해 법선벡터에 마이너스(-)를 곱해준다.
	rec->normal = rec->front_face ? outward_normal : negate(outward_normal);
}
