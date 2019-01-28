#include "ExpMesh.h"

namespace Lypi
{

	void NormalizeBoneWeights(BYTE* pWeights)
	{
		DWORD dwSum;

		dwSum =
			static_cast<DWORD>(pWeights[0]) +
			static_cast<DWORD>(pWeights[1]) +
			static_cast<DWORD>(pWeights[2]) +
			static_cast<DWORD>(pWeights[3]);

		if (dwSum == 255) {
			return;
		}

		INT iDifference = 255 - static_cast<INT>(dwSum);

		for (DWORD i = 0; i < 4; ++i)
		{

			if (pWeights[i] == 0) {
				continue;
			}

			INT iValue = static_cast<INT>(pWeights[i]);

			if (iValue + iDifference > 255) {
				iDifference -= (255 - iValue);
				iValue = 255;
			}
			else {
				iValue += iDifference;
				iDifference = 0;
			}

			pWeights[i] = static_cast<BYTE>(iValue);
		}

		dwSum =
			static_cast<DWORD>(pWeights[0]) +
			static_cast<DWORD>(pWeights[1]) +
			static_cast<DWORD>(pWeights[2]) +
			static_cast<DWORD>(pWeights[3]);

		assert(dwSum == 255);
	}


	INT GetElementSizeFromDeclType(DWORD Type)
	{
		switch (Type) {
			case D3DDECLTYPE_FLOAT1:
			case D3DDECLTYPE_D3DCOLOR:
			case D3DDECLTYPE_UBYTE4:
			case D3DDECLTYPE_UBYTE4N:
			case D3DDECLTYPE_FLOAT16_2:
			return 4;

			case D3DDECLTYPE_FLOAT2:
			case D3DDECLTYPE_SHORT4N:
			case D3DDECLTYPE_FLOAT16_4:
			return 8;

			case D3DDECLTYPE_FLOAT3:
			return 12;

			case D3DDECLTYPE_FLOAT4:
			return 16;

			case D3DDECLTYPE_UNUSED:
			return 0;

			default:
			assert(false);
			return 0;
		}
	}

	VertexFormat::VertexFormat() : m_bPosition(true), m_bNormal(true), m_bSkinData(false), m_bTangent(false), m_bBinormal(false), m_bVertexColor(true), m_uUVSetCount(1), m_uUVSetSize(2)
	{
	}

	VertexFormat::~VertexFormat()
	{
	}

	Export_Mesh_Vertex::Export_Mesh_Vertex()
	{
		Initialize();
	}

	void Export_Mesh_Vertex::Initialize()
	{
		ZeroMemory(this, sizeof(Export_Mesh_Vertex));
		BoneWeights.x = 1.0f;
	}

	bool Export_Mesh_Vertex::Equals(const Export_Mesh_Vertex* pOtherVertex) const
	{
		if (!pOtherVertex) {
			return false;
		}

		if (pOtherVertex == this) {
			return true;
		}

		D3DXVECTOR3 v0 = Position;
		D3DXVECTOR3 v1 = pOtherVertex->Position;
		if (v0 != v1) {
			return false;
		}

		v0 = Normal;
		v1 = pOtherVertex->Normal;
		if (v0 != v1) {
			return false;
		}

		D3DXVECTOR4 v2, v3;

		for (size_t i = 0; i < 8; i++) {
			v2 = TexCoords[i];
			v3 = pOtherVertex->TexCoords[i];
			if (v2 != v3) {
				return false;
			}
		}

		v2 = Color;
		v3 = pOtherVertex->Color;
		if (v2 != v1) {
			return false;
		}

		return true;
	}

	Export_Mesh_Vertex::~Export_Mesh_Vertex()
	{}

	Export_VB::Export_VB() : m_uVertexCount(0), m_uVertexSizeBytes(0)
	{
	}

	void Export_VB::SetVertexSize(DWORD uByteCount)
	{
		m_uVertexSizeBytes = uByteCount;
	}

	DWORD Export_VB::GetVertexSize() const
	{
		return m_uVertexSizeBytes;
	}

	void Export_VB::SetVertexCount(size_t uVertexCount) {
		m_uVertexCount = uVertexCount;
	}

	size_t Export_VB::GetVertexCount() const
	{
		return m_uVertexCount;
	}

