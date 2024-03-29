﻿#include <string>
#include "..\LuaWrapper.hpp"

namespace SPFbase
{
	namespace LuaWrapper
	{
		namespace IO
		{
			void BinaryReaderWrapper::Register(lua_State* L)LNOEXCEPT {
				struct Function {
#define GETUDATA(index) BinaryReaderWrapper::Wrapper* p = static_cast<BinaryReaderWrapper::Wrapper*>(luaL_checkudata(L, (index), SPFBASE_LUA_TYPENAME_IO_BINARY_READER));
					static int ReadChar(lua_State* L)LNOEXCEPT {
						GETUDATA(-1);
						fChar ch[2] = { 0,0 };
						bool ok = false;
						try {
							ch[0] = p->handle->ReadChar();
							ok = true;
						}
						catch (...) { }
						if (ok)
							lua_pushstring(L, ch);
						else
							lua_pushnil(L);
						return 1;
					}
					static int ReadChars(lua_State* L)LNOEXCEPT {
						GETUDATA(-2);
						size_t count = (size_t)luaL_checkinteger(L, -1);
						std::string buffer;
						buffer.resize(count);
						bool ok = false;
						try {
							p->handle->ReadChars(buffer.data(), (fLen)count);
							ok = true;
						}
						catch (...) {}
						if (ok)
							lua_pushstring(L, buffer.c_str());
						else
							lua_pushnil(L);
						return 1;
					}
					static int ReadByte(lua_State* L)LNOEXCEPT {
						GETUDATA(-1);
						fByte b = 0u;
						bool ok = false;
						try {
							b = p->handle->ReadByte();
							ok = true;
						}
						catch (...) {}
						if (ok) {
							lua_Integer ret = (lua_Integer)b;
							::lua_pushinteger(L, ret);
						}
						else
							lua_pushnil(L);
						return 1;
					}
					static int ReadInt16(lua_State* L)LNOEXCEPT {
						GETUDATA(-1);
						fShort b = 0;
						bool ok = false;
						try {
							b = p->handle->ReadInt16();
							ok = true;
						}
						catch (...) {}
						if (ok) {
							lua_Integer ret = (lua_Integer)b;
							::lua_pushinteger(L, ret);
						}
						else
							lua_pushnil(L);
						return 1;
					}
					static int ReadUInt16(lua_State* L)LNOEXCEPT {
						GETUDATA(-1);
						fuShort b = 0u;
						bool ok = false;
						try {
							b = p->handle->ReadUInt16();
							ok = true;
						}
						catch (...) {}
						if (ok) {
							lua_Integer ret = (lua_Integer)b;
							::lua_pushinteger(L, ret);
						}
						else
							lua_pushnil(L);
						return 1;
					}
					static int ReadInt32(lua_State* L)LNOEXCEPT {
						GETUDATA(-1);
						fInt b = 0;
						bool ok = false;
						try {
							b = p->handle->ReadInt32();
							ok = true;
						}
						catch (...) {}
						if (ok) {
							lua_Integer ret = (lua_Integer)b;
							::lua_pushinteger(L, ret);
						}
						else
							lua_pushnil(L);
						return 1;
					}
					static int ReadFloat(lua_State* L)LNOEXCEPT {
						GETUDATA(-1);
						fFloat b = 0;
						bool ok = false;
						try {
							b = p->handle->ReadFloat();
							ok = true;
						}
						catch (...) {}
						if (ok) {
							lua_Number ret = (lua_Number)b;
							::lua_pushnumber(L, ret);
						}
						else
							lua_pushnil(L);
						return 1;
					}
					static int ReadDouble(lua_State* L)LNOEXCEPT {
						GETUDATA(-1);
						fDouble b = 0;
						bool ok = false;
						try {
							b = p->handle->ReadDouble();
							ok = true;
						}
						catch (...) {}
						if (ok) {
							lua_Number ret = (lua_Number)b;
							::lua_pushnumber(L, ret);
						}
						else
							lua_pushnil(L);
						return 1;
					}
					
					static int Meta_ToString(lua_State* L)LNOEXCEPT
					{
						GETUDATA(-1);
						::lua_pushstring(L, SPFBASE_LUA_TYPENAME_IO_BINARY_READER);
						return 1;
					}
					static int Meta_GC(lua_State* L)LNOEXCEPT
					{
						GETUDATA(-1);
						if (p->handle != nullptr) {
							delete p->handle;
							p->handle = nullptr;
						}
						return 0;
					}
#undef GETUDATA
				};

				luaL_Reg tMethods[] =
				{
					{ "ReadChar", &Function::ReadChar },
					{ "ReadChars", &Function::ReadChars },
					{ "ReadByte", &Function::ReadByte },
					{ "ReadInt16", &Function::ReadInt16 },
					{ "ReadUInt16", &Function::ReadUInt16 },
					{ "ReadInt32", &Function::ReadInt32 },
					{ "ReadFloat", &Function::ReadFloat },
					{ "ReadDouble", &Function::ReadDouble },
					{ NULL, NULL }
				};

				luaL_Reg tMetaTable[] =
				{
					{ "__tostring", &Function::Meta_ToString },
					{ "__gc", &Function::Meta_GC },
					{ NULL, NULL }
				};

				RegisterClassIntoTable(L, ".BinaryReader", tMethods, SPFBASE_LUA_TYPENAME_IO_BINARY_READER, tMetaTable);
			}

			void BinaryReaderWrapper::CreateAndPush(lua_State* L, fcyStream* handle) {
				BinaryReaderWrapper::Wrapper* p = static_cast<BinaryReaderWrapper::Wrapper*>(lua_newuserdata(L, sizeof(BinaryReaderWrapper::Wrapper))); // udata
				new(p) BinaryReaderWrapper::Wrapper();
				p->handle = new fcyBinaryReader(handle);
				luaL_getmetatable(L, SPFBASE_LUA_TYPENAME_IO_BINARY_READER); // udata mt
				lua_setmetatable(L, -2); // udata 
			}
		}
	}
}
