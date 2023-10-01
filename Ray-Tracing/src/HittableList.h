#pragma once
#include "Hittable.h"
#include <memory>
#include <vector>

class HittableList : public Hittable
{
public : 
	std::vector<std::shared_ptr<Hittable>> m_Objects;
	HittableList() {};
	HittableList(std::shared_ptr<Hittable> object)
	{
		add(object);
	}

	void clear() {
		m_Objects.clear();
	}

	void add(std::shared_ptr<Hittable> object) {
		m_Objects.push_back(object);
	}

	bool hit(const Ray& ray, Interval ray_t, HitRecord& record) const override {
		bool hit_anything = false;
		auto closest_so_far = ray_t.getMax();

		for (const auto& object : m_Objects) {
			if (object->hit(ray, Interval(ray_t.getMin(), closest_so_far), record)) {
				hit_anything = true;
				closest_so_far = record.m_T;
			}
		}
		return hit_anything;
	}
};