	void Export_VB::Allocate()
	{
		size_t uSize = GetVertexDataSize();
		m_pVertexData.reset(new uint8_t[uSize]);
		ZeroMemory(m_pVertexData.get(), uSize);
	}

	uint8_t* Export_VB::GetVertex(size_t uIndex)
	{
		if (!m_pVertexData) {
			return nullptr;
		}

		if (uIndex >= m_uVertexCount) {
			return nullptr;
		}

		return m_pVertexData.get() + (uIndex * m_uVertexSizeBytes);
	}

	const uint8_t* Export_VB::GetVertex(size_t uIndex) const
	{
		if (!m_pVertexData) {
			return nullptr;
		}

		if (uIndex >= m_uVertexCount) {
			return nullptr;
		}

		return m_pVertexData.get() + (uIndex * m_uVertexSizeBytes);
	}

	uint8_t* Export_VB::GetVertexData()
	{
		return m_pVertexData.get();
	}

	const uint8_t* Export_VB::GetVertexData() const
	{
		return m_pVertexData.get();
	}

	size_t Export_VB::GetVertexDataSize() const
	{
		return m_uVertexSizeBytes * m_uVertexCount;
	}

	void Export_VB::ByteSwap(const D3D_VERTEX_ELEMENT9* pVertexElements, const size_t dwVertexElementCount)
	{
		WORD* pWord;
		DWORD* pElement;
		uint8_t* pVB;

		for (size_t dwVertexIndex = 0; dwVertexIndex < m_uVertexCount; dwVertexIndex++) {
			pVB = GetVertex(dwVertexIndex);

			for (size_t i = 0; i < dwVertexElementCount; i++) {
				pElement = reinterpret_cast<DWORD*>(pVB + pVertexElements[i].Offset);

				switch (pVertexElements[i].Type) {
					{
					case D3DDECLTYPE_FLOAT4:
					*pElement = _byteswap_ulong(*pElement);
					pElement++;
					case D3DDECLTYPE_FLOAT3:
					*pElement = _byteswap_ulong(*pElement);
					pElement++;
					case D3DDECLTYPE_FLOAT2:
					*pElement = _byteswap_ulong(*pElement);
					pElement++;
					case D3DDECLTYPE_FLOAT1:
					case D3DDECLTYPE_D3DCOLOR:
					case D3DDECLTYPE_UBYTE4:
					case D3DDECLTYPE_UBYTE4N:
					*pElement = _byteswap_ulong(*pElement);
					} break;

					{
					case D3DDECLTYPE_SHORT4N:
					case D3DDECLTYPE_FLOAT16_4:
					pWord = reinterpret_cast<WORD*>(pElement);
					*pWord = _byteswap_ushort(*pWord);
					pWord++;
					*pWord = _byteswap_ushort(*pWord);
					pElement++;

					case D3DDECLTYPE_FLOAT16_2:
					pWord = reinterpret_cast<WORD*>(pElement);
					*pWord = _byteswap_ushort(*pWord);
					pWord++;
					*pWord = _byteswap_ushort(*pWord);
					pElement++;
					} break;
				}
			}
		}
	}

	Export_VB::~Export_VB()
	{
	}

	Export_IB::Export_IB() : m_uIndexCount(0), m_dwIndexSize(2)
	{
	}

	void Export_IB::SetIndexSize(DWORD dwIndexSize)
	{
		assert(dwIndexSize == 2 || dwIndexSize == 4);
		m_dwIndexSize = dwIndexSize;
	}

	DWORD Export_IB::GetIndexSize() const
	{
		return m_dwIndexSize;
	}

	void Export_IB::SetIndexCount(size_t uIndexCount)
	{
		m_uIndexCount = uIndexCount;
	}

	size_t Export_IB::GetIndexCount() const
	{
		return m_uIndexCount;
	}

	void Export_IB::Allocate()
	{
		if (m_dwIndexSize == 2) {
			m_pIndexData.reset(reinterpret_cast<uint8_t*>(new WORD[m_uIndexCount]));
			ZeroMemory(m_pIndexData.get(), m_uIndexCount * sizeof(WORD));
		}
		else {
			m_pIndexData.reset(reinterpret_cast<uint8_t*>(new DWORD[m_uIndexCount]));
			ZeroMemory(m_pIndexData.get(), m_uIndexCount * sizeof(DWORD));
		}
	}

