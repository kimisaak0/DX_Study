#pragma once
#include "ShapeHeader.h"

namespace Lypi
{

	enum D3D_DECL_USAGE
	{
		D3DDECLUSAGE_POSITION = 0,
		D3DDECLUSAGE_BLENDWEIGHT = 1,
		D3DDECLUSAGE_BLENDINDICES = 2,
		D3DDECLUSAGE_NORMAL = 3,
		D3DDECLUSAGE_TEXCOORD = 5,
		D3DDECLUSAGE_TANGENT = 6,
		D3DDECLUSAGE_BINORMAL = 7,
		D3DDECLUSAGE_COLOR = 10,
	};

	enum D3D_DECL_TYPE
	{
		D3DDECLTYPE_FLOAT1 = 0,  // 1D float expanded to (value, 0., 0., 1.)
		D3DDECLTYPE_FLOAT2 = 1,  // 2D float expanded to (value, value, 0., 1.)
		D3DDECLTYPE_FLOAT3 = 2,  // 3D float expanded to (value, value, value, 1.)
		D3DDECLTYPE_FLOAT4 = 3,  // 4D float
		D3DDECLTYPE_D3DCOLOR = 4,  // 4D packed unsigned bytes mapped to 0. to 1. range
								   // Input is in D3DCOLOR format (ARGB) expanded to (R, G, B, A)
								   D3DDECLTYPE_UBYTE4 = 5,  // 4D unsigned byte
								   D3DDECLTYPE_UBYTE4N = 8,  // Each of 4 bytes is normalized by dividing to 255.0
								   D3DDECLTYPE_SHORT4N = 10,  // 4D signed short normalized (v[0]/32767.0,v[1]/32767.0,v[2]/32767.0,v[3]/32767.0)
															  // Note: There is no equivalent to D3DDECLTYPE_DEC3N (14) as a DXGI_FORMAT
															  D3DDECLTYPE_FLOAT16_2 = 15,  // Two 16-bit floating point values, expanded to (value, value, 0, 1)
															  D3DDECLTYPE_FLOAT16_4 = 16,  // Four 16-bit floating point values

															  D3DDECLTYPE_UNUSED = 17,  // When the type field in a decl is unused.

																						// These are extensions for DXGI-based versions of Direct3D
																						D3DDECLTYPE_DXGI_R10G10B10A2_UNORM = 32 + DXGI_FORMAT_R10G10B10A2_UNORM,
																						D3DDECLTYPE_DXGI_R11G11B10_FLOAT = 32 + DXGI_FORMAT_R11G11B10_FLOAT,
																						D3DDECLTYPE_DXGI_R8G8B8A8_SNORM = 32 + DXGI_FORMAT_R8G8B8A8_SNORM,
																						D3DDECLTYPE_XBOX_R10G10B10_SNORM_A2_UNORM = 32 + 189,
	};

#pragma pack(push,4)

	void NormalizeBoneWeights(BYTE* pWeights);
	INT GetElementSizeFromDeclType(DWORD Type);

	struct D3D_VERTEX_ELEMENT9
	{
		WORD    Stream;     // Stream index
		WORD    Offset;     // Offset in the stream in bytes
		BYTE    Type;       // Data type
		BYTE    Method;     // Processing method
		BYTE    Usage;      // Semantics
		BYTE    UsageIndex; // Semantic index
	};

#pragma pack(pop)

	struct VertexFormat
	{
		bool        m_bPosition;
		bool        m_bNormal;
		bool        m_bTangent;
		bool        m_bBinormal;
		bool        m_bSkinData;
		bool        m_bVertexColor;
		UINT        m_uUVSetCount;
		UINT        m_uUVSetSize;

	public:
		VertexFormat();
		~VertexFormat();
	};

	struct Export_Mesh_Vertex
	{
		UINT                      DCCVertexIndex;
		D3DXVECTOR3               Position;
		D3DXVECTOR3               Normal;
		D3DXVECTOR3               SmoothNormal;
		D3DXVECTOR3               Tangent;
		D3DXVECTOR3               Binormal;
		D3DXVECTOR4				  BoneIndices;
		D3DXVECTOR4               BoneWeights;
		D3DXVECTOR4               TexCoords[8];
		D3DXVECTOR4               Color;
		Export_Mesh_Vertex*       pNextDuplicateVertex;


