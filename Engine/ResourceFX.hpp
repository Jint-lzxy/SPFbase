#pragma once
#include "ResourceBase.hpp"
#include "Dictionary.hpp"

namespace LuaSTGPlus {
	// shader��װ
	class ResFX :
		public Resource
	{
	private:
		fcyRefPointer<f2dEffect> m_pShader;

		// ��������
		std::vector<f2dEffectParamValue*> m_pBindingPostEffectTexture;  // POSTEFFECTTEXTURE
		std::vector<f2dEffectParamValue*> m_pBindingViewport;  // VIEWPORT
		std::vector<f2dEffectParamValue*> m_pBindingScreenSize;  // SCREENSIZE

		// ������
		Dictionary<std::vector<f2dEffectParamValue*>> m_pBindingVar;
	public:
		f2dEffect* GetEffect()LNOEXCEPT { return m_pShader; }

		void SetPostEffectTexture(f2dTexture2D* val)LNOEXCEPT;
		void SetViewport(fcyRect rect)LNOEXCEPT;
		void SetScreenSize(fcyVec2 size)LNOEXCEPT;

		void SetValue(const char* key, float val)LNOEXCEPT;
		void SetValue(const char* key, fcyColor val)LNOEXCEPT;  // ��float4���а�
		void SetValue(const char* key, f2dTexture2D* val)LNOEXCEPT;
	public:
		ResFX(const char* name, fcyRefPointer<f2dEffect> shader);
	};
}