	DWORD Export_IB::GetIndex(size_t uIndex) const
	{
		if (m_dwIndexSize == 2) {
			auto pIndexData16 = reinterpret_cast<const WORD*>(m_pIndexData.get());
			return pIndexData16[uIndex];
		}
		else {
			auto pIndexData32 = reinterpret_cast<const DWORD*>(m_pIndexData.get());
			return pIndexData32[uIndex];
		}
	}

	void Export_IB::SetIndex(size_t uIndex, DWORD dwData)
	{
		if (m_dwIndexSize == 2) {
			auto pIndexData16 = reinterpret_cast<WORD*>(m_pIndexData.get());
			pIndexData16[uIndex] = static_cast<WORD>(dwData);
		}
		else {
			auto pIndexData32 = reinterpret_cast<DWORD*>(m_pIndexData.get());
			pIndexData32[uIndex] = dwData;
		}
	}

	uint8_t* Export_IB::GetIndexData()
	{
		return m_pIndexData.get();
	}

	const uint8_t* Export_IB::GetIndexData() const
	{
		return m_pIndexData.get();
	}

	size_t Export_IB::GetIndexDataSize() const
	{
		return m_uIndexCount * m_dwIndexSize;
	}

	void Export_IB::ByteSwap()
	{
		if (m_dwIndexSize == 2) {
			auto pIndexData16 = reinterpret_cast<WORD*>(m_pIndexData.get());
			for (size_t i = 0; i < m_uIndexCount; i++) {
				WORD wIndex = _byteswap_ushort(pIndexData16[i]);
				pIndexData16[i] = wIndex;
			}
		}
		else {
			auto pIndexData32 = reinterpret_cast<DWORD*>(m_pIndexData.get());
			for (size_t i = 0; i < m_uIndexCount; i++) {
				DWORD dwIndex = _byteswap_ulong(pIndexData32[i]);
				pIndexData32[i] = dwIndex;
			}
		}
	}

	Export_IB::~Export_IB()
	{
	}

	Exp_Mesh::Exp_Mesh()
	{
	}

	void Exp_Mesh::AddInfluence(T_STR InfluenceName)
	{
		m_InfluenceNames.push_back(InfluenceName);
		m_VertexFormat.m_bSkinData = true;
	}
	void Exp_Mesh::SetVertexUVCount(UINT uCount)
	{
		m_VertexFormat.m_uUVSetCount = uCount;
	}

	void Exp_Mesh::SetVertexUVDimension(UINT uDimension)
	{
		m_VertexFormat.m_uUVSetSize = uDimension;
	}

	void Exp_Mesh::SetVertexColorCount(UINT uCount)
	{
		m_VertexFormat.m_bVertexColor = (uCount > 0);
	}

	size_t Exp_Mesh::GetVertexDeclElementCount()
	{
		return m_VertexElements.size();
	}

	const D3D_VERTEX_ELEMENT9& Exp_Mesh::GetVertexDeclElement(size_t uIndex) const
	{
		return m_VertexElements[uIndex];
	}