	public:
		void Initialize();
		bool Equals(const Export_Mesh_Vertex* pOtherVertex) const;

	public:
		Export_Mesh_Vertex();
		~Export_Mesh_Vertex();
	};

	typedef vector< Export_Mesh_Vertex* > Export_Mesh_Vertex_Array;

	class Export_VB
	{

	protected:
		DWORD                       m_uVertexSizeBytes;
		size_t                      m_uVertexCount;
		unique_ptr<uint8_t[]>       m_pVertexData;

	public:
		void SetVertexSize(DWORD uByteCount);
		DWORD GetVertexSize() const; 

		void SetVertexCount(size_t uVertexCount);
		size_t GetVertexCount() const;

		void Allocate();

		uint8_t* GetVertex(size_t uIndex);
		const uint8_t* GetVertex(size_t uIndex) const;

		uint8_t* GetVertexData();
		const uint8_t* GetVertexData() const;
		size_t GetVertexDataSize() const;

		void ByteSwap(const D3D_VERTEX_ELEMENT9* pVertexElements, const size_t dwVertexElementCount);

	public:
		Export_VB();
		~Export_VB();
	};

	class Export_IB
	{
	protected:
		DWORD                       m_dwIndexSize;
		size_t                      m_uIndexCount;
		std::unique_ptr<uint8_t[]>  m_pIndexData;

	public:
		void SetIndexSize(DWORD dwIndexSize);
		DWORD GetIndexSize() const;

		void SetIndexCount(size_t uIndexCount);
		size_t GetIndexCount() const;

		void Allocate();

		DWORD GetIndex(size_t uIndex) const;

		void SetIndex(size_t uIndex, DWORD dwData);
		uint8_t* GetIndexData();
		const uint8_t* GetIndexData() const;
		size_t GetIndexDataSize() const;

		void ByteSwap();

	public:
		Export_IB();
		~Export_IB();

	};

	class Exp_Mesh
	{
	protected:
		float m_fUnitScale;
		bool  m_bMaxConversion;
		bool  m_bFlipZ;

	public:
		enum OptimizationFlags
		{
			COMPRESS_VERTEX_DATA = 1,
			FLIP_TRIANGLES = 2,
			FORCE_SUBD_CONVERSION = 4,
			CLEAN_MESHES = 8,
			VCACHE_OPT = 16,
		};

		bool                                     m_x2Bias;
		vector< D3D_VERTEX_ELEMENT9 >            m_VertexElements;
		vector< D3D11_INPUT_ELEMENT_DESC  >      m_InputLayout;
		unique_ptr<Export_VB>                    m_pVB;
		unique_ptr<Export_IB>                    m_pIB;
		unique_ptr<D3DXVECTOR3[]>                m_pVBPositions;
		unique_ptr<D3DXVECTOR3[]>                m_pVBNormals;
		unique_ptr<D3DXVECTOR2[]>                m_pVBTexCoords;
	
		// 2018
		vector< T_STR >                         m_InfluenceNames;
		unordered_map<T_STR, D3DXMATRIX>        m_matBindPoseMap;
		VertexFormat                            m_VertexFormat;
		
	public:
		void AddInfluence(T_STR InfluenceName);
		void SetVertexUVCount(UINT uCount);
		void SetVertexUVDimension(UINT uDimension);
		void SetVertexColorCount(UINT uCount);

		size_t GetVertexDeclElementCount();
		const D3D_VERTEX_ELEMENT9& GetVertexDeclElement(size_t uIndex) const;

		void BuildVertexBuffer(Export_Mesh_Vertex_Array& VertexArray, DWORD dwFlags);

		void TransformPosition(D3DXVECTOR3* pDestPosition, const D3DXVECTOR3* pSrcPosition) const;
		void TransformAndWriteVector(BYTE* pDest, D3DXVECTOR3* normal, const D3DXVECTOR3& Src, DWORD dwDestFormat);
		void TransformDirection(D3DXVECTOR3* pDestDirection, const D3DXVECTOR3* pSrcDirection) const;
		void TransformMatrix(D3DXMATRIX* pDestMatrix, const D3DXMATRIX* pSrcMatrix) const;
		float TransformLength(float fInputLength) const;

		// Sets unit scale for exporting all geometry - works with characters too.
		void SetUnitScale(const float fScale);
		void SetZFlip(const bool bFlip);


	public:
		Exp_Mesh();
		virtual ~Exp_Mesh();
	};
}