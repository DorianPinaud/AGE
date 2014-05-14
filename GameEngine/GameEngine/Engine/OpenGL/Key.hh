#ifndef KEY_HH_
# define KEY_HH_

#include <iostream>

# define CLASS_ACCESS \
	friend VerticesManager;\

namespace gl
{
	//!\file Key.hh
	//!\author Dorian Pinaud
	//!\version v1.0
	//!\class Key<TYPE>
	//!\brief Key use to represent opengl instance outside the render context
	template <typename TYPE>
	class Key
	{
	public:
		Key();
		~Key();
		Key(Key<TYPE> const &copy);
		Key<TYPE> &operator=(Key<TYPE> const &t);
		std::size_t getId() const;
		bool empty() const;
		bool operator!() const;
		bool operator==(Key<TYPE> const &compare) const;
		bool operator!=(Key<TYPE> const &compare) const;
		void destroy();
	private:
		std::size_t _id;
	};
}

#include <OpenGL/Key.hpp>

#endif /*KEY_HK_*/