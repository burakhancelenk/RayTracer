#ifndef UNION_H
#define UNION_H

#include "Object.h"
#include "Ray.h"
#include "Hit.h"
#include <vector>


namespace Primitive {

	// Union object made of others
	class Union : public Object 
	{
		private:
			std::vector<ObjectPtr> m_objects;

		public:
			// No need for default constructor
			// @param objects, a vector containing some objects
			Union(const std::vector<ObjectPtr>& objects);

			// Adds @param obj to the vector "m_objects"
			void add(const ObjectPtr& obj);

			// override Object::intersect_first_image
			bool intersect_first_image(const Ray& ray) const override;

			// override Object::intersect
			Hit intersect(const Ray& ray) const override;

			// Returns "m_objects" vector
			const std::vector<ObjectPtr>& objects() const { return m_objects; }

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const Union& u)
			{
				os << "Union(";
				bool first = true;
				for (const ObjectPtr& obj : u.objects())
				{
					if (!first) os << ", ";
					os << *obj;
					first = false;
				}
				os << ")" << std::endl;
				return os;
			}
	};

}

#endif // !UNION_H


