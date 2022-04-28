#pragma once
#include "ResourceBase.hpp"

namespace LuaSTGPlus {
	// ����ϵͳ
	// HGE����ϵͳ��f2dʵ��
	class ResParticle :
		public Resource
	{
	public:
		/// @brief ������Ϣ
		struct ParticleInfo
		{
			fuInt iBlendInfo;

			int nEmission;  // ÿ�뷢�����
			float fLifetime;  // ������
			float fParticleLifeMin;  // ������С������
			float fParticleLifeMax;  // �������������
			float fDirection;  // ���䷽��
			float fSpread;  // ƫ�ƽǶ�
			bool bRelative;  // ʹ�����ֵ���Ǿ���ֵ

			float fSpeedMin;  // �ٶ���Сֵ
			float fSpeedMax;  // �ٶ����ֵ

			float fGravityMin;  // ������Сֵ
			float fGravityMax;  // �������ֵ

			float fRadialAccelMin;  // ����߼��ٶ�
			float fRadialAccelMax;  // ����߼��ٶ�

			float fTangentialAccelMin;  // ��ͽǼ��ٶ�
			float fTangentialAccelMax;  // ��߽Ǽ��ٶ�

			float fSizeStart;  // ��ʼ��С
			float fSizeEnd;  // ���մ�С
			float fSizeVar;  // ��С����ֵ

			float fSpinStart;  // ��ʼ����
			float fSpinEnd;  // ��������
			float fSpinVar;  // ��������ֵ

			float colColorStart[4];  // ��ʼ��ɫ(rgba)
			float colColorEnd[4];  // ������ɫ
			float fColorVar;  // ��ɫ����ֵ
			float fAlphaVar;  // alpha����ֵ
		};
		/// @brief ����ʵ��
		struct ParticleInstance
		{
			fcyVec2 vecLocation;  // λ��
			fcyVec2 vecVelocity;  // �ٶ�

			float fGravity;  // ����
			float fRadialAccel;  // �߼��ٶ�
			float fTangentialAccel;  // �Ǽ��ٶ�

			float fSpin;  // ����
			float fSpinDelta;  // ��������

			float fSize;  // ��С
			float fSizeDelta;  // ��С����

			float colColor[4];  // ��ɫ
			float colColorDelta[4];  // ��ɫ����

			float fAge;  // ��ǰ���ʱ��
			float fTerminalAge;  // ��ֹʱ��
		};
		/// @brief ���ӳ�
		class ParticlePool
		{
			friend class ResParticle;
		public:
			enum class Status
			{
				Alive,
				Sleep
			};
		private:
			fcyRefPointer<ResParticle> m_pInstance;  // ��Ϣ

			BlendMode m_BlendMode = BlendMode::MulAlpha;
			fcyColor m_MixColor;//��Ⱦʱ������ɫ
			Status m_iStatus = Status::Alive;  // ״̬
			fcyVec2 m_vCenter;  // ����
			fcyVec2 m_vPrevCenter;  // ��һ������
			float m_fRotation = 0.f;  // ����
			size_t m_iAlive = 0;  // �����
			float m_fAge = 0.f;  // �Ѵ��ʱ��
			float m_fEmission = 0.f;  // ÿ�뷢����
			float m_fEmissionResidue = 0.f;  // �����������
			std::array<ParticleInstance, LPARTICLE_MAXCNT> m_ParticlePool;
		public:
			size_t GetAliveCount()const LNOEXCEPT { return m_iAlive; }
			BlendMode GetBlendMode()const LNOEXCEPT { return m_BlendMode; }
			void SetBlendMode(BlendMode m)LNOEXCEPT { m_BlendMode = m; }
			fcyColor GetMixColor()LNOEXCEPT { return m_MixColor; }
			void SetMixColor(fcyColor c)LNOEXCEPT { m_MixColor = c; }
			float GetEmission()const LNOEXCEPT { return m_fEmission; }
			void SetEmission(float e)LNOEXCEPT { m_fEmission = e; }
			bool IsActived()const LNOEXCEPT { return m_iStatus == Status::Alive; }
			void SetActive()LNOEXCEPT
			{
				m_iStatus = Status::Alive;
				m_fAge = 0.f;
			}
			void SetInactive()LNOEXCEPT
			{
				m_iStatus = Status::Sleep;
			}
			void SetCenter(fcyVec2 pos)LNOEXCEPT
			{
				if (m_iStatus == Status::Alive)
					m_vPrevCenter = m_vCenter;
				else
					m_vPrevCenter = pos;
				m_vCenter = pos;
			}
			void SetRotation(float r)LNOEXCEPT { m_fRotation = r; }
			void Update(float delta);
			void Render(f2dGraphics2D* graph, float scaleX, float scaleY);
		public:
			ParticlePool(fcyRefPointer<ResParticle> ref);
		};
	private:
		static fcyMemPool<sizeof(ParticlePool)> s_MemoryPool;

		fcyRefPointer<f2dSprite> m_BindedSprite;
		BlendMode m_BlendMode = BlendMode::MulAlpha;
		ParticleInfo m_ParticleInfo;
		double m_HalfSizeX = 0.;
		double m_HalfSizeY = 0.;
		bool m_bRectangle = false;
	public:
		ParticlePool* AllocInstance()LNOEXCEPT;
		void FreeInstance(ParticlePool* p)LNOEXCEPT;

		f2dSprite* GetBindedSprite()LNOEXCEPT { return m_BindedSprite; }
		const ParticleInfo& GetParticleInfo()const LNOEXCEPT { return m_ParticleInfo; }
		double GetHalfSizeX()const LNOEXCEPT { return m_HalfSizeX; }
		double GetHalfSizeY()const LNOEXCEPT { return m_HalfSizeY; }
		bool IsRectangle()const LNOEXCEPT { return m_bRectangle; }
	public:
		ResParticle(const char* name, const ParticleInfo& pinfo, fcyRefPointer<f2dSprite> sprite, BlendMode bld, double a, double b, bool rect = false);
	};
}
