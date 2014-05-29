#include <OpenGL/MemoryBlocksGPU.hh>
#include <iostream>
#include <stdint.h>

# define WARNING_MESSAGE_SETTING(type, index) \
	std::cerr << "warning: tentative to set value to the index : [" << index << "] which is out of range on a object MemoryBlocksGPU for " << type << std::endl;\

# define WARNING_MESSAGE_GETTING(type, index) \
	std::cerr << "warning: tentative to get value to the index : [" << index << "] which is out of range on a object MemoryBlocksGPU for " << type << std::endl;\

namespace gl
{
	MemoryBlocksGPU::MemoryBlocksGPU()
		: _nbrObject(0),
		_nbrElement(0),
		_startElement(0),
		_nbrBlock(0),
		_sizeBlocks(NULL),
		_baseOffset(NULL),
		_sync(false)
	{

	}

	MemoryBlocksGPU::~MemoryBlocksGPU()
	{
		if (_nbrBlock)
		{
			delete[] _sizeBlocks;
			delete[] _baseOffset;
		}
	}

	MemoryBlocksGPU::MemoryBlocksGPU(MemoryBlocksGPU const &copy)
		: _nbrObject(copy._nbrObject),
		_nbrElement(copy._nbrElement),
		_startElement(copy._startElement),
		_nbrBlock(copy._nbrBlock),
		_sizeBlocks(NULL),
		_baseOffset(NULL),
		_sync(false)
	{
		if (_nbrBlock)
		{
			_sizeBlocks = new size_t[_nbrBlock];
			_baseOffset = new size_t[_nbrBlock];
		}
		for (size_t index = 0; index < copy._nbrBlock; ++index)
		{
			_sizeBlocks[index] = copy._sizeBlocks[index];
			_baseOffset[index] = copy._baseOffset[index];
		}
	}

	MemoryBlocksGPU &MemoryBlocksGPU::operator=(MemoryBlocksGPU const &b)
	{
		if (&b != this)
		{
			_sync = false;
			_nbrObject = b._nbrObject;
			_startElement = b._startElement;
			_nbrElement = b._nbrElement;
			if (b._nbrBlock != _nbrBlock)
			{
				if (_nbrBlock)
				{
					delete[] _sizeBlocks;
					delete[] _baseOffset;
				}
				_nbrBlock = b._nbrBlock;
				if (_nbrBlock)
				{
					_sizeBlocks = new size_t[_nbrBlock];
					_baseOffset = new size_t[_nbrBlock];
				}
				else
				{
					_baseOffset = NULL;
					_sizeBlocks = NULL;
				}
			}
			for (size_t index = 0; index < b._nbrBlock; ++index)
			{
				_sizeBlocks[index] = b._sizeBlocks[index];
				_baseOffset[index] = b._baseOffset[index];
			}
		}
		return (*this);
	}

	size_t MemoryBlocksGPU::getNbrObject() const
	{
		return (_nbrObject);
	}

	size_t MemoryBlocksGPU::getElementStart() const
	{
		return (_startElement);
	}

	size_t MemoryBlocksGPU::getOffset(uint8_t index) const
	{
		if (index >= _nbrBlock)
		{
			WARNING_MESSAGE_GETTING("getOffset", index);
			return (-1);
		}
		return (_baseOffset[index]);
	}

	size_t MemoryBlocksGPU::getNbrBlock() const
	{
		return (_nbrBlock);
	}

	size_t MemoryBlocksGPU::getSizeBlock(uint8_t index) const
	{
		if (index >= _nbrBlock)
		{
			WARNING_MESSAGE_GETTING("size", index);
			return (-1);
		}
		return (_sizeBlocks[index]);
	}

	MemoryBlocksGPU &MemoryBlocksGPU::setNbrObject(size_t nbrObject)
	{
		_nbrObject = nbrObject;
		return (*this);
	}

	MemoryBlocksGPU &MemoryBlocksGPU::setStartElement(size_t start)
	{
		_startElement = start;
		return (*this);
	}

	MemoryBlocksGPU &MemoryBlocksGPU::setOffset(uint8_t index, size_t offset)
	{
		if (index >= _nbrBlock)
		{
			WARNING_MESSAGE_SETTING("setOffset", index);
			return (*this);
		}
		_baseOffset[index] = offset;
		return (*this);
	}

	// the values into the new storage are set to 0.
	MemoryBlocksGPU &MemoryBlocksGPU::setNbrBlock(size_t nbrBlock)
	{
		if (nbrBlock != _nbrBlock)
		{
			if (_nbrBlock)
			{
				delete[] _baseOffset;
				delete[] _sizeBlocks;
			}
			_nbrBlock = nbrBlock;
			if (nbrBlock)
			{
				_baseOffset = new size_t[_nbrBlock];
				_sizeBlocks = new size_t[_nbrBlock];
				memset(_sizeBlocks, 0, sizeof(size_t) * _nbrBlock);
				memset(_baseOffset, 0, sizeof(size_t)* _nbrBlock);
			}
			else
			{
				_baseOffset = NULL;
				_sizeBlocks = NULL;
			}
		}
		return (*this);
	}

	MemoryBlocksGPU &MemoryBlocksGPU::setSizeBlock(uint8_t index, size_t sizeBlock)
	{
		if (index >= _nbrBlock)
		{
			WARNING_MESSAGE_SETTING("size", index);
			return (*this);
		}
		_sizeBlocks[index] = sizeBlock;
		return (*this);
	}

	MemoryBlocksGPU &MemoryBlocksGPU::setNbrElement(size_t nbrElement)
	{
		_nbrElement = nbrElement;
		return (*this);
	}

	size_t MemoryBlocksGPU::getNbrElement() const
	{
		return (_nbrElement);
	}

	MemoryBlocksGPU &MemoryBlocksGPU::setSync(bool sync)
	{
		_sync = sync;
		return (*this);
	}

	bool MemoryBlocksGPU::getSync() const
	{
		return (_sync);
	}
}