	void Exp_Mesh::BuildVertexBuffer(Export_Mesh_Vertex_Array& VertexArray, DWORD dwFlags)
	{
		UINT uVertexSize = 0;
		INT iCurrentVertexOffset = 0;
		INT iPositionOffset = -1;
		INT iNormalOffset = -1;
		INT iTangentOffset = -1;
		INT iBinormalOffset = -1;
		INT iSkinDataOffset = -1;
		INT iColorOffset = -1;
		INT iUVOffset = -1;

		// create a vertex element struct and set default values
		D3D_VERTEX_ELEMENT9 VertexElement;
		ZeroMemory(&VertexElement, sizeof(D3D_VERTEX_ELEMENT9));

		D3D11_INPUT_ELEMENT_DESC InputElement;
		ZeroMemory(&InputElement, sizeof(D3D11_INPUT_ELEMENT_DESC));

		bool bCompressVertexData = (dwFlags & COMPRESS_VERTEX_DATA);

		DWORD dwColorType = D3DDECLTYPE_FLOAT4;
		DXGI_FORMAT dwColorTypeDXGI = DXGI_FORMAT_B8G8R8A8_UNORM;

		switch (dwColorType) {
			case D3DDECLTYPE_FLOAT4:
			dwColorTypeDXGI = DXGI_FORMAT_R32G32B32A32_FLOAT;
			break;

			case D3DDECLTYPE_D3DCOLOR:
			break;

			case D3DDECLTYPE_UBYTE4N:
			dwColorTypeDXGI = DXGI_FORMAT_R8G8B8A8_UNORM;
			break;

			case D3DDECLTYPE_FLOAT16_4:
			dwColorTypeDXGI = DXGI_FORMAT_R16G16B16A16_FLOAT;
			break;

			default:
			assert(false);
			break;
		}

		DWORD dwNormalType = D3DDECLTYPE_FLOAT3;
		DXGI_FORMAT dwNormalTypeDXGI = DXGI_FORMAT_R32G32B32_FLOAT;
		m_x2Bias = false;

		if (bCompressVertexData) {
			dwNormalType = DXGI_FORMAT_R8G8B8A8_UNORM;

			switch (dwNormalType) {
				case D3DDECLTYPE_UBYTE4N:
				dwNormalTypeDXGI = DXGI_FORMAT_R8G8B8A8_UNORM;
				m_x2Bias = true;
				break;

				case D3DDECLTYPE_SHORT4N:
				dwNormalTypeDXGI = DXGI_FORMAT_R16G16B16A16_SNORM;
				break;

				case D3DDECLTYPE_FLOAT16_4:
				dwNormalTypeDXGI = DXGI_FORMAT_R16G16B16A16_FLOAT;
				break;

				default:
				assert(false);
				break;
			}
		}

		m_VertexElements.clear();
		m_InputLayout.clear();

		// check each vertex format option, and create a corresponding decl element
		if (m_VertexFormat.m_bPosition) {
			iPositionOffset = iCurrentVertexOffset;

			VertexElement.Offset = static_cast<WORD>(iCurrentVertexOffset);
			VertexElement.Usage = D3DDECLUSAGE_POSITION;
			VertexElement.Type = D3DDECLTYPE_FLOAT3;
			m_VertexElements.push_back(VertexElement);

			InputElement.SemanticName = "SV_Position";
			InputElement.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			InputElement.AlignedByteOffset = static_cast<UINT>(iCurrentVertexOffset);
			m_InputLayout.push_back(InputElement);

			iCurrentVertexOffset += GetElementSizeFromDeclType(VertexElement.Type);
		}

		if (m_VertexFormat.m_bSkinData) {
			iSkinDataOffset = iCurrentVertexOffset;

			VertexElement.Offset = static_cast<WORD>(iCurrentVertexOffset);
			VertexElement.Usage = D3DDECLUSAGE_BLENDWEIGHT;
			VertexElement.Type = D3DDECLTYPE_UBYTE4N;
			m_VertexElements.push_back(VertexElement);

			InputElement.SemanticName = "BLENDWEIGHT";
			InputElement.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			InputElement.AlignedByteOffset = static_cast<UINT>(iCurrentVertexOffset);
			m_InputLayout.push_back(InputElement);

			iCurrentVertexOffset += GetElementSizeFromDeclType(VertexElement.Type);

			VertexElement.Offset = static_cast<WORD>(iCurrentVertexOffset);
			VertexElement.Usage = D3DDECLUSAGE_BLENDINDICES;
			VertexElement.Type = D3DDECLTYPE_UBYTE4;
			m_VertexElements.push_back(VertexElement);

			InputElement.SemanticName = "BLENDINDICES";
			InputElement.Format = DXGI_FORMAT_R8G8B8A8_UINT;
			InputElement.AlignedByteOffset = static_cast<UINT>(iCurrentVertexOffset);
			m_InputLayout.push_back(InputElement);

			iCurrentVertexOffset += GetElementSizeFromDeclType(VertexElement.Type);
		}

		if (m_VertexFormat.m_bNormal) {
			iNormalOffset = iCurrentVertexOffset;

			VertexElement.Offset = static_cast<WORD>(iCurrentVertexOffset);
			VertexElement.Usage = D3DDECLUSAGE_NORMAL;
			VertexElement.Type = static_cast<BYTE>(dwNormalType);
			m_VertexElements.push_back(VertexElement);

			InputElement.SemanticName = "NORMAL";
			InputElement.Format = dwNormalTypeDXGI;
			InputElement.AlignedByteOffset = static_cast<UINT>(iCurrentVertexOffset);
			m_InputLayout.push_back(InputElement);

			iCurrentVertexOffset += GetElementSizeFromDeclType(VertexElement.Type);
		}

		if (m_VertexFormat.m_bVertexColor) {
			iColorOffset = iCurrentVertexOffset;

			VertexElement.Offset = static_cast<WORD>(iCurrentVertexOffset);
			VertexElement.Usage = D3DDECLUSAGE_COLOR;
			VertexElement.Type = static_cast<BYTE>(dwColorType);
			m_VertexElements.push_back(VertexElement);

			InputElement.SemanticName = "COLOR";
			InputElement.Format = dwColorTypeDXGI;
			InputElement.AlignedByteOffset = static_cast<UINT>(iCurrentVertexOffset);
			m_InputLayout.push_back(InputElement);

			iCurrentVertexOffset += GetElementSizeFromDeclType(VertexElement.Type);
		}

		if (m_VertexFormat.m_uUVSetCount > 0) {
			iUVOffset = iCurrentVertexOffset;
			for (UINT t = 0; t < m_VertexFormat.m_uUVSetCount; t++)
			{
				VertexElement.Offset = static_cast<WORD>(iCurrentVertexOffset);
				VertexElement.Usage = D3DDECLUSAGE_TEXCOORD;

				InputElement.SemanticName = "TEXCOORD";
				InputElement.AlignedByteOffset = static_cast<UINT>(iCurrentVertexOffset);

				switch (m_VertexFormat.m_uUVSetSize)
				{
					case 1:
					VertexElement.Type = D3DDECLTYPE_FLOAT1;
					InputElement.Format = DXGI_FORMAT_R32_FLOAT;
					break;

					case 2:
					if (bCompressVertexData) {
						VertexElement.Type = D3DDECLTYPE_FLOAT16_2;
						InputElement.Format = DXGI_FORMAT_R16G16_FLOAT;
					}
					else {
						VertexElement.Type = D3DDECLTYPE_FLOAT2;
						InputElement.Format = DXGI_FORMAT_R32G32_FLOAT;
					}	break;

					case 3:
					if (bCompressVertexData) {
						VertexElement.Type = D3DDECLTYPE_FLOAT16_4;
						InputElement.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
					}
					else {
						VertexElement.Type = D3DDECLTYPE_FLOAT3;
						InputElement.Format = DXGI_FORMAT_R32G32B32_FLOAT;
					} break;

					case 4:
					if (bCompressVertexData) {
						VertexElement.Type = D3DDECLTYPE_FLOAT16_4;
						InputElement.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
					}
					else {
						VertexElement.Type = D3DDECLTYPE_FLOAT4;
						InputElement.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
					} break;

					default:
					continue;
				}

				VertexElement.UsageIndex = static_cast<BYTE>(t);
				m_VertexElements.push_back(VertexElement);

				InputElement.SemanticIndex = t;
				m_InputLayout.push_back(InputElement);

				iCurrentVertexOffset += GetElementSizeFromDeclType(VertexElement.Type);
			}
			VertexElement.UsageIndex = 0;
			InputElement.SemanticIndex = 0;
		}

		if (m_VertexFormat.m_bTangent) {
			iTangentOffset = iCurrentVertexOffset;

			VertexElement.Offset = static_cast<WORD>(iCurrentVertexOffset);
			VertexElement.Usage = D3DDECLUSAGE_TANGENT;
			VertexElement.Type = static_cast<BYTE>(dwNormalType);
			m_VertexElements.push_back(VertexElement);

			InputElement.SemanticName = "TANGENT";
			InputElement.Format = dwNormalTypeDXGI;
			InputElement.AlignedByteOffset = static_cast<UINT>(iCurrentVertexOffset);
			m_InputLayout.push_back(InputElement);

			iCurrentVertexOffset += GetElementSizeFromDeclType(VertexElement.Type);
		}

		if (m_VertexFormat.m_bBinormal) {
			iBinormalOffset = iCurrentVertexOffset;

			VertexElement.Offset = static_cast<WORD>(iCurrentVertexOffset);
			VertexElement.Usage = D3DDECLUSAGE_BINORMAL;
			VertexElement.Type = static_cast<BYTE>(dwNormalType);
			m_VertexElements.push_back(VertexElement);

			InputElement.SemanticName = "BINORMAL";
			InputElement.Format = dwNormalTypeDXGI;
			InputElement.AlignedByteOffset = static_cast<UINT>(iCurrentVertexOffset);
			m_InputLayout.push_back(InputElement);

			iCurrentVertexOffset += GetElementSizeFromDeclType(VertexElement.Type);
		}

		assert(m_VertexElements.size() == m_InputLayout.size());

		// save vertex size
		uVertexSize = iCurrentVertexOffset;
		if (uVertexSize == 0) {
			return;
		}

		// create vertex buffer and allocate storage
		size_t nVerts = VertexArray.size();

		m_pVB = std::make_unique<Export_VB>();
		m_pVB->SetVertexCount(nVerts);
		m_pVB->SetVertexSize(uVertexSize);
		m_pVB->Allocate();

		if (iPositionOffset != -1) {
			m_pVBPositions.reset(new D3DXVECTOR3[nVerts]);
			memset(m_pVBPositions.get(), 0, sizeof(D3DXVECTOR3) * nVerts);
		}

		if (iNormalOffset != -1) {
			m_pVBNormals.reset(new D3DXVECTOR3[nVerts]);
			memset(m_pVBNormals.get(), 0, sizeof(D3DXVECTOR3) * nVerts);
		}

		if (iUVOffset != -1) {
			m_pVBTexCoords.reset(new D3DXVECTOR2[nVerts]);
			memset(m_pVBTexCoords.get(), 0, sizeof(D3DXVECTOR2) * nVerts);
		}

		// copy raw vertex data into the packed vertex buffer
		for (size_t i = 0; i < nVerts; i++)
		{
			auto pDestVertex = m_pVB->GetVertex(i);
			Export_Mesh_Vertex* pSrcVertex = VertexArray[i];

			if (!pSrcVertex) {
				continue;
			}

			if (iPositionOffset != -1) {
				auto pDest = reinterpret_cast<D3DXVECTOR3*>(pDestVertex + iPositionOffset);
				TransformPosition(pDest, &pSrcVertex->Position);

				memcpy(&m_pVBPositions[i], pDest, sizeof(D3DXVECTOR2));
			}

			if (iNormalOffset != -1) {
				TransformAndWriteVector((BYTE*)pDestVertex + iNormalOffset, &m_pVBNormals[i], pSrcVertex->Normal, dwNormalType);
			}

			if (iSkinDataOffset != -1) {
				BYTE* pDest = (BYTE*)pDestVertex + iSkinDataOffset;
				BYTE* pBoneWeights = pDest;

				*pDest++ = static_cast<BYTE>(pSrcVertex->BoneWeights.x * 255.0f);
				*pDest++ = static_cast<BYTE>(pSrcVertex->BoneWeights.y * 255.0f);
				*pDest++ = static_cast<BYTE>(pSrcVertex->BoneWeights.z * 255.0f);
				*pDest++ = static_cast<BYTE>(pSrcVertex->BoneWeights.w * 255.0f);

				NormalizeBoneWeights(pBoneWeights);

				*pDest++ = pSrcVertex->BoneIndices.x;
				*pDest++ = pSrcVertex->BoneIndices.y;
				*pDest++ = pSrcVertex->BoneIndices.z;
				*pDest++ = pSrcVertex->BoneIndices.w;
			}

			if (iTangentOffset != -1) {
				TransformAndWriteVector((BYTE*)pDestVertex + iTangentOffset, nullptr, pSrcVertex->Tangent, dwNormalType);
			}

			if (iBinormalOffset != -1) {
				TransformAndWriteVector((BYTE*)pDestVertex + iBinormalOffset, nullptr, pSrcVertex->Binormal, dwNormalType);
			}

			if (iUVOffset != -1) {
				UINT iTangentSpaceIndex = 0;

				if (m_VertexFormat.m_uUVSetCount > iTangentSpaceIndex) {
					if (m_VertexFormat.m_uUVSetSize > 1) {
						memcpy(&m_pVBTexCoords[i], &pSrcVertex->TexCoords[iTangentSpaceIndex], sizeof(D3DXVECTOR2));
					}
				}

				size_t uStride = m_VertexFormat.m_uUVSetSize * sizeof(float);
				BYTE* pDest = (BYTE*)pDestVertex + iUVOffset;

				for (UINT t = 0; t < m_VertexFormat.m_uUVSetCount; t++) {
					memcpy(pDest, &pSrcVertex->TexCoords[t], uStride);
					pDest += uStride;
				}
			}
		}
	}

	void Exp_Mesh::TransformPosition(D3DXVECTOR3* pDestPosition, const D3DXVECTOR3* pSrcPosition) const
	{
		D3DXVECTOR3 SrcVector;
		if (pSrcPosition == pDestPosition) {
			SrcVector = *pSrcPosition;
			pSrcPosition = &SrcVector;
		}

		if (m_bMaxConversion) {
			pDestPosition->x = pSrcPosition->x * m_fUnitScale;
			pDestPosition->y = pSrcPosition->z * m_fUnitScale;
			pDestPosition->z = pSrcPosition->y * m_fUnitScale;
		}
		else {
			const float flipZ = m_bFlipZ ? -1.0f : 1.0f;

			pDestPosition->x = pSrcPosition->x * m_fUnitScale;
			pDestPosition->y = pSrcPosition->y * m_fUnitScale;
			pDestPosition->z = pSrcPosition->z * m_fUnitScale * flipZ;
		}
	}

	void Exp_Mesh::TransformAndWriteVector(BYTE* pDest, D3DXVECTOR3* normal, const D3DXVECTOR3& Src, DWORD dwDestFormat)
	{
		D3DXVECTOR3 SrcTransformed;
		TransformDirection(&SrcTransformed, &Src);

		if (normal) {
			memcpy(normal, &SrcTransformed, sizeof(D3DXVECTOR3));
		}

		switch (dwDestFormat) {
			case D3DDECLTYPE_FLOAT3:
			*reinterpret_cast<D3DXVECTOR3*>(pDest) = SrcTransformed;
			break;

			default:
			assert(false);
			break;
		}
	}

