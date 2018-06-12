/*
		AUTHOR: SlonoBoyko
		LiteHack.Ru
		21.05.2018
*/

#pragma once

namespace func
{
	template<typename Ret = void, typename ... Args>
	inline Ret stdcall(DWORD func_address, Args ... args)
	{
		return reinterpret_cast<Ret(__stdcall *)(Args ...)>(func_address)(args ...);
	}

	template<typename Ret = void, typename T, typename ... Args>
	inline Ret thiscall(DWORD func_address, T _this, Args ... args)
	{
		return reinterpret_cast<Ret(__thiscall *)(T, Args ...)>(func_address)(_this, args ...);
	}

	template<typename Ret = void, typename ... Args>
	inline Ret cdclcall(DWORD func_address, Args ... args)
	{
		return reinterpret_cast<Ret(__cdecl *)(Args ...)>(func_address)(args ...);
	}
};

namespace hook
{
	static uint32_t protect(void *dest, size_t len, uint32_t protection)
	{
		uint32_t old_protection;
		VirtualProtectEx(GetCurrentProcess(), dest, len, protection, (PDWORD)&old_protection);
		return old_protection;
	}

	inline uint32_t call(uint32_t addr, void *func, size_t len = 5)
	{
		uint32_t prot = protect((void*)addr, len, PAGE_EXECUTE_READWRITE);
		uint32_t func_ptr = reinterpret_cast<uint32_t>(func);
		memset((void*)addr, 0x90, len);
		*reinterpret_cast<uint8_t*>(addr) = 0xE8;
		*reinterpret_cast<uint32_t*>(addr + 1) = func_ptr - addr - 5;
		protect((void*)addr, len, prot);
		return addr + len;
	}

	inline uint32_t jump(uint32_t addr, void *func, size_t len = 5)
	{
		uint32_t prot = protect((void*)addr, len, PAGE_EXECUTE_READWRITE);
		uint32_t func_ptr = reinterpret_cast<uint32_t>(func);
		memset((void*)addr, 0x90, len);
		*reinterpret_cast<uint8_t*>(addr) = 0xE9;
		*reinterpret_cast<uint32_t*>(addr + 1) = func_ptr - addr - 5;
		protect((void*)addr, len, prot);
		return addr + len;
	}

	template<typename T>
	inline T func(uint32_t addr, T func)
	{
		uint32_t prot = protect((void*)addr, 4, PAGE_EXECUTE_READWRITE);
		uint32_t func_ptr = reinterpret_cast<uint32_t>(func);
		uint32_t orig_ptr = *reinterpret_cast<uint32_t*>(addr);
		*reinterpret_cast<uint32_t*>(addr) = func_ptr;
		protect((void*)addr, 4, prot);
		return reinterpret_cast<T>(orig_ptr);
	}
};

namespace mem
{
	template<typename T>
	static T *duplicate(const T *value)
	{
		if (!value) return nullptr;	
		return new T(*value);
	};

	static uint32_t protect(void *dest, size_t len, uint32_t protection)
	{
		uint32_t old_protection;
		if (!VirtualProtectEx(GetCurrentProcess(), dest, len, protection, (PDWORD)&old_protection))
			return 0;
		return old_protection;
	};

	static void *read(void *dest, const void *src, size_t len)
	{
		SYSTEM_INFO sinfo;
		GetSystemInfo(&sinfo);
		size_t psz = sinfo.dwPageSize;

		void	*_src = const_cast<void*>(src);
		uint8_t *src_ptr = static_cast<uint8_t*>(_src);
		uint8_t *dst_ptr = static_cast<uint8_t*>(dest);
		size_t	read_len = 0, all_size = len;

		uint32_t prot = protect(_src, all_size, PAGE_EXECUTE_READWRITE);
		while ((src_ptr += read_len) && (dst_ptr += read_len) && (len -= read_len))
		{
			size_t pg_offs = (size_t)((uintptr_t)src_ptr % psz);
			size_t pg_remn = psz - pg_offs;
			read_len = len > pg_remn ? pg_remn : len;
			std::copy(src_ptr, src_ptr + read_len, dst_ptr);
		}
		protect(_src, all_size, prot);
		return dest;
	};

	static void *write(void *dest, const void *src, size_t len)
	{
		SYSTEM_INFO sinfo;
		GetSystemInfo(&sinfo);
		size_t psz = sinfo.dwPageSize;

		void *_src = const_cast<void*>(src);
		uint8_t *src_ptr = static_cast<uint8_t*>(_src);
		uint8_t *dst_ptr = static_cast<uint8_t*>(dest);
		size_t	read_len = 0, all_size = len;
		
		uint32_t prot = protect(dest, all_size, PAGE_EXECUTE_READWRITE);
		while ((src_ptr += read_len) && (dst_ptr += read_len) && (len -= read_len))
		{
			size_t pg_offs = (size_t)((uintptr_t)dst_ptr % psz);
			size_t pg_remn = psz - pg_offs;
			read_len = len > pg_remn ? pg_remn : len;
			std::copy(src_ptr, src_ptr + read_len, dst_ptr);
		}
		protect(dest, all_size, prot);
		return dest;
	};

	// returns 1 if bytes match and 0 if not match
	static int compare(const void *orig, const void *comp, size_t len)
	{
		int		retvalue = 1;
		void	*_org = const_cast<void*>(orig);
		void	*_cmp = const_cast<void*>(comp);
		uint8_t *org = static_cast<uint8_t*>(_org);
		uint8_t	*cmp = static_cast<uint8_t*>(_cmp);

		size_t	nlen = len > 4096 ? 4096 : len;
		void	*temp = malloc(nlen);
		memcpy	(temp, org, nlen);

		for (size_t sz = len; sz; sz -= nlen, org += nlen, cmp += nlen)
		{
			nlen = sz > 4096 ? 4096 : sz;
			mem::read(temp, org, nlen);
			retvalue = memcmp(temp, comp, nlen);
		}
		free(temp);

		return retvalue;
	};

	// returns a pointer to a modified memory location
	static void *copy(void *dest, const void *src, size_t len, bool cmp = false,
		const void *cmpdata = nullptr)
	{
		if (cmp && cmpdata != nullptr) {
			if (mem::compare(dest, cmpdata, len)) {
				return nullptr;
			}
		}
		void	*_src = const_cast<void*>(src);
		uint8_t *sptr = static_cast<uint8_t*>(_src);
		uint8_t *dptr = static_cast<uint8_t*>(dest);
		size_t	nlen = len > 4096 ? 4096 : len;
		void	*temp = malloc(nlen);

		for (size_t sz = len; sz; sz -= nlen, 
			sptr += nlen, dptr += nlen)
		{
			nlen = sz > 4096 ? 4096 : sz;
			mem::read(temp, sptr, nlen);
			mem::write(dptr, temp, nlen);
		}
		free(temp);

		return dest;
	};

	// returns a pointer to a modified memory location
	static void *set(void *dest, uint8_t val, size_t len)
	{
		size_t	nlen = len > 4096 ? 4096 : len;
		uint8_t *dptr = static_cast<uint8_t*>(dest);
		void	*temp = malloc(nlen);

		memset(temp, val, nlen);

		for (size_t sz = len; sz; sz -= nlen, dptr += nlen)
		{
			nlen = sz > 4096 ? 4096 : sz;
			mem::write(dptr, temp, nlen);
		}
		free(temp);

		return dest;
	};
};
