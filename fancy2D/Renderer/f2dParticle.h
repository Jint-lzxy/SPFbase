////////////////////////////////////////////////////////////////////////////////
/// @file  f2dParticle.h
/// @brief fancy2D 2D����
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <fcyRefObj.h>
#include "../f2dRenderer.h"

#include <vector>

#include <fcyMisc\fcyRandom.h>

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D 2D���ӳ�ʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dParticlePoolImpl : 
	public fcyRefObjImpl<f2dParticlePool>
{
public:
	struct Particle
	{
		f2dSprite* pSprite;
		fBool bInUse;

		float CurTime;    // ��ǰ����ֵ
		float Angle;      // ��ǰ�Ƕ�

		fcyVec2 Pos;
		fcyVec2 CreatePos;
		fcyVec2 V;        // �ٶ�
		float RA;         // ������ٶ�
		float TA;         // ������ٶ�
		float Spin;       // �����ٶ�
		float LifeTime;   // ����ֵ

		float RandomSeed; // �����

		fcyColor CurColor;   // ��ǰ��ɫ
		fcyColor StartColor; // ��ʼ��ɫ
		fcyColor EndColor;   // ��ֹ��ɫ
		
		fcyVec2 CurScale;    // ��ǰ����
		fcyVec2 StartScale;  // ��ʼ����
		fcyVec2 EndScale;    // ��ֹ����
	};
protected:
	fcyRandomWELL512 m_Randomizer;

	std::vector<Particle> m_ParticlePool;

	std::vector<f2dParticleForce*> m_ForcePool;

	fuInt m_ParticleCount;
public: // �ӿ�ʵ��
	fuInt GetRandomSeed()
	{
		return m_Randomizer.GetRandSeed();
	}
	void SetRandomSeed(fuInt Seed)
	{
		m_Randomizer.SetSeed(Seed);
	}
	fFloat RandFloat(fFloat Min, fFloat Max)
	{
		return m_Randomizer.GetRandFloat(Min, Max);
	}
	
	fuInt GetCount()
	{
		return m_ParticleCount;
	}

	fuInt GetCapacity()
	{
		return m_ParticlePool.size();
	}

	void Clear()
	{
		// ������������
		std::vector<Particle>::iterator i = m_ParticlePool.begin();

		while(i != m_ParticlePool.end())
		{
			FCYSAFEKILL(i->pSprite);

			++i;
		}

		m_ParticlePool.clear();
	}

	fResult AppendForce(f2dParticleForce* pForce);
	bool RemoveForce(f2dParticleForce* pForce);
	void ClearForce();
	fResult Emitted(f2dSprite* pSprite, const fcyVec2& Center, const fcyVec2& EmittedCountRange, const f2dParticleCreationDesc& Desc);
	void Update(fFloat ElapsedTime);
	void Render(f2dGraphics2D* pGraph);
public:
	f2dParticlePoolImpl()
		: m_ParticleCount(0) {}
	~f2dParticlePoolImpl();
};
