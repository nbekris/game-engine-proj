//------------------------------------------------------------------------------
//
// File Name:	ColliderLine.cpp
// Author(s):	bekri
// Course:		CS529F25
// Project:		Project 1
// Purpose:		Template for a new .cpp file.
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include "ColliderLine.h"
#include "Stream.h"
#include "ColliderCircle.h"
#include "Transform.h"
#include "Physics.h"
#include "Entity.h"
#include "Vector2D.h"
#include "CollisionRecord.h"

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	//--------------------------------------------------------------------------
	// Public Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Public Static Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Public Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Static Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Static Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	ColliderLine::ColliderLine(void)
	{
	}

	ColliderLine::ColliderLine(const ColliderLine* other)
	{
		if (other)
		{
			this->lineSegments = other->lineSegments;
		}
	}

	//--------------------------------------------------------------------------

#pragma endregion Constructors

	//--------------------------------------------------------------------------
	// Public Static Functions:
	//--------------------------------------------------------------------------

#pragma region Public Static Functions

#pragma endregion Public Static Functions

	//--------------------------------------------------------------------------
	// Public Functions:
	//--------------------------------------------------------------------------

#pragma region Public Functions

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

	void ColliderLine::Read(Stream& stream)
	{
		if (stream.IsValid())
		{
			stream.PushNode("ColliderLine");
			if (stream.Contains("LineSegments"))
			{
				auto lambda = [&stream, this]()
					{
						LineSegment lineSeg;
						stream.ReadVector2D("P0", lineSeg.p0);
						stream.ReadVector2D("P1", lineSeg.p1);

						this->AddLineSegment(lineSeg);
					};
				stream.ReadArray("LineSegments", lambda);
			}
			stream.PopNode();
		}
	}

	bool ColliderLine::IsColliding(const Collider* other) const
	{
		const ColliderCircle* circle = dynamic_cast<const ColliderCircle*>(other);
		if (circle) 
		{
			Transform otherTr = other->Parent()->Get<Transform>();
			Physics otherPh = other->Parent()->Get<Physics>();
			Vector2D Bs = otherPh.OldTranslation();
			Vector2D Be = otherTr.Translation();

			return IntersectAndReflect(circle, Bs, Be);
		}
		return false;
	}

	void ColliderLine::AddLineSegment(const LineSegment& line)
	{
		lineSegments.push_back(line);
	}

	bool ColliderLine::IntersectAndReflect(const ColliderCircle* circle, const Vector2D& Bs, const Vector2D& Be) const
	{
		float ti = 1.0f;
		Vector2D v = Bs;
		v.Sub(Be);
		CollisionRecord collisionRecord(this->Parent(), circle->Parent(), Bs, Be);
		for (const LineSegment& segment : lineSegments)
		{
			Vector2D p0 = segment.p0;
			Vector2D p1 = segment.p1;
			Vector2D e(p1);
			e.Sub(p0);
			Vector2D n(e.y, -e.x);
			n.Normalize();

			if (n.DotProduct(v) == 0)
			{
				continue;
			}

			if ((n.DotProduct(Bs) <= n.DotProduct(p0) && (n.DotProduct(Be) < n.DotProduct(p0))))
			{
				continue;
			}

			if ((n.DotProduct(Bs) >= n.DotProduct(p0) && (n.DotProduct(Be))))
			{
				continue;
			}

			float t = (n.DotProduct(p0) - n.DotProduct(Bs)) / n.DotProduct(v);

			if (t >= ti)
			{
				continue;
			}

			ti = t;

			Vector2D Bi(Bs);
			v.Scale(ti);
			Bi.Add(v);

			//Vector2D p1Check(p1);
			//Vector2D p0Check(p0);
			//Vector2D Bi1Check(Bi);
			//Vector2D Bi0Check(Bi);

			//p1Check.Sub(p0);
			//Bi1Check.Sub(p0);
			//p0Check.Sub(p1);
			//Bi0Check.Sub(p1);

			if (IsOutsideSegment(Bi, p1, p0)/*p1Check.DotProduct(Bi1Check) < 0*/)
			{
				continue;
			}

			if (IsOutsideSegment(Bi, p0, p1)/*p0Check.DotProduct(Bi0Check) < 0*/)
			{
				continue;
			}

			collisionRecord.Update(ti, Bi, n);

			continue;


			// Intersection test goes here
		}

		if (collisionRecord.ti < 1.0f)
		{
			Reflect(collisionRecord);
			return true;
		}

		return false;
	}

	bool ColliderLine::IsOutsideSegment(const Vector2D& Bi, const Vector2D& p0, const Vector2D& p1) const
	{
		Vector2D pCheck(p0);
		Vector2D BiCheck(Bi);
		pCheck.Sub(p1);
		BiCheck.Sub(p1);
		return pCheck.DotProduct(BiCheck) < 0;
	}

	void ColliderLine::Reflect(const CollisionRecord& collision) const
	{
		Vector2D i = collision.Be;
		i.Sub(collision.Bi);

		Vector2D s = collision.n;
		s.Scale(i.DotProduct(s));

		Vector2D r = i;
		s.Scale(2.0f);
		r.Sub(s);

		Vector2D Br(collision.Bi);
		Br.Add(r);

		ColliderCircle* circle = collision.entityA->Get<ColliderCircle>();
		Transform tr = collision.entityA->Get<Transform>();
		Physics ph = collision.entityA->Get<Physics>();

		tr.Translation(Br);
		float angle = atan2f(r.y, r.x);
		tr.Rotation(angle);
		ph.Velocity(r);
	}

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace