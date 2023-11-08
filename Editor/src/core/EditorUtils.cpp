#include <imgui.h>
#include <imgui_internal.h>
#include "pch.h"
#include "EditorUtils.h"
#include "AssetUtility.h"

namespace overflow::edit
{
	//region Operators
	bool operator !=(const ImVec2& v1, const ImVec2& v2) { return v1.x != v2.x || v1.y != v2.y; }
	bool operator ==(const ImVec2& v1, const ImVec2& v2) { return v1.x == v2.x && v1.y == v2.y; }
	
	ImVec2 operator -(const ImVec2& v1, const ImVec2& v2) { return { v1.x - v2.x, v1.y - v2.y }; }
	void operator -=(ImVec2& v1, const ImVec2& v2) { v1.x -= v2.x; v1.y -= v2.y; }
	
	ImVec2 operator +(const ImVec2& v1, const ImVec2& v2) { return { v1.x + v2.x, v1.y + v2.y }; }
	void operator +=(ImVec2& v1, const ImVec2& v2) { v1.x += v2.x; v1.y += v2.y; }
	
	ImVec2 operator *(const ImVec2& v1, float f) { return { v1.x * f, v1.y * f }; }
	void operator *=(ImVec2& v1, float f) { v1.x *= f; v1.y *= f; }
	//endregion

#define VAR_NAME ImGui::TableNextRow();\
				 ImGui::TableSetColumnIndex(0);\
				 ImGui::Text("%s", label);\
				 ImGui::TableNextColumn();

	//region Basics
	bool DrawBool(const char* label, bool& v)
	{
		bool valueChanged = false;
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
		VAR_NAME

		std::string str = "##";
		str.append(label);
		valueChanged = ImGui::Checkbox(str.c_str(), &v);

		ImGui::PopStyleVar();
		return valueChanged;
	}

	bool DrawString(const char* label, std::string& v)
	{
		static std::string old_String;
		bool valueChanged = false;
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
		VAR_NAME

		std::string str = "##";
		str.append(label);

		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
		valueChanged = ImGui::InputText(str.data(), &v[0], 128);
		ImGui::PopStyleVar();
		return valueChanged;
	}
	bool DrawStringBox(const char* label, std::string& v)
	{
		static std::string old_String;
		bool valueChanged = false;
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
		VAR_NAME

		std::string str = "##";
		str.append(label);

		valueChanged = ImGui::InputTextMultiline(str.data(), &v[0], 4096,
		                             { ImGui::GetContentRegionAvail().x, 100.0f });
		ImGui::PopStyleVar();
		return valueChanged;
	}

	bool DrawScalar(const char* label, ImGuiDataType data_type, void* v)
	{
		bool valueChanged = false;
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
		VAR_NAME

		std::string id = "##";
		id.append(label);
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
		valueChanged = ImGui::DragScalar(id.c_str(), data_type, v);

		ImGui::PopStyleVar();
		return valueChanged;
	}

	bool DrawNumber(const char* label, int16_t& v)   { return DrawScalar(label, ImGuiDataType_S16,    &v); }
	bool DrawNumber(const char* label, uint16_t& v)  { return DrawScalar(label, ImGuiDataType_U16,    &v); }
	bool DrawNumber(const char* label, int32_t& v)   { return DrawScalar(label, ImGuiDataType_S32,    &v); }
	bool DrawNumber(const char* label, uint32_t& v)  { return DrawScalar(label, ImGuiDataType_U32,    &v); }
	bool DrawNumber(const char* label, int64_t & v)  { return DrawScalar(label, ImGuiDataType_S64,    &v); }
	bool DrawNumber(const char* label, uint64_t & v) { return DrawScalar(label, ImGuiDataType_U64,    &v); }
	bool DrawNumber(const char* label, float_t& v)   { return DrawScalar(label, ImGuiDataType_Float,  &v); }
	bool DrawNumber(const char* label, double_t& v)  { return DrawScalar(label, ImGuiDataType_Double, &v); }
	//endregion
	//region Colored_Vectors
	bool DrawNoNameScalar(const char* label, ImGuiDataType data_type, void* v, float speed)
	{
		bool valueChanged = false;
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });

		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
		if(ImGui::DragScalar(label, data_type, v, speed)) valueChanged = true;

		ImGui::PopStyleVar();
		return valueChanged;
	}

	bool DrawVectorN(const char* label, ImGuiDataType data_type, int size, void* vec, void* resetValue)
	{
		bool valueChanged = false;
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
		VAR_NAME

		if(ImGui::BeginTable(label, size))
		{
			for (int i = 0; i < size; ++i)
				ImGui::TableSetupColumn(VECTOR_COLUMN_IDS[i].c_str(),
				                        ImGuiTableColumnFlags_WidthStretch, 70.0f);

			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);

			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

			size_t type_size = GDataTypeInfo[data_type].Size;
			void* ptr = vec;
			for (int i = 0; i < size; ++i)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, VECTOR_STYLES[i * 3]);
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, VECTOR_STYLES[i * 3 + 1]);
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, VECTOR_STYLES[i * 3 + 2]);
				if (ImGui::Button(VECTOR_NAMES[i].c_str(), buttonSize))
				{
					std::memcpy(ptr, resetValue, type_size);
					valueChanged = true;
				}
				ImGui::PopStyleColor(3);
				ImGui::SameLine();
				ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
				valueChanged |= DrawNoNameScalar(VECTOR_IDS[i].c_str(), data_type, ptr, 0.1f);
				ptr = (void*)((char*)ptr + type_size);

				if(i + 1 < size) ImGui::TableNextColumn();
			}

			ImGui::EndTable();
		}
		ImGui::PopStyleVar();

		ImGui::Spacing();
		return valueChanged;
	}

	bool DrawVector(const char* label, vec2& vec, float_t resetValue) { return DrawVectorN(label, ImGuiDataType_Float, 2, &vec.x, &resetValue); }
	bool DrawVector(const char* label, vec3& vec, float_t resetValue) { return DrawVectorN(label, ImGuiDataType_Float, 3, &vec.x, &resetValue); }
	bool DrawVector(const char* label, vec4& vec, float_t resetValue) { return DrawVectorN(label, ImGuiDataType_Float, 4, &vec.x, &resetValue); }

	bool DrawVector(const char* label, vec2i& vec, int32_t resetValue) { return DrawVectorN(label, ImGuiDataType_S32, 2, &vec.x, &resetValue); }
	bool DrawVector(const char* label, vec3i& vec, int32_t resetValue) { return DrawVectorN(label, ImGuiDataType_S32, 3, &vec.x, &resetValue); }
	bool DrawVector(const char* label, vec4i& vec, int32_t resetValue) { return DrawVectorN(label, ImGuiDataType_S32, 4, &vec.x, &resetValue); }

	bool DrawColor(const char* label, vec4& vec)
	{
		bool valueChanged = false;
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
		VAR_NAME

		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
		valueChanged = ImGui::ColorEdit4(label, &vec[0],
										 ImGuiColorEditFlags_NoLabel |
										 ImGuiColorEditFlags_NoSidePreview);

		ImGui::PopStyleVar();

		ImGui::Spacing();
		return valueChanged;
	}
//endregion
	//region Search
	struct AssetResult
	{
		utils::EditorAsset asset;
		size_t searchIterator;
	};

	bool Draw_AssetSelection(const char* label, Asset*& selected, AssetType type,
	                         int singleLineCount, float columnWidth)
	{
		static std::vector<utils::EditorAsset> s_Results;
		static std::vector<AssetResult> s_Sorted_Results;
		static bool s_SelectionIsOpen = false;
		static bool s_SelectionWasOpen = false;
		static int s_Selection = 0;
		static std::string s_OldText;
		static char s_TextBuffer[128] = "";

		strcpy_s(s_TextBuffer, sizeof(s_TextBuffer), s_OldText.c_str());
		utils::EditorAsset selection;

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });

		VAR_NAME

		std::string comboName = "none";
		if(selected != nullptr)
		{
			selection = utils::GetAsset(selected->GetUUID());
			comboName = selection.Name;
		}
		std::string comboId = "##";
		comboId.append(label);
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);

		s_SelectionWasOpen = s_SelectionIsOpen;
		bool isOpen = ImGui::BeginCombo(comboId.c_str(), comboName.c_str());
		if(ImGui::IsItemActivated())
		{
			s_Selection = 0;
			s_Results.clear();
			s_Sorted_Results.clear();
			s_SelectionIsOpen = true;
			utils::FindAssets(type, s_Results);
			for (auto& asset : s_Results)
				s_Sorted_Results.push_back({ asset, 0 });
		}

		bool changed = false;

		if(isOpen)
		{
			int maxCount = std::floor((float) s_Sorted_Results.size() / (float) singleLineCount);
			s_Selection = std::clamp(s_Selection, 0, maxCount);
			float fontSize = ImGui::GetFontSize() + 6;
			if(ImGui::BeginTable("##__Header", 3, 0, { 0, fontSize }))
			{
				ImGui::TableSetupColumn("##col_i_1", ImGuiTableColumnFlags_WidthFixed, fontSize);
				ImGui::TableSetupColumn("##col_i_2", ImGuiTableColumnFlags_WidthStretch, columnWidth);
				ImGui::TableSetupColumn("##col_i_3", ImGuiTableColumnFlags_WidthFixed, fontSize);
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				if(ImGui::Button("<", { fontSize, fontSize }))
				{
					s_Selection--;
					s_Selection = std::max(0, s_Selection);
				}
				ImGui::TableNextColumn();
				ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);

				if(ImGui::InputText("##__text", s_TextBuffer, sizeof s_TextBuffer))
				{
					std::string_view newText = s_TextBuffer;

					if(newText != s_OldText)
					{
						s_Sorted_Results.clear();
						for (auto& asset : s_Results)
						{
							std::string_view sv = asset.Name;
							auto it = overflow::utils::i_case_contains(sv, newText);
							if(it != sv.end())
								s_Sorted_Results.push_back({ asset, (size_t)std::distance(sv.begin(), it) });
						}
						s_OldText = newText;
						std::sort(s_Sorted_Results.begin(), s_Sorted_Results.end(),
						          [](const AssetResult& a, const AssetResult& b) {
							          return a.searchIterator < b.searchIterator;
						          });
					}
				}

				ImGui::TableNextColumn();
				if(ImGui::Button(">", { fontSize, fontSize }))
				{
					s_Selection++;
					s_Selection = std::min(maxCount, s_Selection);
				}
				ImGui::EndTable();
			}
			ImGui::Separator();
			int limit = std::min((s_Selection + 1) * singleLineCount, (int)s_Sorted_Results.size());
			for (int i = s_Selection * singleLineCount; i < limit; ++i)
			{
				if(ImGui::Selectable(s_Sorted_Results[i].asset.Name.c_str(),
				                     s_Sorted_Results[i].asset.Asset == selected))
				{
					selected = s_Sorted_Results[i].asset.Asset;
					changed = true;
				}

				ImGui::SameLine(100.0f);
				ImGui::Text("%s", s_Sorted_Results[i].asset.LocationCompat.c_str());
			}
			ImGui::EndCombo();
		}

		ImGui::PopStyleVar();
		return changed;
	}

	bool Draw_AssetSelection(const char* label, Shader*& selected,
	                          int singleLineCount, float columnWidth)
	{
		Asset* asset = selected;
		if(Draw_AssetSelection(label, asset, AssetType::Shader,
								   singleLineCount, columnWidth))
		{
			selected = (Shader*)asset;
			return true;
		}
		return false;
	}
	bool Draw_AssetSelection(const char* label, Tex2D*& selected,
	                         int singleLineCount, float columnWidth)
	{
		Asset* asset = selected;

		bool isOpen = Draw_AssetSelection(label, asset, AssetType::Tex2D,
		                                  singleLineCount, columnWidth);

		if(selected != nullptr)
		{
			ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::GetFontSize() * 2 - ImGui::GetStyle().ItemSpacing.x);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
			float buttonSize = ImGui::GetFontSize();

			ImGui::Image((void*)(size_t)selected->TexID(), { buttonSize, buttonSize });
		}

		if(isOpen)
		{
			selected = (Tex2D*)asset;
			return true;
		}
		return false;
	}
	bool Draw_AssetSelection(const char* label, Mesh*& selected,
	                        int singleLineCount, float columnWidth)
	{
		Asset* asset = selected;
		if(Draw_AssetSelection(label, asset, AssetType::Mesh,
		                       singleLineCount, columnWidth))
		{
			selected = (Mesh*)asset;
			return true;
		}
		return false;
	}
	bool Draw_AssetSelection(const char* label, Material*& selected,
	                            int singleLineCount, float columnWidth)
	{
		Asset* asset = selected;
		if(Draw_AssetSelection(label, asset, AssetType::Material,
		                       singleLineCount, columnWidth))
		{
			selected = (Material*)asset;
			return true;
		}
		return false;
	}
	//endregion
}