	void Exp_Mesh::TransformDirection(D3DXVECTOR3* pDestDirection, const D3DXVECTOR3* pSrcDirection) const
	{
		D3DXVECTOR3 SrcVector;

		if (pSrcDirection == pDestDirection) {
			SrcVector = *pSrcDirection;
			pSrcDirection = &SrcVector;
		}

		if (m_bMaxConversion) {
			pDestDirection->x = pSrcDirection->x;
			pDestDirection->y = pSrcDirection->z;
			pDestDirection->z = pSrcDirection->y;
		}
		else {
			const float flipZ = m_bFlipZ ? -1.0f : 1.0f;

			pDestDirection->x = pSrcDirection->x;
			pDestDirection->y = pSrcDirection->y;
			pDestDirection->z = pSrcDirection->z * flipZ;
		}
	}

	void Exp_Mesh::TransformMatrix(D3DXMATRIX* pDestMatrix, const D3DXMATRIX* pSrcMatrix) const
	{
		D3DXMATRIX SrcMatrix;
		if (pSrcMatrix == pDestMatrix) {
			memcpy(&SrcMatrix, pSrcMatrix, sizeof(D3DXMATRIX));
			pSrcMatrix = &SrcMatrix;
		}
		memcpy(pDestMatrix, pSrcMatrix, sizeof(D3DXMATRIX));

		if (m_bFlipZ) {
			pDestMatrix->_13 = -pSrcMatrix->_13;
			pDestMatrix->_23 = -pSrcMatrix->_23;
			pDestMatrix->_43 = -pSrcMatrix->_43;

			pDestMatrix->_31 = -pSrcMatrix->_31;
			pDestMatrix->_32 = -pSrcMatrix->_32;
			pDestMatrix->_34 = -pSrcMatrix->_34;
		}

		// Apply the global unit scale to the translation components of the matrix.
		pDestMatrix->_41 *= m_fUnitScale;
		pDestMatrix->_42 *= m_fUnitScale;
		pDestMatrix->_43 *= m_fUnitScale;
	}

	float Exp_Mesh::TransformLength(float fInputLength) const
	{
		return fInputLength * m_fUnitScale;
	}
	// Sets unit scale for exporting all geometry - works with characters too.
	void Exp_Mesh::SetUnitScale(const float fScale)
	{
		m_fUnitScale = fScale;
	}

	void Exp_Mesh::SetZFlip(const bool bFlip)
	{
		m_bFlipZ = bFlip;
	}

	Exp_Mesh::~Exp_Mesh()
	{
	}
}