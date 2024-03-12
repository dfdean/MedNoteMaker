////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2013-2024 Dawson Dean
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////
//
// To Add A Control Panel:
// =======================
// 1. medNoteMaker.html - Add the HTML <div> in the "CONTROL PANEL CATALOG" section
//       I use the original procedure from noteBuilderPlans.cpp as a template
// 2. noteBuilderTables.cpp - Add the div ID to the "controlPanelID" in the appropriate entry in g_AllPlansDeclaration.
// 3. noteBuilderTables.cpp - Add all option entries from the control panel html to g_AllOptionsDeclaration[]
// 4. noteBuilderPlans.cpp - MedNote_StartNewPlanSection() needs to pass in the correct g_AllPlansDeclaration entry name in the second param.
/////////////////////////////////////////////////////////////////////////////


/////////////////////////
var g_AllPlansDeclaration = {
    ///////////////////////////////////////////////////////////
    // Header and Footer Plans
    "PlanHeader" :     { "isSelected" : 1, "planSelectStatusHTMLElementID" : "PlanHeader", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "HeaderControlPanel", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "PlanFooter" :     { "isSelected" : 1, "planSelectStatusHTMLElementID" : "PlanFooter", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "FooterControlPanel", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},

    ///////////////////////////////////////////////////////////
    // Chief Complaint Plans
    "DyspneaPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "DyspneaPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "DyspneaCP", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "NSTEMIPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "NSTEMIPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "NSTEMI_CONTROL_PANEL_ID", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "DKAPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "DKAPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "DKA_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "GIBleedPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "GIBleedPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "GI_BLEED_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "SepsisPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "SepsisPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "SepsisControlPanel", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "StrokePlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "StrokePlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "Stroke_CONTROL_PANEL_ID", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "DICPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "DICPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "DIC_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "PEDVTPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "PEDVTPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "PEDVT_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "CovidPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "CovidPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "CovidControlPanel", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "EncephalopathyPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "EncephalopathyPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "ENCEPHALOPATHY_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "DysphagiaPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "DysphagiaPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "DYSPHAGIA_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "SyncopePlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "SyncopePlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "SYNCOPE_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "OncologyPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "OncologyPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "ONCOLOGY_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "HepatitisPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "HepatitisPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "HEPATITIS_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "PancPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "PancPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "PANCREATITIS_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "GISymptomsPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "GISymptomsPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "GISymptoms_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "PneumoniaPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "PneumoniaPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "PneumoniaControlPanel", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "CADPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "CADPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "CADControls", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "CHFPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "CHFPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "CHFControls", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "COPDPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "COPDPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "COPDControls", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "AFibPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "AFibPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "AFib_CONTROL_PANEL_ID", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "PreopPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "PreopPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "PREOP_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},

    ///////////////////////////////////////////////////////////
    // Complex Comorbidity OR Chief Complaint Plans
    "CirrhosisPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "CirrhosisPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "CirrhosisControls", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "HemoDialysisPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "HemoDialysisPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "ESRDControls", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "RenalTransplantPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "RenalTransplantPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "RenalTransplantControlPanel", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    
    ///////////////////////////////////////////////////////////
    // Renal Plans
    "AKIPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "AKIPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "AKIControls", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "CKDPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "CKDPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "CKD_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "NephroticPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "NephroticPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "NephroticControlPanel", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "IVContrastPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "IVContrastPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "IV_CONTRAST_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "MBDPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "MBDPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "MBD_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "HTNPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "HTNPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "HypertensionControlPanel", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "AcidBasePlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "AcidBasePlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "AcidBaseControls", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "HyponatremiaPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "HyponatremiaPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "HyponatremiaControlPanel", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "HypokalemiaPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "HypokalemiaPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "LOW_POTASSIUM_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "HyperkalemiaPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "HyperkalemiaPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "HIGH_POTASSIUM_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "HypERnatremiaPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "HypERnatremiaPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "HIGH_SODIUM_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "HypomagnesemiaPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "HypomagnesemiaPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "LOW_MG_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "HypoPhosPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "HypoPhosPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "LOW_PHOS_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "HypoCalcemiaPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "HypoCalcemiaPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "LOW_CALCIUM_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "HypERCalcemiaPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "HypERCalcemiaPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "HIGH_CALCIUM_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "ParathyroidectomyPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "ParathyroidectomyPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "ParathyroidectomyCP", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "VitDPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "VitDPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "LOW_VITD_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "NephrolithiasisPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "NephrolithiasisPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "NephrolithiasisControlPanel", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},


    ///////////////////////////////////////////////////////////
    // Non-Complex Comorbidities
    "AsthmaPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "AsthmaPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "AsthmaControlPanel", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "OSAPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "OSAPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "OSAControlPanel", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "HypothyroidPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "HypothyroidPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "HYPOTHYROID_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "DiabetesPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "DiabetesPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "Diabetes_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "AnemiaPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "AnemiaPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "ANEMIA_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "GoutPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "GoutPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "GOUT_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "BPHPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "BPHPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "BPH_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},

    ///////////////////////////////////////////////////////////
    // Preexisting Conditions
    "EtOHPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "EtOHPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "ALCOHOL_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "PressureUlcersPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "PressureUlcersPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "PRESSURE_ULCER_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "HepCPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "HepCPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "HEPATITIS_C_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},

    ///////////////////////////////////////////////////////////
    // Other Plans
    "IllicitDrugsPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "IllicitDrugsPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "ILLICITS_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "PalliativePlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "PalliativePlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "PALLIATIVE_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "LegFracturePlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "LegFracturePlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "LEG_FRACTURE_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "MigrainesPlan" : { "isSelected" : 0, "planSelectStatusHTMLElementID" : "MigrainesPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "MIGRAINES_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},


    ///////////////////////////////////////////////////////////
    // SINGLE_LINE PLANS
    "DepressionPlan" : { "isSelected" : 0, "planSelectStatusHTMLElementID" : "DepressionPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "MOOD_DISORDER_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "TobaccoPlan" : { "isSelected" : 0, "planSelectStatusHTMLElementID" : "TobaccoPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "TOBACCO_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "GERDPlan" : { "isSelected" : 0, "planSelectStatusHTMLElementID" : "GERDPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "GERD_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "ObesityPlan" : { "isSelected" : 0, "planSelectStatusHTMLElementID" : "ObesityPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "OBESITY_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "MalnutritionPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "MalnutritionPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "MALNUTRITION_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "WeaknessPlan" : { "isSelected" : 0, "planSelectStatusHTMLElementID" : "WeaknessPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "WEAKNESS_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},


    ///////////////////////////////////////////////////////////
    // Last Plan
    "PreventionPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "PreventionPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "PREVENTION_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},
    "BillingPlan" :     { "isSelected" : 0, "planSelectStatusHTMLElementID" : "BillingPlan", "planSelectStatusHTMLElement" : null, "PrintFunction" : null, "PrintSingleLine" : 0, "controlPanelID" : "BILLING_CONTROL_PANEL", "activeControlPanel" : null, "planTableRowElement" : null, "planTextHTMLElement" : null},

}; // g_AllPlansDeclaration





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CONTROL PANEL OPTIONS
//
//  g_AllOptionsDeclaration is an object
//      It has one attribute for each entry.
//      The name of the attribute is the name of the option, which is also used as the "id" attribute int he HTML control that toggles this option.
//      The value of the attribute is another object
//
//  for (var key in g_AllOptionsDeclaration) {
//      if (g_AllOptionsDeclaration.hasOwnProperty(key)) {
//          var entry = g_AllOptionsDeclaration[key];
//      }
//  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
var g_AllOptionsDeclaration = {
    ///////////////////////////////////////////////////////////
    // PHYSICAL EXAM
    ///////////////////////////////////////////////////////////
    // General
    "AOx3Option" : { "ButtonLabelList" : ["AOx3", "AOx1", "FollowsCmds"], "ValueList" : ["AOx3", "AOx1", "awake, follows commands"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "NADOption" : { "ButtonLabelList" : ["NAD", "MildDistress", "Agitated"], "ValueList" : ["no acute distress", "moderate distress", "agitated"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "NourishedOption" : { "ButtonLabelList" : ["Nourished", "Obese", "Weak", "Cachectic"], "ValueList" : ["well-nourished", "obese", "weak and ill-appearing", "frail, cachectic"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "GCSEyesOption" : { "ButtonLabelList" : ["GCS E=4", "GCS E=3", "GCS E=2", "GCS E=1", "GCS E=NT"], "ValueList" : ["GCS E=Spontaneously (+4)", "GCS E=On verbal command (+3)", "GCS E=To pain (+2)", "GCS E=No eye opening (+1)", "GCS E=Not testable (NT)"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "GCSVerbalOption" : { "ButtonLabelList" : ["GCS V=5", "GCS V=4", "GCS V=3", "GCS V=2", "GCS V=1", "GCS V=NT"], "ValueList" : ["GCS V=Oriented (+5)", "GCS V=Confused (+4)", "GCS V=Inappropriate words (+3)", "GCS V=Incomprehensible sounds (+2)", "GCS V=No verbal response (+1)", "GCS V=Not testable (NT)"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "GCSMotorOption" : { "ButtonLabelList" : ["GCS M=6", "GCS M=5", "GCS M=4", "GCS M=3", "GCS M=2", "GCS M=1", "GCS M=NT"], "ValueList" : ["GCS M=Obeys commands (+6)", "GCS M=Localizes pain (+5)", "GCS M=Withdrawal from pain (+4)", "GCS M=Flexion to pain (+3)", "GCS M=Extension to pain (+2)", "GCS M=No motor response (+1)", "GCS M=Not testable (NT)"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // HEENT:
    "OPCOption" : { "ButtonLabelList" : ["OPC", "Edentulous", "Poor Teeth"], "ValueList" : ["oral pharynx clear", "edentulous", "poor dentition with multiple missing teeth"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "MucosaMoistOption" : { "ButtonLabelList" : ["Moist"], "ValueList" : ["mucosa moist"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "IctericOption" : { "ButtonLabelList" : ["Anicteric", "Icteric"], "ValueList" : ["anicteric", "scleral icterus"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Neck:
    "SuppleOption" : { "ButtonLabelList" : ["Supple"], "ValueList" : ["supple"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "ThyromegalyOption" : { "ButtonLabelList" : ["Euthyroid"], "ValueList" : ["no thyromegaly"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "TrachOption" : { "ButtonLabelList" : ["Trach"], "ValueList" : ["Trach in place"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Cardiovascular:
    "HROption" : { "ButtonLabelList" : ["RRR", "IrregIrreg", "Tachy"], "ValueList" : ["regular s1/s2", "irregular-irregular s1/s2", "tachycardic but regular s1/s2"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "MurmurOption" : { "ButtonLabelList" : ["NoMurmur", "LUSB", "RUSB"], "ValueList" : ["no murmurs", "II/VI systolic murmur loudest at LUSB", "II/VI systolic murmur loudest at RUSB"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    "MurmurIncrease" : { "ButtonLabelList" : ["MurmurInc", "NoChange"], "ValueList" : ["murmur increases on inspiration", "murmur does not change on inspiration"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    "JVDOption" : { "ButtonLabelList" : ["NoJVD", "+JVD"], "ValueList" : ["no JVD", "+JVD"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "EdemaOption" : { "ButtonLabelList" : ["NoEdema", "1+Pitting", "2+pitting"], "ValueList" : ["no lower extremity edema", "1+ pitting lower extremity edema", "2+ pitting lower extremity edema"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PulsesOption" : { "ButtonLabelList" : ["2+", "1+"], "ValueList" : ["2+ Pulses bilateral pedal", "1+ Pulses bilateral pedal"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Pulmonary:
    "CBTAOption" : { "ButtonLabelList" : ["Clear"], "ValueList" : ["clear"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RalesOption" : { "ButtonLabelList" : ["NoRales", "WetCrackles", "FineCrackles"], "ValueList" : ["no crackles", "wet crackles at bases", "fine crackles"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "WheezesOption" : { "ButtonLabelList" : ["NoWheezes", "Wheezes"], "ValueList" : ["no wheezes", "expiratory wheezes"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "LaboredOption" : { "ButtonLabelList" : ["NonLabored", "Tachypnic", "Labored"], "ValueList" : ["non-labored", "tachypnic", "labored"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Abd:
    "BowelSoundsOption" : { "ButtonLabelList" : ["BowelSounds", "Hypoactive", "Hyperactive"], "ValueList" : ["normal bowel sounds", "hypoactive bowel sounds", "hyperactive bowel sounds"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "SoftOption" : { "ButtonLabelList" : ["Soft", "Firm", "Guarding"], "ValueList" : ["soft", "firm", "guarding"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "NTOption" : { "ButtonLabelList" : ["NT", "RUQ TTP", "Central TTP", "All Quads TTP"], "ValueList" : ["non-tender", "tenderness in RUQ", "epigastric tenderness", "tender to palpation in all quadrants"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "NDOption" : { "ButtonLabelList" : ["ND", "Distended"], "ValueList" : ["non-distended", "distended"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "ReboundOption" : { "ButtonLabelList" : ["NoRebound", "Rebound"], "ValueList" : ["no rebound tenderness", "+rebound tenderness"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "GTubeOption" : { "ButtonLabelList" : ["G-Tube"], "ValueList" : ["G-Tube present"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Muskuloskeletal:
    "RoMArmsOption" : { "ButtonLabelList" : ["ArmsOK"], "ValueList" : ["full RoM in BUE"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RoMKneesOption" : { "ButtonLabelList" : ["LegsOK"], "ValueList" : ["full RoM in Knees"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RoMHipsOption" : { "ButtonLabelList" : ["HipsOK"], "ValueList" : ["full RoM in Hips"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "AmputationOption" : { "ButtonLabelList" : ["Left BKA", "Right BKA", "BKA", "Left AKA", "Right AKA", "AKA"], "ValueList" : ["Left BKA", "Right BKA", "BKA", "Left AKA", "Right AKA", "AKA"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "WoundVacOption" : { "ButtonLabelList" : ["Wound Vac"], "ValueList" : ["Wound Vac in place"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Neurologic:
    "AsterixisOption" : { "ButtonLabelList" : ["NoAsterixis", "Asterixis"], "ValueList" : ["no asterixis", "+asterixis"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "CNIntactOption" : { "ButtonLabelList" : ["CN OK"], "ValueList" : ["CN II-XII grossly intact"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "5/5BUEOption" : { "ButtonLabelList" : ["5/5 BUE", "4/5 LUE", "3/5 LUE", "1/5 LUE", "4/5 RUE", "3/5 RUE", "1/5 RUE"], "ValueList" : ["5/5 BUE strength", "4/5 LUE strength", "3/5 LUE strength", "1/5 LUE strength", "4/5 RUE strength", "3/5 RUE strength", "1/5 RUE strength"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "5/5BLEOption" : { "ButtonLabelList" : ["5/5 BLE", "4/5 LLE", "3/5 LLE", "1/5 LLE", "4/5 RLE", "3/5 RLE", "1/5 RLE"], "ValueList" : ["5/5 BLE strength", "4/5 LLE strength", "3/5 LLE strength", "1/5 LLE strength", "4/5 RLE strength", "3/5 RLE strength", "1/5 RLE strength"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "BabinskiOption" : { "ButtonLabelList" : ["Neg Babinski", "+Babinski"], "ValueList" : ["Negative Babinski", "+Babinski"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Dermatologic:
    "RashesOption" : { "ButtonLabelList" : ["No Rashes", "stasis dermatitis", "Erythema", "Macular", "Papular"], "ValueList" : ["no rashes", "stasis dermatitis bilateral distal lower extremities", "erythema", "macular rash", "papular rash"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "LesionsOption" : { "ButtonLabelList" : ["No Lesions", "C/D/I wound"], "ValueList" : ["no lesions", "surgical wound is clean/dry/intact"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "UlcersOption" : { "ButtonLabelList" : ["No Ulcers"], "ValueList" : ["no ulcers"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Access:
    "AccessTypeOption" : { "ButtonLabelList" : ["TDC", "LUE AVF", "RUE AVF", "IJ", "Fem"], "ValueList" : ["Tunnel Dialysis Catheter", "LUE AVF", "RUE AVF", "IJ temporary dialysis catheter", "Femoral temporary dialysis catheter"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "AccessBruitOption" : { "ButtonLabelList" : ["+bruit", "No bruit"], "ValueList" : ["audible bruit", "no audible bruit"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "AccessThrillOption" : { "ButtonLabelList" : ["+thrill", "No thrill"], "ValueList" : ["palpable thrill", "no palpable thrill"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "AccessAugmentationOption" : { "ButtonLabelList" : ["+augmentation", "No augmentation"], "ValueList" : ["augmentation", "no augmentation"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},



    ///////////////////////////////////////////////////////////
    // REVIEW OF SYSTEMS
    ///////////////////////////////////////////////////////////
    "RoSCannotAssessOption" : { "ButtonLabelList" : ["Cannot Assess"], "ValueList" : ["Cannot assess due to patient mental status"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RoS14PointOption" : { "ButtonLabelList" : ["14PointsReviewed"], "ValueList" : ["A fourteen (14) point Review of Systems was performed and is otherwise negative except as per the history above and also the following specific positive and negative findings:"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Constitutional
    "RosFeverOption" : { "ButtonLabelList" : ["NoFever", "+fevers"], "ValueList" : ["no fevers", "+ fevers"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosWeaknessOption" : { "ButtonLabelList" : ["NoWeakness", "+Weakness"], "ValueList" : ["no weakness", "+ weakness"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosFatigueOption" : { "ButtonLabelList" : ["NoFatigue", "+Fatigue"], "ValueList" : ["no fatigue", "+ fatigue"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosWeightLossOption" : { "ButtonLabelList" : ["NoWtLoss", "+WtrLoss"], "ValueList" : ["no weight loss", "+ unintentional weight loss"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosAppetiteOption" : { "ButtonLabelList" : ["OKAppetite", "PoorAppetite"], "ValueList" : ["normal appetite", "+ poor appetite"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Eyes
    "RosDryEyesOption" : { "ButtonLabelList" : ["NoDry", "Dry"], "ValueList" : ["no dry eyes", "+ dry"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosBlurredVisionOption" : { "ButtonLabelList" : ["NoBlur", "+Blurred"], "ValueList" : ["no blurred vision", "+ blurred vision"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosVisionChangesOption" : { "ButtonLabelList" : ["NoVisionChanges", "+VisionChanges"], "ValueList" : ["no vision changes", "+ vision changes"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Ear/Nose/Mouth/Throat
    "RosHearingOption" : { "ButtonLabelList" : ["HearingOK", "HearingLoss", "Tinnitis"], "ValueList" : ["no hearing loss", "+ hearing loss", "+tinnitis"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosMouthOption" : { "ButtonLabelList" : ["MouthOK", "DryMouth", "OralLesions", "NoTeeth"], "ValueList" : ["no oral lesions", "+ dry mouth", "+ oral lesions", "+missing teth"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosNoseOption" : { "ButtonLabelList" : ["NoseOK", "Rhinorrhea"], "ValueList" : ["no rhinorrhea", "+ rhinorrhea"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Cardiovascular
    "RosChestPainOption" : { "ButtonLabelList" : ["NoAngina", "Angina"], "ValueList" : ["no chest pain", "+ chest pain"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosPalpitationsOption" : { "ButtonLabelList" : ["NoPalpitations", "Palpitations"], "ValueList" : ["no palpitations", "+ palpitations"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosEdemaOption" : { "ButtonLabelList" : ["No Edema", "Edema"], "ValueList" : ["no edema", "+ edema"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Respiratory
    "RosDyspneaOption" : { "ButtonLabelList" : ["No Dyspnea", "Dyspnea"], "ValueList" : ["no shortness of breath", "+ shortness of breath"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosCoughOption" : { "ButtonLabelList" : ["No Cough", "Cough"], "ValueList" : ["no cough", "+ cough"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosDoEOption" : { "ButtonLabelList" : ["No DoE", "DoE"], "ValueList" : ["no dyspnea on exertion", "+ dyspnea on exertion"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosSputumOption" : { "ButtonLabelList" : ["No Sputum", "Sputum Changes"], "ValueList" : ["no change in sputum production", "+change in sputum production"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Gastrointestinal
    "RosNauseaOption" : { "ButtonLabelList" : ["No Nausea", "Nausea"], "ValueList" : ["no nausea", "+ nausea"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosVomitingOption" : { "ButtonLabelList" : ["No Vomiting", "Vomiting"], "ValueList" : ["no vomiting", "+ vomiting"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosDiarrheaOption" : { "ButtonLabelList" : ["No Diarrhea", "Diarrhea"], "ValueList" : ["no diarrhea", "+ diarrhea"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosConstipationOption" : { "ButtonLabelList" : ["No Constipation", "Constipation"], "ValueList" : ["no constipation", "+ constipation"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosAbdomPainOption" : { "ButtonLabelList" : ["No Abdom Pain", "Abdom Pain"], "ValueList" : ["no abdominal pain", "+ abdominal pain"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Genitourinary
    "RosStrainingOption" : { "ButtonLabelList" : ["NoStraining", "Straining"], "ValueList" : ["no urinary straining", "+ urinary straining"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosPartialVoidOption" : { "ButtonLabelList" : ["NoPartialVoid", "PartialVoid"], "ValueList" : ["no partial voiding", "+ partial voiding"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosWeakStreamOption" : { "ButtonLabelList" : ["NoWakStream", "WeakStream"], "ValueList" : ["no weak stream", "+ weak stream"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosUrinaryHesitancyOption" : { "ButtonLabelList" : ["NoHesitancy", "Hesitancy"], "ValueList" : ["no urinary hesitancy", "+ urinary hesitancy"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosHematuriaOption" : { "ButtonLabelList" : ["NoHematuria", "Hematuria"], "ValueList" : ["no hematuria", "+ hematuria"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosDysuriaOption" : { "ButtonLabelList" : ["NoDysuria", "Dysuria"], "ValueList" : ["no dysuria", "+ dysuria"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Musculoskeletal
    "RosBackPainOption" : { "ButtonLabelList" : ["NoBackPain", "BackPain"], "ValueList" : ["no back pain", "+ back pain"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosShoulderPainOption" : { "ButtonLabelList" : ["NoShoulderPain", "ShoulderPain"], "ValueList" : ["no shoulder pain", "+shoulder pain"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosHipPainOption" : { "ButtonLabelList" : ["NoHipPain", "HipPain"], "ValueList" : ["no hip pain", "+ hip pain"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosKneePainOption" : { "ButtonLabelList" : ["NoKneePain", "KneePain"], "ValueList" : ["no knee pain", "+ knee pain"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Integumentary
    "RosRashOption" : { "ButtonLabelList" : ["NoRashes", "Rashes"], "ValueList" : ["no rashes", "+ rashes"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosLesionOption" : { "ButtonLabelList" : ["NoLesions", "Lesions"], "ValueList" : ["no lesions", "+ lesions"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosBruisingOption" : { "ButtonLabelList" : ["NoBruising", "Bruising"], "ValueList" : ["no bruising", "+ bruising"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Neurological
    "RosHeadachesOption" : { "ButtonLabelList" : ["NoHeadaches", "Headaches"], "ValueList" : ["no headaches", "+headaches"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosDizzinessOption" : { "ButtonLabelList" : ["NoDizziness", "Dizziness"], "ValueList" : ["no dizziness", "+dizziness"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosNumbnessOption" : { "ButtonLabelList" : ["NoNumbness", "Numbness"], "ValueList" : ["no sensation loss", "+sensation loss"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosBurningOption" : { "ButtonLabelList" : ["NoBurning", "Burning"], "ValueList" : ["no burning", "+burning"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Psychiatric
    "RosDepressionOption" : { "ButtonLabelList" : ["NoDepression", "Depression"], "ValueList" : ["no depression", "+depression"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosAnxietyOption" : { "ButtonLabelList" : ["NoAnxiety", "Anxiety"], "ValueList" : ["no anxiety", "+anxiety"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosHallucinationOption" : { "ButtonLabelList" : ["NoHallucinations", "Hallucinations"], "ValueList" : ["no hallucinations", "+hallucinations"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Hematologic
    "RosMelenaOption" : { "ButtonLabelList" : ["NoMelena", "Melena"], "ValueList" : ["no melena", "+melena"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosHematocheziaOption" : { "ButtonLabelList" : ["NoHematochezia", "Hematochezia"], "ValueList" : ["no hematochezia", "+hematochezia"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosHematemesisOption" : { "ButtonLabelList" : ["NoHematemesis", "Hematemesis"], "ValueList" : ["no hematemesis", "+hematemesis"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosCoffeeGroundOption" : { "ButtonLabelList" : ["NoCoffeeGround", "CoffeeGround"], "ValueList" : ["no coffee ground emesis", "+coffee ground emesis"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Endocrine
    "RosHeatOption" : { "ButtonLabelList" : ["NoHheatIntolerance", "HeatIntolerance"], "ValueList" : ["no heat intolerance", "+heat intolerance"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosColdOption" : { "ButtonLabelList" : ["NoColdIntolerance", "ColdIntolerance"], "ValueList" : ["no cold intolerance", "+cold intolerance"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosThirstOption" : { "ButtonLabelList" : ["NoThirst", "Thirst"], "ValueList" : ["no excessive thirst", "+ excessive thirst"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    ///////////////////
    // Allergic
    "RosAllergiesOption" : { "ButtonLabelList" : ["NoAllergies", "Allergies"], "ValueList" : ["no allergic reactions", "+allergic reactions"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "RosInfectionsOption" : { "ButtonLabelList" : ["NoInfections", "Infections"], "ValueList" : ["no recurrent infections", "+recurrent infections"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},



    ///////////////////////////////////////////////////////////
    // Past Medical History
    ///////////////////////////////////////////////////////////
    "PMHxHypertension" : { "ButtonLabelList" : ["HTN"], "ValueList" : ["Hypertension"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PMHxDiabetes" : { "ButtonLabelList" : ["DM2", "DM1"], "ValueList" : ["Diabetes, Type 2", "Diabetes, Type 1"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PMHxHeartFailure" : { "ButtonLabelList" : ["CHF"], "ValueList" : ["Heart Failure"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PMHxCOPD" : { "ButtonLabelList" : ["COPD"], "ValueList" : ["COPD"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PMHxCirrhosis" : { "ButtonLabelList" : ["Cirrhosis"], "ValueList" : ["Cirrhosis"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PMHxCoronaryArteryDisease" : { "ButtonLabelList" : ["CAD"], "ValueList" : ["Coronary Artery Disease"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PMHxCKD" : { "ButtonLabelList" : ["CKD"], "ValueList" : ["Stroke"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PMHxStroke" : { "ButtonLabelList" : ["CVA"], "ValueList" : ["Stroke"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PMHxHypoThyroid" : { "ButtonLabelList" : ["Hypothyroid"], "ValueList" : ["Hypothyroid"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PMHxAnxiety" : { "ButtonLabelList" : ["Anxiety"], "ValueList" : ["Anxiety"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PMHxAFib" : { "ButtonLabelList" : ["AFib"], "ValueList" : ["Atrial Fibrillation"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PMHxDepression" : { "ButtonLabelList" : ["Depression"], "ValueList" : ["Depression"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PMHxTobacco" : { "ButtonLabelList" : ["Tobacco"], "ValueList" : ["Tobacco"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PMHxEtOH" : { "ButtonLabelList" : ["EtOH"], "ValueList" : ["Alcohol Use Disorder"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},


    ///////////////////////////////////////////////////////////
    // Past Surgical History
    ///////////////////////////////////////////////////////////
    "PSHxCholecystectomy" : { "ButtonLabelList" : ["CCY"], "ValueList" : ["Cholecystectomy"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PSHxArthroscopy" : { "ButtonLabelList" : ["Ortho"], "ValueList" : ["Arthroscopy"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PSHxAppendectomy" : { "ButtonLabelList" : ["Appy"], "ValueList" : ["Appendectomy"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PSHxHysterectomy" : { "ButtonLabelList" : ["Hyst"], "ValueList" : ["Hysterectomy"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PSHxTonsillectomy" : { "ButtonLabelList" : ["Tonsils"], "ValueList" : ["Tonsillectomy"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PSHxCABG" : { "ButtonLabelList" : ["CABG"], "ValueList" : ["Coronary Artery Bypass Grafting"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PSHxCSection" : { "ButtonLabelList" : ["C-Section"], "ValueList" : ["C-Section"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PSHxBTL" : { "ButtonLabelList" : ["Tubal"], "ValueList" : ["Tubal Ligation"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},


    ///////////////////////////////////////////////////////////
    // Past Social History
    ///////////////////////////////////////////////////////////
    "PHxTobacco" : { "ButtonLabelList" : ["Past Use", "Current", "Smokeless", "Never"], "ValueList" : ["Past Use", "Currently Smokes", "Uses Smokeless Tobacco", "Never"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PHxAlcohol" : { "ButtonLabelList" : ["Light Use", "Past", "Current", "Never"], "ValueList" : ["Light Use", "Past Heavy use", "Current heavy use", "Never"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PHxDrugs" : { "ButtonLabelList" : ["None", "THC", "Cocaine", "Heroin", "Meth"], "ValueList" : ["None", "THC", "Cocaine", "Heroin", "Methamphetamine"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},


    ///////////////////////////////////////////////////////////
    // Family Medical History
    ///////////////////////////////////////////////////////////
    "FHxMotherDM" : { "ButtonLabelList" : ["DM"], "ValueList" : ["Diabetes"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "FHxMotherHTN" : { "ButtonLabelList" : ["HTN"], "ValueList" : ["Hypertension"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "FHxMotherCAD" : { "ButtonLabelList" : ["CAD"], "ValueList" : ["CAD"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "FHxMotherCancer" : { "ButtonLabelList" : ["Cancer"], "ValueList" : ["Cancer"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "FHxMotherCOPD" : { "ButtonLabelList" : ["COPD"], "ValueList" : ["COPD"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "FHxMotherNone" : { "ButtonLabelList" : ["None"], "ValueList" : ["No known medical issues"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    "FHxFatherDM" : { "ButtonLabelList" : ["DM"], "ValueList" : ["Diabetes"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "FHxFatherHTN" : { "ButtonLabelList" : ["HTN"], "ValueList" : ["Hypertension"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "FHxFatherCAD" : { "ButtonLabelList" : ["CAD"], "ValueList" : ["CAD"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "FHxFatherCancer" : { "ButtonLabelList" : ["Cancer"], "ValueList" : ["Cancer"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "FHxFatherCOPD" : { "ButtonLabelList" : ["COPD"], "ValueList" : ["COPD"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "FHxFatherNone" : { "ButtonLabelList" : ["None"], "ValueList" : ["No known medical issues"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},

    "FHxSiblingsDM" : { "ButtonLabelList" : ["DM"], "ValueList" : ["Diabetes"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "FHxSiblingsHTN" : { "ButtonLabelList" : ["HTN"], "ValueList" : ["Hypertension"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "FHxSiblingsCAD" : { "ButtonLabelList" : ["CAD"], "ValueList" : ["CAD"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "FHxSiblingsCancer" : { "ButtonLabelList" : ["Cancer"], "ValueList" : ["Cancer"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},


    ///////////////////////////////////////////////////////////
    // Home Medications
    ///////////////////////////////////////////////////////////
    "PHxMedsMetoprolol" : { "ButtonLabelList" : ["Metoprolol"], "ValueList" : ["Metoprolol"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PHxMedsLisinopril" : { "ButtonLabelList" : ["Lisinopril"], "ValueList" : ["Lisinopril"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PHxMedsLosartan" : { "ButtonLabelList" : ["Losartan"], "ValueList" : ["Losartan"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PHxMedsAmlodipine" : { "ButtonLabelList" : ["Amlodipine"], "ValueList" : ["Amlodipine"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PHxMedsHCTZ" : { "ButtonLabelList" : ["HCTZ"], "ValueList" : ["Hydrochlorothiazide"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PHxMedsPantoprazole" : { "ButtonLabelList" : ["PPI", "PPI"], "ValueList" : ["Pantoprazole", "Omeprazole"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PHxMedsOxycodone" : { "ButtonLabelList" : ["Oxy", "Hydro"], "ValueList" : ["Oxycodone", "Hydrocodone/Apap"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},


    "PHxMedsCoreg" : { "ButtonLabelList" : ["Carvedilol"], "ValueList" : ["Carvedilol"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PHxMedsFurosemide" : { "ButtonLabelList" : ["Furosemide"], "ValueList" : ["Furosemide"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PHxMedsAsa" : { "ButtonLabelList" : ["Aspirin"], "ValueList" : ["Aspirin"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PHxMedsAtorvastatin" : { "ButtonLabelList" : ["Atorva"], "ValueList" : ["Atorvastatin"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PHxMedsApixaban" : { "ButtonLabelList" : ["Apixaban"], "ValueList" : ["Apixaban"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PHxMedsClopidogrel" : { "ButtonLabelList" : ["Clopidogrel"], "ValueList" : ["Clopidogrel"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PHxMedsAlbuterol" : { "ButtonLabelList" : ["Albuterol"], "ValueList" : ["Albuterol inhaler"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PHxMedsFluticSalm" : { "ButtonLabelList" : ["Flutic/Salm"], "ValueList" : ["Fluticasone/Salmoterol"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PHxMedsTiotropium" : { "ButtonLabelList" : ["Tiotropium"], "ValueList" : ["Tiotropium"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PHxMedsMontelukast" : { "ButtonLabelList" : ["Montelukast"], "ValueList" : ["Montelukast"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PHxMedsTamsulosin" : { "ButtonLabelList" : ["Tamsulosin"], "ValueList" : ["Tamsulosin"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PHxMedsMetformin" : { "ButtonLabelList" : ["Metformin"], "ValueList" : ["Metformin"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},




    ///////////////////////////////////////////////////////////
    // Allergies
    ///////////////////////////////////////////////////////////
    "PHxAllergyPenicillins" : { "ButtonLabelList" : ["PCN"], "ValueList" : ["Penicillins"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},
    "PHxAllergySulfa" : { "ButtonLabelList" : ["Sulfa"], "ValueList" : ["Sulfa medications"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanHeader"},


    ///////////////////////////////////////////////////////////
    // FOOTER
    ///////////////////////////////////////////////////////////
    // Diet
    "DietOption" : { "ButtonLabelList" : ["Regular", "Low Na", "DM diet", "Renal", "Dysphagia", "Clears", "NPO"], "ValueList" : ["Regular diet", "Low sodium diet", "3-carb diabetic diet", "Renal diet", "Diet as discussed for Dysphagia", "Clear liquid diet", "NPO"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},

    // DVT Prophylaxis
    "DVTProphylaxisOption" : { "ButtonLabelList" : ["Enoxaparin", "Heparin", "SCDs", "See AFib", "See PE/DVT", "See MI", "See Above"], "ValueList" : ["Enoxaparin subcu", "Heparin subcu (due to reduced renal clearance)", "SCDs (due to suspected bleed)", "As discussed above for A-Fib", "As discussed above for PE/DVT", "As discussed above for MI", "As discussed above"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},

    // DischargePlanning
    "DispoDisplayDischargePlanning" : { "ButtonLabelList" : ["Display"], "ValueList" : ["Display"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},
    "DispoPTOption" : { "ButtonLabelList" : ["PT/OT"], "ValueList" : ["Physical Therapy, Occupational Therapy"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},
    "DispoIVAbxOption" : { "ButtonLabelList" : ["IV Antibiotics"], "ValueList" : ["IV Antibiotics"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},
    "DispoDysphagiaOption" : { "ButtonLabelList" : ["Dysphagia"], "ValueList" : ["Dysphagia"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},
    "DispoAMSOption" : { "ButtonLabelList" : ["Agitation"], "ValueList" : ["Agitation"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},
    "DispoMedicalOption" : { "ButtonLabelList" : ["Medical"], "ValueList" : ["Not medically ready"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},
    "DispoInsuranceOption" : { "ButtonLabelList" : ["Placement"], "ValueList" : ["Placement"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},

    // PT Recommendations
    "DispoPTRecsOption" : { "ButtonLabelList" : ["Acute Rehab", "Subacute", "Home-assist", "Home"], "ValueList" : ["Acute Rehab", "Subacute Rehab", "Home with assist", "Home"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},
    "DispoPatientAgreeOption" : { "ButtonLabelList" : ["Agrees", "Disagrees"], "ValueList" : ["the patient agrees", "the patient declines and will go home"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},

    // Discharge Equipment
    "WeaknessHospBed1Option" : { "ButtonLabelList" : ["Hosp Bed1"], "ValueList" : ["The patient has medical conditions that require positioning of the body in ways not feasible with an ordinary bed"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},
    "WeaknessHospBed2Option" : { "ButtonLabelList" : ["Hosp Bed1"], "ValueList" : ["The patient needs the head of the bed to be elevated more than 30 degrees most of the time due to chromic pulmonary disease. Pillows and wedges have been attempted and ruled out"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},
    "WeaknessWheelchairOption" : { "ButtonLabelList" : ["Wheelchair"], "ValueList" : ["The patient requires a wheelchair for activities of daily living at home such as toileting, grooming, bathing and transportation to medical appointments. Patient can only ambulate short distances with a walker and so a walker cannot sufficiently resolve the mobility limitation. Use of a wheelchair will improve the patient's ability to perform mobility related activities and the patient has agreed to do so. Patient has a caregiver to assist with wheelchair or the patient can self-propel a wheelchair."], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},

    // Discharge Followup Appointments
    "DispoClinicPCPOption" : { "ButtonLabelList" : ["PCP"], "ValueList" : ["Primary Care"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},
    "DischargeFollowUpGI" : { "ButtonLabelList" : ["GI"], "ValueList" : ["Gastroenterology clinic"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},
    "DischargeFollowUpID" : { "ButtonLabelList" : ["ID"], "ValueList" : ["Infectious Disease Clinic"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},
    "DischargeFollowUpEndocrine" : { "ButtonLabelList" : ["Endocrine"], "ValueList" : ["Endocrinology clinic"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},
    "DischargeFollowUpRenal" : { "ButtonLabelList" : ["Renal"], "ValueList" : ["Nephrology clinic"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},
    "DischargeFollowUpCards" : { "ButtonLabelList" : ["Cards"], "ValueList" : ["Cardiology clinic"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},
    "DischargeFollowUpOnc" : { "ButtonLabelList" : ["Onc"], "ValueList" : ["Oncology Clinic"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},
    "DischargeFollowUpNeuro" : { "ButtonLabelList" : ["Neuro"], "ValueList" : ["Neurology Clinic"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},
    "DischargeFollowUpSurgery" : { "ButtonLabelList" : ["Surgery"], "ValueList" : ["Surgery Clinic"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},



    // Discharge Meds
    "DispoPneumovaxOption" : { "ButtonLabelList" : ["Pneumovax"], "ValueList" : ["On discharge, give Pneumovax"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},
    "DispoHAVVaccineOption" : { "ButtonLabelList" : ["HAV Vax"], "ValueList" : ["On discharge, give HAV Vaccine"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},
    "DispoHBVVaccineOption" : { "ButtonLabelList" : ["HBV Vax"], "ValueList" : ["On discharge, give HBV Vaccine"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},
    "DispoNarcanOption" : { "ButtonLabelList" : ["Narcan"], "ValueList" : ["On discharge, prescribe Narcan"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},

    // Code
    "CodeStatusOption" : { "ButtonLabelList" : ["Full Code", "DNR", "DNR-OK Intub"], "ValueList" : ["FULL CODE", "DNR/DNI", "DNR, Intubation OK"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "PlanFooter"},


    ///////////////////////////////////////////////////////////
    // CIRRHOSIS
    ///////////////////////////////////////////////////////////
    // General
    "CirrhosisPossibleOption" : { "ButtonLabelList" : ["Possible", "Likely", "Decompensated"], "ValueList" : ["Possible", "Likely", "Decompensated"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisCoagulopathyOption" : { "ButtonLabelList" : ["Coagulopathy"], "ValueList" : ["Coagulopathy"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisThrombocytopeniaOption" : { "ButtonLabelList" : ["Thrombocytopenia"], "ValueList" : ["Thrombocytopenia"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisCauseOption" : { "ButtonLabelList" : ["EtOH", "NASH", "ViralHep"], "ValueList" : ["The suspected cause is Alcoholic", "The suspected cause is NASH", "The suspected cause is Viral Hepatitis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisBiopsyRecordOption" : { "ButtonLabelList" : ["No Biopsy", "Likely", "Biopsy"], "ValueList" : ["No liver biopsy found in the available medical record", "No liver biopsy record found, but there are other findings conststent with Cirrhosis", "Biopsy proven"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},


    // Labs and Inputs
    "Cirrhosis_Ascites_Modifier" : { "ButtonLabelList" : ["None", "Slight", "Large"], "ValueList" : ["None", "Slight", "Large" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "Cirrhosis_Encephalopathy_Modifier" : { "ButtonLabelList" : ["None", "Grade 1", "Grade 2"], "ValueList" : ["None", "Grade 1", "Grade 2" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},

    ///////////////////
    // Scores
    "CirrhosisMELDOption" : { "ButtonLabelList" : ["MELD"], "ValueList" : ["MELD"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisElastographyOption" : { "ButtonLabelList" : ["Elastography"], "ValueList" : ["Abdominal Ultrasound with Elastography for possible Cirrhosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisBiopsyOption" : { "ButtonLabelList" : ["Biopsy"], "ValueList" : ["Liver Biopsy to confirm Cirrhosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},


    ///////////////////
    // Etiology
    "CirrhosisViralHepOption" : { "ButtonLabelList" : ["Hep A/B/C"], "ValueList" : ["Hepatitis A IgM, B surface antigen, B core antibody, C antibody"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},

    "CirrhosisANAOption" : { "ButtonLabelList" : ["ANA"], "ValueList" : ["ANA"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CirrhosisPlan"},

    "CirrhosisSmoothMuscleOption" : { "ButtonLabelList" : ["Smooth"], "ValueList" : ["anti-smooth muscle antibody"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisMitoOption" : { "ButtonLabelList" : ["Mitochondrial"], "ValueList" : ["anti-mitochondrial antibody"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisFerritinOption" : { "ButtonLabelList" : ["Ferritin"], "ValueList" : ["Ferritin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisCeruloplasmOption" : { "ButtonLabelList" : ["Ceruloplasm"], "ValueList" : ["Ceruloplasm"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisAntiTyypsinOption" : { "ButtonLabelList" : ["AntiTrypsin"], "ValueList" : ["alpha-1 antitrypsin level and phenotype"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},

    ///////////////////
    // Varices
    "CirrhosisEGDResultOption" : { "ButtonLabelList" : ["Latest EGD"], "ValueList" : ["Latest endoscopy on xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisGIBleedOption" : { "ButtonLabelList" : ["Bleed"], "ValueList" : ["Manage as discussed under GI bleed"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisPropranololOption" : { "ButtonLabelList" : ["Propranolol", "Nadolol", "Hold"], "ValueList" : ["Propranolol 20mg PO BID", "Nadolol 20mg PO once daily", "Hold non-selective beta blockers due to active bleed"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisCeftriaxoneOption" : { "ButtonLabelList" : ["Ceftriaxone"], "ValueList" : ["Ceftriaxone 1g IV daily x7 days"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CirrhosisPlan"},

    ///////////////////
    // Ascites
    "CirrhosisParaResultOption" : { "ButtonLabelList" : ["Para"], "ValueList" : ["Paracentesis (if any ascites) with labs on the ascitic fluid for albumin, total protein, LDH, cell count and gram-stain/culture to identify source and also rule out SBP"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisDopplersOption" : { "ButtonLabelList" : ["Dopplers"], "ValueList" : ["Abdominal Dopplers to rule out Portal Vein Thrombosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisLasixOption" : { "ButtonLabelList" : ["Lasix"], "ValueList" : ["Furosemide 40mg PO daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisSpironolactoneOption" : { "ButtonLabelList" : ["Spironolactone"], "ValueList" : ["Spironolactone 100mg PO daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisHoldDiureticsOption" : { "ButtonLabelList" : ["Hold Diuretics"], "ValueList" : ["Hold Diuretics"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisSBPAntibioticsOption" : { "ButtonLabelList" : ["SBP Treat", "7day SBP PPX", "Lifetime SBP PPX", "Continue Home"], "ValueList" : ["SBP treatment, Cefotaxime 2g IV Q8h. or Ceftriaxone (1g IV BID x5d)", "SBP Prophylaxis with Ceftriaxone 1g IV daily x7days", "If Cr over 1.5 and fluid Protein below 1.5, then SBP prophylaxis for life, with Fluoroquinolone", "Continue home antibiotics for lifetime SBP prophylaxis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "Cirrhosis2gNaDietOption" : { "ButtonLabelList" : ["2g Na Diet"], "ValueList" : ["2g Sodium diet"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisExplainDiureticsOption" : { "ButtonLabelList" : ["Diuretics Info"], "ValueList" : ["Diuretics (doses in 100:40 ratio up to 400:160). But, do not give diuretics if there is GI bleeding or hepatic encephalopathy or renal dysfunction (avoid hepatorenal)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},

    ///////////////////
    // Encephalopathy
    "CirrhosisNH3ResultOption" : { "ButtonLabelList" : ["NH3", "Check NH3"], "ValueList" : ["NH3=", "Check NH3"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisHEGradeOption" : { "ButtonLabelList" : ["Stage 0", "Stage 1", "Stage 2", "Stage 3", "Stage 4"], "ValueList" : ["Stage 0 (none)", "Stage 1 (mild confusion)", "Stage 2 (lethargy)", "Stage 3 (somnolent but arousable)", "Stage 4 (no response to stimuli)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisLactuloseOption" : { "ButtonLabelList" : ["Lactulose"], "ValueList" : ["Lactulose 30mL PO TID, titrate for 2-3 stools daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisRifaximinOption" : { "ButtonLabelList" : ["Rifaximin"], "ValueList" : ["Rifaximin 550mg PO BID"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},

    ///////////////////
    // Coagulopathy
    "CirrhosisNoBleedOption" : { "ButtonLabelList" : ["No Bleeding"], "ValueList" : ["No active signs of bleeding"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisCheckINROption" : { "ButtonLabelList" : ["Check INR", "Monitor"], "ValueList" : ["Check INR", "Monitor"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},

    ///////////////////
    // Hep A Immunity   
    "CirrhosisHAVVaccineOption" : { "ButtonLabelList" : ["Check HepA", "HAV immune", "HAV Vaccine"], "ValueList" : ["Check HepA IgG", "Patient is Hep A immune", "HAV Vaccine"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},

    ///////////////////
    // HCC Screen
    "CirrhosisShowHCCResultOption" : { "ButtonLabelList" : ["HCC Screen"], "ValueList" : ["Last abdominal US was xxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisHCCShowAFPOption" : { "ButtonLabelList" : ["Show AFP"], "ValueList" : ["Last AFP="], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisHCCCheckAFPOption" : { "ButtonLabelList" : ["Check AFP"], "ValueList" : ["Check AFP"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},

    ///////////////////
    // NASH
    "CirrhosisStatinOption" : { "ButtonLabelList" : ["Statin"], "ValueList" : ["Statin - Atorvastatin 40mg"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisVitEOption" : { "ButtonLabelList" : ["Vit E"], "ValueList" : ["Vitamin E (800 IU/day) but do not give if patient is diabetic"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},

    ///////////////////
    // Nutrition
    "CirrhosisZincOption" : { "ButtonLabelList" : ["Zinc"], "ValueList" : ["Zinc sulfate 220mg BID"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisThiamineOption" : { "ButtonLabelList" : ["Thiamine"], "ValueList" : ["Thiamine"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisVitaminOption" : { "ButtonLabelList" : ["Vitamin"], "ValueList" : ["Multivitamin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},

    ///////////////////
    // Transplant
    "CirrhosisStatusTransplantOption" : { "ButtonLabelList" : ["Xplant None", "Xplant In-Process", "Xplant Listed", "Xplant Unlisted", "Xplant NotListed"], "ValueList" : ["The patient is has not been evaluated for liver transplant", "The patient is currently being evaluated for liver transplant", "The patient is currently listed for liver transplant", "The patient is currently unlisted for liver transplant but will be reevaluated", "The patient has been evaluated and is not a candidate for liver transplant" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},
    "CirrhosisReferToTransplantOption" : { "ButtonLabelList" : ["Refer Transplant"], "ValueList" : ["Refer to liver transplant clinic for evaluation" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CirrhosisPlan"},



    ///////////////////////////////////////////////////////////
    // AKI
    ///////////////////////////////////////////////////////////
    "AKIOnCKDOption" : { "ButtonLabelList" : ["AKI", "AKI on CKD", "AKI on CKDIV", "AKI on CKDIIIb", "AKI on CKDIIIa", "AKI on CKDII"], "ValueList" : ["", " on Chronic Kidney Disease", " on Chronic Kidney Disease Stage IV", " on Chronic Kidney Disease Stage IIIb", " on Chronic Kidney Disease Stage IIIa", " on Chronic Kidney Disease Stage II"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIATNOption" : { "ButtonLabelList" : ["ATN"], "ValueList" : ["Acute Tubular Necrosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKICardiorenalOption" : { "ButtonLabelList" : ["Cardiorenal"], "ValueList" : ["Cardiorenal Syndrome"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},

    ///////////////////
    // Labs
    "AKITrendCrOption" : { "ButtonLabelList" : ["Trend Cr"], "ValueList" : ["Recent Creatinine Trend: "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKICystatinCTrendOption" : { "ButtonLabelList" : ["Trend CysC"], "ValueList" : ["Recent Cystatin C Trend: "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "AKIPlan"},
    "AKITrendUrineOption" : { "ButtonLabelList" : ["Trend Urine"], "ValueList" : ["Recent 24hr total urine output: "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIBaselineCrOption" : { "ButtonLabelList" : ["Baseline Cr"], "ValueList" : ["Baseline Cr is "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIBaselineGFROption" : { "ButtonLabelList" : ["Baseline Urine"], "ValueList" : ["xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIEstimateGFROption" : { "ButtonLabelList" : ["Estimate GFR"], "ValueList" : ["The current approximate eGFR (Creatinine is a lagging indicator) is: "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKI_Male_Modifier" : { "ButtonLabelList" : ["Male", "Female"], "ValueList" : ["male", "female" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},

    ///////////////////
    // KDIGO
    "AKIKDIGOOption" : { "ButtonLabelList" : ["KDIGO 1", "KDIGO 2", "KDIGO 3", "Calculated"], "ValueList" : ["This is KDIGO Stage 1 (Cr rose 0.3 or 1.5x to 2x baseline within 48hrs)", "This is KDIGO Stage 2 (Cr rose 2x to 3x baseline within 48hrs)", "This is KDIGO Stage 3 (Cr rose over 3x baseline within 48hrs or rose over 0.5 and now is over 4.0)", "CALCULATE"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},

    ///////////////////
    // Results
    "AKIFEUreaOption" : { "ButtonLabelList" : ["FEUrea=PreRenal", "FEUrea=Intrinsic", "COMPUTE"], "ValueList" : ["The FE-Urea is xxxx, which is less than 35 percent, consistent with a pre-renal cause (volume overload causing renal venous back pressure, hypovolemia, blood loss, sepsis)", "The FE-Urea is xxxx, which is over 35 percent, consistent with either an intrinsic-renal or post-renal cause (toxicity, ischemia, obstruction)", "COMPUTE"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},


    "AKIFENaOption" : { "ButtonLabelList" : ["FENa=PreRenal", "FENa=Intrinsic", "COMPUTE"], "ValueList" : ["The FENa is xxxx, which is less than 1 percent, consistent with a pre-renal cause (volume overload causing renal venous back pressure, hypovolemia, blood loss, sepsis)", "The FENa is xxxx, which is over 1 percent, consistent with either an intrinsic-renal or post-renal cause (toxicity, ischemia, obstruction)", "COMPUTE"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIUAInfectionOption" : { "ButtonLabelList" : ["UA Infection", "UA no infection"], "ValueList" : ["Urinalysis shows active infection", "Urinalysis is not consistent with infection"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIUSHydroOption" : { "ButtonLabelList" : ["US - Hydro", "US - No Hydro"], "ValueList" : ["Renal US shows hydro, suggesting obstruction", "Renal US does not show hydro, suggesting no obstruction"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKISpunUrineOption" : { "ButtonLabelList" : ["Spun Urine"], "ValueList" : ["On personal examination of the urine sediment, there were muddy brown casts consistent with acute tubular necrosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIUPCROption" : { "ButtonLabelList" : ["UPCR Low", "UPCR Nephritic", "UPCR Nephrotic"], "ValueList" : ["Urine protein/Creatinine ratio is low, so no nephrotic", "Urine protein/Creatinine ratio is elevated but not nephrotic", "Urine protein/Creatinine ratio is over 3.5 and nephrotic"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIAbdSoftOption" : { "ButtonLabelList" : ["Abd Soft", "Abd firm"], "ValueList" : ["On examination, the abdomen is soft and not tense, which goes against abdominal hypertension", "On examination, the abdomen is firm and may be consistent with abdominal hypertension"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIOverloadedOption" : { "ButtonLabelList" : ["Euvolemic", "Hypervolemic"], "ValueList" : ["The patient is clinically hypovolemic or euvolemic", "The patient is clinically hypervolemic with pitting edema"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKICXRResultsOption" : { "ButtonLabelList" : ["CXR Clear", "CXR Edema"], "ValueList" : ["Chest Xray shows no pulmonary edema", "Chest XRay shows pulmonary edema"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIBNPLowOption" : { "ButtonLabelList" : ["BNP Low", "BNP High"], "ValueList" : ["BNP is low", "BNP is elevated"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIHasFoleyOption" : { "ButtonLabelList" : ["Has Foley", "No Foley"], "ValueList" : ["The patient has a foley, which goes against obstruction", "The patient does not have a foley"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},

    ///////////////////
    // HRS Findings
    "AKIHRSAscitesOption" : { "ButtonLabelList" : ["Ascites", "No Ascites"], "ValueList" : ["ascites", "no ascites"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIHRSLowBPOption" : { "ButtonLabelList" : ["Low BP", "OK BP"], "ValueList" : ["low systolic blood pressure (usually below 115)", "systolic blood pressure is not significantly low"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIHRSLowNaOption" : { "ButtonLabelList" : ["Low Na", "OK Na"], "ValueList" : ["low serum sodium (usually below 130)", "serum sodium is not significantly low"], "htmlButton" : null, "toggleBehavior" : "OK/Bad/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},

    ///////////////////
    // Causes
    "AKIStartedOption" : { "ButtonLabelList" : ["AKI Start Date"], "ValueList" : ["Serum Creatinine began to rise on: "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKISepsisption" : { "ButtonLabelList" : ["Sepsis", "No Sepsis"], "ValueList" : ["hypotension from sepsis", "no sepsis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIInfectionOption" : { "ButtonLabelList" : ["Infection", "No Infection"], "ValueList" : ["infection with direct nephrotoxicity", "no infection"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIOverdiuresisOption" : { "ButtonLabelList" : ["Overdiuresis", "No overdiuresis"], "ValueList" : ["overdiuresis", "no recent diuretic changes"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKICHFOption" : { "ButtonLabelList" : ["CHF", "No CHF"], "ValueList" : ["volume overload causing renal venous back pressure", "no volume overload"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIObstructionOption" : { "ButtonLabelList" : ["Obstruction", "No Obstruction"], "ValueList" : ["post-renal obstruction", "no post-renal obstruction"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIPoorPOOption" : { "ButtonLabelList" : ["Poor PO", "OK PO"], "ValueList" : ["volume depletion from poor PO intake", "normal PO intake"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIBloodLossOption" : { "ButtonLabelList" : ["Blood Loss", "No Blood Loss"], "ValueList" : ["reduced renal perfusion from blood loss", "no significant blood loss"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKISurgeryOption" : { "ButtonLabelList" : ["Surgery", "No Surgery"], "ValueList" : ["recent surgery with intraoperative hypotension", "no recent surgery"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "AKIPlan"},
    "AKIAbdomCompartmentOption" : { "ButtonLabelList" : ["Abdom HTN", "No Abdom HTN"], "ValueList" : ["increased abdominal pressure", "no significant abdominal pressure"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIMedChangesOption" : { "ButtonLabelList" : ["Med Changes", "No Med changes"], "ValueList" : ["medication nephrotoxicity", "no recent nephrotoxic medication changes"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKINSAIDsOption" : { "ButtonLabelList" : ["NSAIDs", "No NSAIDs"], "ValueList" : ["chronic NSAID use", "no chronic NSAIDs"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "AKIPlan"},
    "AKICTContrastOption" : { "ButtonLabelList" : ["CT Contrast", "No recent IV contrast"], "ValueList" : ["recent CT with contrast", "no recent IV contrast"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIHRS1Option" : { "ButtonLabelList" : ["HRS 1"], "ValueList" : ["Hepatorenal syndrome type 1 (acute)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIHRS2Option" : { "ButtonLabelList" : ["HRS 2"], "ValueList" : ["Hepatorenal syndrome type 2 (chronic)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},

    ///////////////////
    // Workup
    "AKIUrinalysisOption" : { "ButtonLabelList" : ["Urinalysis"], "ValueList" : ["Urinalysis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKILytesOption" : { "ButtonLabelList" : ["Urine Lytes"], "ValueList" : ["urine Cr, Urea, Na, Protein"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKICPKOption" : { "ButtonLabelList" : ["CPK"], "ValueList" : ["CPK level"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIBladderPressureOption" : { "ButtonLabelList" : ["Bladder Pressure"], "ValueList" : ["Check bladder pressure. Pressures over 12mm indicated intra-abdominal hypertension, which may be due to liver disease, large volume IV fluids or more."], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIRenalUltrasoundOption" : { "ButtonLabelList" : ["Renal US"], "ValueList" : ["Renal Ultrasound to estimate degree of CKD with renal atrophy and degree of cortical thickening, also to rule hydronephrosis (which may be asymptomatic)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIDopplersOption" : { "ButtonLabelList" : ["Renal Dopplers"], "ValueList" : ["Renal artery/vein dopplers, to rule out Renal Vein Thrombosis and Renal Artery Stenosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIBNPOption" : { "ButtonLabelList" : ["BNP"], "ValueList" : ["NT-ProBNP"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKICXROption" : { "ButtonLabelList" : ["CXR"], "ValueList" : ["Chest XRay"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},

    ///////////////////
    // Treat
    "AKIFluidBolusOption" : { "ButtonLabelList" : ["Bolus LR", "Bolus NS", "Bolus Bicarb"], "ValueList" : ["IV fluid bolus, 1L LR", "IV fluid bolus, 1L NS", "IV fluid bolus, 1L D5W with 150mEq bicarb"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIMaintFluidOption" : { "ButtonLabelList" : ["IV Drip LR", "IV Drip NS", "IV Drip Bicarb"], "ValueList" : ["Continuous IV fluids, LR at 150mL/hr", "Continuous IV fluids, NS at 150mL/hr", "Continuous IV fluids, D5W with 150mEq Bicarb at 150mL/hr"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIHoldDiureticsOption" : { "ButtonLabelList" : ["Hold Diuretics"], "ValueList" : ["Hold Diuretics"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIHoldACEARBOption" : { "ButtonLabelList" : ["Hold Lisinopril", "Hold Losartan"], "ValueList" : ["Hold Lisinopril", "Hold Losartan"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIHoldNSAIDsOption" : { "ButtonLabelList" : ["Hold NSAIDs", "Replace NSAIDs"], "ValueList" : ["Hold NSAIDs (Ibuprofen and others)", "Hold systemic NSAIDs (Ibuprofen and others) and replace with topical Diclofenac"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},


    "AKIDiureseOption" : { "ButtonLabelList" : ["Diurese"], "ValueList" : ["Diurese as discussed for heart failure"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKITreatUTIOption" : { "ButtonLabelList" : ["Treat UTI"], "ValueList" : ["Treat UTI as discussed above"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKITreatBladderScanOption" : { "ButtonLabelList" : ["Bladder Scan"], "ValueList" : ["Q6h Bladder scan with PRN I/O cath for volume over 350mL"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKITreatFoleyOption" : { "ButtonLabelList" : ["Foley"], "ValueList" : ["Place foley"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKITreatTamsulosinOption" : { "ButtonLabelList" : ["Tamsulosin"], "ValueList" : ["Tamsulosin 0.4mg PO daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKITitratePipTazoOption" : { "ButtonLabelList" : ["Pip/Tazo"], "ValueList" : ["Reduce dose of Pip/Tazo"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIConvertOpioidsOption" : { "ButtonLabelList" : ["Opioids"], "ValueList" : ["Replace Oxycodone and Morphine with non-renally cleared medications: Hydromorphone)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKITitrateGabapentinOption" : { "ButtonLabelList" : ["Gabapentin"], "ValueList" : ["Reduce Gabapentin dose"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKITitrateColchicineOption" : { "ButtonLabelList" : ["Colchicine"], "ValueList" : ["Hold Colchicine"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},

    ///////////////////
    // HRS
    "AKIHRSAlbuminOption" : { "ButtonLabelList" : ["Albumin1g/kg", "Algumin25g/day"], "ValueList" : ["IV Albumin 1g/kg x2 days", "IV Albumin 25 gram daily x20days"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIHRSMidodrineOption" : { "ButtonLabelList" : ["Midodrine 5mgTID", "Midodrine 10mgTID", "Midodrine 12mgTID", "Midodrine 15mgTID"], "ValueList" : ["Midodrine 5mg PO TID", "Midodrine 10mg PO TID", "Midodrine 12mg PO TID", "Midodrine 15mg PO TID"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},
    "AKIHRSOctreotideOption" : { "ButtonLabelList" : ["Octreotide Subcu", "Octreotide Drip"], "ValueList" : ["Octreotide 100 mcg subcu TID", "Octreotide drip 50mcg/hr"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},

    ///////////////////
    // Recovery
    "AKIRecoveryFluidsOption" : { "ButtonLabelList" : ["Recovery Fluids"], "ValueList" : ["Match 1/2 to 2/3 of daily output with IV 1/2NS and taper down the replacement fluid so as not to perpetuate high urinary output. Daily total output was x mL, so give x mL IV 1/2 NS."], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AKIPlan"},




    ///////////////////////////////////////////////////////////
    // ACID-BASE
    ///////////////////////////////////////////////////////////
    "AcidBaseTypeOption": { "ButtonLabelList" : ["Acid Base", "Metabolic Acidosis", "Metabolic Alkalosis"], "ValueList" : ["Acid Base", "Metabolic Acidosis", "Metabolic Alkalosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},

    ///////////////////
    // pH
    "AcidBaseShowpHOption": { "ButtonLabelList" : ["Show pH"], "ValueList" : ["Show pH"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseInterpretpHOption": { "ButtonLabelList" : ["Interpret pH"], "ValueList" : ["xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},

    ///////////////////
    // Anion Gap
    "AcidBaseBicarbOption": { "ButtonLabelList" : ["Show Bicarb"], "ValueList" : ["xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseAnionGapOption": { "ButtonLabelList" : ["Anion Gap"], "ValueList" : ["xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseAdjustedAnionGapOption": { "ButtonLabelList" : ["Adjusted Gap"], "ValueList" : ["xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDeltaDeltaOption": { "ButtonLabelList" : ["Delta-Delta"], "ValueList" : ["xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},

    ///////////////////
    // Compensation
    "AcidBaseMetAcidCompOption": { "ButtonLabelList" : ["Met Acidosis"], "ValueList" : ["xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseMetAlkCompOption": { "ButtonLabelList" : ["Met Alkalosis"], "ValueList" : ["xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseRespAcidCompOption": { "ButtonLabelList" : ["Resp Acidosis"], "ValueList" : ["xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseRespAlkCompOption": { "ButtonLabelList" : ["Resp Alkalosis"], "ValueList" : ["xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},

    ///////////////////
    // Signs
    "AcidBaseLactateOption": { "ButtonLabelList" : ["Hi Lactate", "Low Lactate"], "ValueList" : ["Serum lactate is elevated which will cause a gap acidosis", "Serum lactate is normal"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBasePaCO2Option": { "ButtonLabelList" : ["Hi PaCO2", "Norm PaCO2", "Low PaCO2"], "ValueList" : ["PaCO2 is elevated which will cause a resp acidosis", "PaCO2 is normal", "PaCO2 is low which will cause a resp alkalosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBasePotassiumRTAOption": { "ButtonLabelList" : ["High K RTA", "Low K RTA"], "ValueList" : ["Serum potassium is normal or elevated, suggesting Type 4 (hypoaldosteronism) or voltage-dependent RTA", "Serum potassium is low, suggesting Type 1 (distal RTA) or Type 2 (proximal RTA)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseUrineKetonesOption": { "ButtonLabelList" : ["U-Ketones", "U No Ketones"], "ValueList" : ["UA has ketones, suggesting ketoacidosis from DKA or malnutrition", "UA has no ketones, not suggestive of ketoacidosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseShowCKOption": { "ButtonLabelList" : ["High CK", "Low CK"], "ValueList" : ["CK is elevated, suggesting rhabdo", "CK is normal, not suggestive of rhabdo"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},


    ///////////////////
    // Diagnose types of acid/base disturbances
    "AcidBaseShowProcessesOption": { "ButtonLabelList" : ["Show Processes"], "ValueList" : ["xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseMetGapAcidProcessOption": { "ButtonLabelList" : ["Gap Met Acidosis"], "ValueList" : ["Anion Gap Metabolic Acidosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseMetNonGapAcidProcessOption": { "ButtonLabelList" : ["Non-Gap Met Acidosis"], "ValueList" : ["Non-Gap Metabolic Acidosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseMetAlkProcessOption": { "ButtonLabelList" : ["Met Alkalosis"], "ValueList" : ["Metabolic Alkalosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseRespAcidProcessOption": { "ButtonLabelList" : ["Resp Acidosis"], "ValueList" : ["Respiratory Acidosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseRespAlkProcessOption": { "ButtonLabelList" : ["Resp Alkalosis"], "ValueList" : ["Respiratory Alkalosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},

    ///////////////////
    // General
    "AcidBaseCheckVBGOption" : { "ButtonLabelList" : ["Check VBG"], "ValueList" : ["venous blood gas"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseUrinepHOption" : { "ButtonLabelList" : ["Check UA"], "ValueList" : ["UA for ketones and urine pH"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},

    ///////////////////
    // Gap Acidosis
    "AcidBaseCheckLactateOption": { "ButtonLabelList" : ["Check Lactate"], "ValueList" : ["venous lactate"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseCheckCKOption": { "ButtonLabelList" : ["Check CK"], "ValueList" : ["Creatine Phosphokinase (to check for rhabdo)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseCheckOsmGapOption": { "ButtonLabelList" : ["Check Osm Gap"], "ValueList" : ["serum Osmolality"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseExplainOsmGapOption": { "ButtonLabelList" : ["Explain Osm Gap"], "ValueList" : ["xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},

    ///////////////////
    // Non-Gap Acidosis
    "AcidBaseCheckUrineLytesOption" : { "ButtonLabelList" : ["Check U-Lytes"], "ValueList" : ["random urine sodium, chloride, potassium to compute urine anion gap"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseShowUrineLytesOption" : { "ButtonLabelList" : ["Show U-Lytes"], "ValueList" : ["Show Urine Lytes"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseExplainUrineLytesOption" : { "ButtonLabelList" : ["Explain U-Lytes"], "ValueList" : ["Explain Urine Lytes"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseCheckAldoReninOption" : { "ButtonLabelList" : ["Check Aldo"], "ValueList" : ["Check morning Aldo and Renin and cortisol levels"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},

    ///////////////////
    // Alkalosis
    "AcidBaseCheckUClOption": { "ButtonLabelList" : ["Check U-Cl"], "ValueList" : ["random urine Chloride"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseShowUClOption": { "ButtonLabelList" : ["Show U-Cl"], "ValueList" : ["xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseExplainUClOption": { "ButtonLabelList" : ["Explain U-Cl"], "ValueList" : ["xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},

    ///////////////////
    // Resp Acidosis/Alkalosis
    "AcidBaseDeltapHOption": { "ButtonLabelList" : ["Delta pH"], "ValueList" : ["xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseRespAcuteChronicOption": { "ButtonLabelList" : ["Resp Acute Chronic"], "ValueList" : ["xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},


    ///////////////////
    // Gap Acidosis Diff
    "AcidBaseDiffMethylAlcoholOption": { "ButtonLabelList" : ["Methyl Alcohol"], "ValueList" : ["Methyl Alcohol"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffUremiaOption": { "ButtonLabelList" : ["Uremia"], "ValueList" : ["Uremia"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffDKAOption": { "ButtonLabelList" : ["DKA"], "ValueList" : ["diabetic ketoacidosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffEtOHOption": { "ButtonLabelList" : ["EtOH"], "ValueList" : ["EtOH ketoacidosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffStarvationOption": { "ButtonLabelList" : ["Starvation"], "ValueList" : ["starvation ketoacidosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffAtivanDripOption": { "ButtonLabelList" : ["AtivanDrip"], "ValueList" : ["Propylene Glycol (used in Lorazepam drips)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffAcetaminophenOption": { "ButtonLabelList" : ["Acetaminophen"], "ValueList" : ["Pyroglutamic Acid (also called Oxoproline, found in chronic acetaminophen use)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffPropofolOption": { "ButtonLabelList" : ["Propofol"], "ValueList" : ["Propofol"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffMyelomaOption": { "ButtonLabelList" : ["Myeloma"], "ValueList" : ["Paraproteinemias (Ig binds Cl in Myeloma)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffIronOption": { "ButtonLabelList" : ["Iron"], "ValueList" : ["Iron"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffIsoniazidOption": { "ButtonLabelList" : ["Isoniazid"], "ValueList" : ["Isoniazid (Type B lactic acidosis)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffIschemiaOption": { "ButtonLabelList" : ["Ischemia Lactate"], "ValueList" : ["Lactic Acid (Type A - Ischemia)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffMetforminOption": { "ButtonLabelList" : ["Metformin"], "ValueList" : ["Metformin (Type B lactic acidosis)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffLinezolidOption": { "ButtonLabelList" : ["Linezolid"], "ValueList" : ["Linezolid (Type B lactic acidosis)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffTenofovirOption": { "ButtonLabelList" : ["Tenofovir"], "ValueList" : ["Tenofovir (Type B lactic acidosis)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffDLactateOption": { "ButtonLabelList" : ["D-Lactate"], "ValueList" : ["D-Lactate (made by bacteria in short gut, serum lactate is normal)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffEthyleneGlycolOption": { "ButtonLabelList" : ["Ethylene Glycol"], "ValueList" : ["Ethylene Glycol"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffSalicylateOption": { "ButtonLabelList" : ["Salicylate"], "ValueList" : ["aspirin (Salicylate)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffRhabdoOption": { "ButtonLabelList" : ["Rhabdo"], "ValueList" : ["Rhabdo"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},

    ///////////////////
    // Non-Gap Acidosis Diff
    "AcidBaseDiffDiarrheaOption": { "ButtonLabelList" : ["Diarrhea"], "ValueList" : ["diarrhea"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffDilutionalOption": { "ButtonLabelList" : ["Dilutional (IV fluid)"], "ValueList" : ["dilutional (IV normal saline)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffCKDOption": { "ButtonLabelList" : ["CKD"], "ValueList" : ["CKD (and reduced acid clearance)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffRTAIVOption": { "ButtonLabelList" : ["RTA IV"], "ValueList" : ["RTA IV"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffRTA2Option": { "ButtonLabelList" : ["RTA II/Fanconi"], "ValueList" : ["RTA II (usually Fanconi)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffRTA1Option": { "ButtonLabelList" : ["RTA I"], "ValueList" : ["RTA I (distal tubule dysfunction)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffRespAlkalosisOption": { "ButtonLabelList" : ["Resp Alkalosis"], "ValueList" : ["compensation to a chronic respiratory alkalosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},

    ///////////////////
    // RTA I
    "AcidBaseDiffAcetazolamideOption" : { "ButtonLabelList" : ["Acetazolamide"], "ValueList" : ["Acetazolamide (Carbonic anhydrase inhibitor)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffTopiramateOption" : { "ButtonLabelList" : ["Topiramate"], "ValueList" : ["Topiramate (Carbonic anhydrase inhibitor)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffAmphotericinOption" : { "ButtonLabelList" : ["Amphotericin"], "ValueList" : ["Amphotericin (renal cell H+ backleak)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffObstructiveUropathyOption" : { "ButtonLabelList" : ["Obstructive uropathy"], "ValueList" : ["Obstructive uropathy"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffSjögrenOption" : { "ButtonLabelList" : ["Sjögren"], "ValueList" : ["Sjögren"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffRheumatoidOption" : { "ButtonLabelList" : ["Rheumatoid"], "ValueList" : ["Rheumatoid"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffLupusOption" : { "ButtonLabelList" : ["Lupus"], "ValueList" : ["Lupus"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffSickleCellOption" : { "ButtonLabelList" : ["Sickle cell"], "ValueList" : ["Sickle cell"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffHepatitisOption" : { "ButtonLabelList" : ["Hepatitis"], "ValueList" : ["viral Hepatitis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffHyperthyroidOption" : { "ButtonLabelList" : ["Hyperthyroid"], "ValueList" : ["Hyperthyroid"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffHyperparathyroidOption" : { "ButtonLabelList" : ["Hyperparathyroid"], "ValueList" : ["Hyperparathyroid"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffPrimaryBiliaryCirrhosisOption" : { "ButtonLabelList" : ["PBC"], "ValueList" : ["Primary Biliary Cirrhosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffChronicUTIOption" : { "ButtonLabelList" : ["chronic UTI"], "ValueList" : ["chronic UTI"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffTolueneOption" : { "ButtonLabelList" : ["Toluene"], "ValueList" : ["Toluene (renal cell H+ backleak)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},

    ///////////////////
    // RTA II
    "AcidBaseDiffWilsonOption" : { "ButtonLabelList" : ["Wilson"], "ValueList" : ["Wilson"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseRTAIDiffTenofovirOption" : { "ButtonLabelList" : ["Tenofovir"], "ValueList" : ["Tenofovir"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseRTAIDiffIfosfamideOption" : { "ButtonLabelList" : ["Ifosfamide"], "ValueList" : ["ifosfamide"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseRTAIDiffAcetazolamideOption" : { "ButtonLabelList" : ["Acetazolamide"], "ValueList" : ["Acetazolamide"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseRTAIDiffMultipleMyelomaOption" : { "ButtonLabelList" : ["Multiple Myeloma"], "ValueList" : ["Multiple myeloma"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},

    ///////////////////
    // RTA IV
    "AcidBaseRTAIVDiffDiabetesOption" : { "ButtonLabelList" : ["Diabetes"], "ValueList" : ["Diabetes"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseRTAIVDiffSpironolactoneOption" : { "ButtonLabelList" : ["Spironolactone"], "ValueList" : ["Spironolactone or epleronone"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseRTAIVDiffACEInhibitorsOption" : { "ButtonLabelList" : ["ACE inhibitors"], "ValueList" : ["ACE inhibitors"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseRTAIVDiffTrimethoprimOption" : { "ButtonLabelList" : ["Trimethoprim"], "ValueList" : ["Trimethoprim"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseRTAIVDiffPentamidineOption" : { "ButtonLabelList" : ["Pentamidine"], "ValueList" : ["Pentamidine"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseRTAIVDiffNSAIDsOption" : { "ButtonLabelList" : ["NSAIDs"], "ValueList" : ["NSAIDs"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseRTAIVDiffHIVOption" : { "ButtonLabelList" : ["HIV"], "ValueList" : ["HIV"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseRTAIVDiffAddisonOption" : { "ButtonLabelList" : ["Addison"], "ValueList" : ["Addison's Disease"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseRTAIVDiffsickleCellOption" : { "ButtonLabelList" : ["Sickle cell"], "ValueList" : ["Sickle cell"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseRTAIVDiffLupusOption" : { "ButtonLabelList" : ["Lupus"], "ValueList" : ["Lupus"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseRTAIVDiffurinaryObstructionOption" : { "ButtonLabelList" : ["urinary obstruction"], "ValueList" : ["urinary obstruction"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseRTAIVDiffAmyloidosisOption" : { "ButtonLabelList" : ["Amyloidosis"], "ValueList" : ["Amyloidosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},

    ///////////////////
    // Metabolic Alkalosis Diff
    "AcidBaseDiffVolumeLossOption": { "ButtonLabelList" : ["Volume Loss"], "ValueList" : ["volume contraction from GI loss"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffPoorPOOption": { "ButtonLabelList" : ["Poor PO"], "ValueList" : ["volume contraction from poor PO intake"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffDiureticsOption": { "ButtonLabelList" : ["Diuretics"], "ValueList" : ["volume contraction from diuresis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffHypercalcemiaOption": { "ButtonLabelList" : ["Hypercalcemia"], "ValueList" : ["hypercalcemia (which acts as a diuretic on TAL)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffHypokalemiaOption": { "ButtonLabelList" : ["Hypokalemia"], "ValueList" : ["hypokalemia (which acts as a diuretic by slowing NKCC2)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffHypercapnicCompensationOption": { "ButtonLabelList" : ["Hypercapnic compensation"], "ValueList" : ["compensation to hypercapnea"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffHyperAldoOption": { "ButtonLabelList" : ["Hyper-Aldo"], "ValueList" : ["hyper-Aldosterone"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffCushingsOption": { "ButtonLabelList" : ["Cushings"], "ValueList" : ["Cushings"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffLiddleOption": { "ButtonLabelList" : ["Liddle"], "ValueList" : ["Pseudo-Hyper-Aldo (Liddle)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffGlucocorticoidRemedialHyperaldoOption": { "ButtonLabelList" : ["Glucocorticoid-Remedial hyperaldo"], "ValueList" : ["Glucocorticoid-Remedial hyperaldo"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},

    ///////////////////
    // Resp Alkalosis Diff
    "AcidBaseDiffPainTachypneaOption": { "ButtonLabelList" : ["Pain Tachypnea"], "ValueList" : ["tachypnea from pain"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffHypoxiaOption": { "ButtonLabelList" : ["Hypoxia"], "ValueList" : ["tachypnea from hypoxia"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffPulmRestrictOption": { "ButtonLabelList" : ["Pulmonary Restriction"], "ValueList" : ["tachypnea from pulmonary restriction"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},

    ///////////////////
    // Resp Acidosis Diff
    "AcidBaseDiffRespAcidCOPDOption": { "ButtonLabelList" : ["COPD"], "ValueList" : ["CO2 retention from COPD"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseDiffSedationOption": { "ButtonLabelList" : ["Sedation"], "ValueList" : ["reduced respiratory drive from sedation"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},

    ///////////////////
    // Treat
    "AcidBasePOBicarbOption": { "ButtonLabelList" : ["PO Bicarb 650", "PO Bicarb 1300"], "ValueList" : ["Sodium Bicarb 650mg PO TID", "Sodium Bicarb 1300mg PO TID"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseIVBicarbOption": { "ButtonLabelList" : ["IV Bicarb 100", "IV Bicarb 150", "IV Bicarb 200"], "ValueList" : ["IV D5W with 150mEq/L Bicarb at 100 mL/hr", "IV D5W with 150mEq/L Bicarb at 150 mL/hr", "IV D5W with 150mEq/L Bicarb at 200 mL/hr"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseIVFluidsOption": { "ButtonLabelList" : ["IV LR 125", "IV LR 150", "IV LR 200"], "ValueList" : ["IV fluids - LR at 125 mL/hr", "IV fluids - LR at 150 mL/hr", "IV fluids - LR at 200 mL/hr"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseIVBolussOption": { "ButtonLabelList" : ["IV Bolus 500", "IV Bolus 1000", "IV Bolus 1500"], "ValueList" : ["IV fluid bolus - LR 500 mL", "IV fluid bolus - LR 1000 mL", "IV fluid bolus - LR 1500 mL"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},

    "AcidBaseThiamineOption": { "ButtonLabelList" : ["Thiamine"], "ValueList" : ["Thiamine 500mg IV daily for 3 days then 100mg PO daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},
    "AcidBaseAcetazolamideOption": { "ButtonLabelList" : ["Acetazolamide"], "ValueList" : ["Acetazolamide 250mg PO daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AcidBasePlan"},



    ///////////////////////////////////////////////////////////
    // HEART FAILURE CONTROLS
    ///////////////////////////////////////////////////////////

    ///////////////////
    "CHFAcuteChronicOption": { "ButtonLabelList" : ["AcuteOnChronic", "Chronic", "Acute"], "ValueList" : ["Acute on Chronic ", "Chronic ", "Acute "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFHFrEFOption": { "ButtonLabelList" : ["HFrEF", "HFmrEF", "HFpEF"], "ValueList" : ["Reduced Ejection Fraction", "Mid-Range Ejection Fraction", "Preserved Ejection Fraction"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFIschemicOption": { "ButtonLabelList" : ["Ischemic", "NonIschemic"], "ValueList" : ["Ischemic", "Non-ischemic"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFSystolicOption": { "ButtonLabelList" : ["Systolic", "Diastolic", "SystolicDiastolic"], "ValueList" : ["Systolic", "Diastolic", "Systolic and Diastolic"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFLeftSideOption": { "ButtonLabelList" : ["Left-Sided", "Right-Sided", "Biventricular"], "ValueList" : ["Left-Sided", "Right-Sided", "Biventricular"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFNotExacerbationOption": { "ButtonLabelList" : ["Not Exacerbation"], "ValueList" : ["The patient is not in exacerbation"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},

    ///////////////////
    // Staging
    "CHFNYHAOption": { "ButtonLabelList" : ["NYHA I", "NYHA II", "NYHA III", "NYHA IV"], "ValueList" : ["NYHA I", "NYHA II", "NYHA III", "NYHA IV"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFACCStageOption": { "ButtonLabelList" : ["ACC Stage A", "ACC Stage B", "ACC Stage C", "ACC Stage D"], "ValueList" : ["ACC Stage A", "ACC Stage B", "ACC Stage C", "ACC Stage D"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFLVEFOption": { "ButtonLabelList" : ["Show LVEF"], "ValueList" : ["LVEF="], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},

    ///////////////////
    // Vitals
    "CHFUrineOutOption": { "ButtonLabelList" : ["Urine Out"], "ValueList" : ["Urine output over the path 24hrs = xxx mL"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFWeightOption": { "ButtonLabelList" : ["Weight"], "ValueList" : ["Standing weight = kg"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFBaseWeightOption": { "ButtonLabelList" : ["Normal Weight"], "ValueList" : ["Baseline weight at home = kg"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFO2NeededOption": { "ButtonLabelList" : ["O2 Use"], "ValueList" : ["O2 requirement  via NC"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFHomeO2Option": { "ButtonLabelList" : ["On Home O2"], "ValueList" : ["on L O2 at home"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},

    ///////////////////
    // Past Workup
    "CHFShowEchoOption": { "ButtonLabelList" : ["Latest Echo"], "ValueList" : ["Echo showed:"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFShowBNPOption": { "ButtonLabelList" : ["Show BNP"], "ValueList" : ["xxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFShowXRayOption": { "ButtonLabelList" : ["Show XRay"], "ValueList" : ["xxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFHomeMedsOption": { "ButtonLabelList" : ["HomeMeds"], "ValueList" : ["Home medications: "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},

    ///////////////////
    // Triggers
    "CHFTriggerDietOption": { "ButtonLabelList" : ["Diet"], "ValueList" : ["high sodium diet"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFTriggerComplianceOption": { "ButtonLabelList" : ["Compliance"], "ValueList" : ["diuretic non-compliance"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFTriggerMedChangesOption": { "ButtonLabelList" : ["Med-Changes"], "ValueList" : ["diuretic dose changes"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFTriggerAKIOption": { "ButtonLabelList" : ["AKI"], "ValueList" : ["reduced renal clearance"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFTriggerFluidsOption": { "ButtonLabelList" : ["Fluids"], "ValueList" : ["increased fluid intake"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},

    ///////////////////
    // Workup
    "CHFXrayOption": { "ButtonLabelList" : ["Get Xray"], "ValueList" : ["Get Chest XRay"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFGetBNPOption": { "ButtonLabelList" : ["Get BNP"], "ValueList" : ["Check serum BNP"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFGetEchoOption": { "ButtonLabelList" : ["Check Echo"], "ValueList" : ["Get Echocardiogram"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},

    ///////////////////
    // Diuresis
    "CHFLasixIVOption": { "ButtonLabelList" : ["Lasix 20IV", "Lasix 20IVBID", "Lasix 40IV", "Lasix 40IVBID", "Lasix 80IV", "Lasix 80IVBID", "Lasix 100IV", "Lasix 100IVBID"], "ValueList" : ["Furosemide 20mg IV daily at breakfast", "Furosemide 20mg IV BID", "Furosemide 40mg IV daily at breakfast", "Furosemide 40mg IV BID", "Furosemide 80mg IV daily at breakfast", "Furosemide 80mg IV BID", "Furosemide 100mg IV daily at breakfast", "Furosemide 100mg IV BID"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFLasixPOOption": { "ButtonLabelList" : ["Lasix 20PO", "Lasix 20POBID", "Lasix 40PO", "Lasix 40POBID", "Lasix 80PO", "Lasix 80POBID"], "ValueList" : ["Furosemide 20mg PO daily at breakfast", "Furosemide 20mg PO BID", "Furosemide 40mg PO daily at breakfast", "Furosemide 40mg PO BID", "Furosemide 80mg PO daily at breakfast", "Furosemide 80mg PO BID"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFTorsemideOption": { "ButtonLabelList" : ["Torsemide20mg", "Torsemide20mgBID", "Torsemide40mg", "Torsemide40mgBID", "Torsemide80mg", "Torsemide80mgBID"], "ValueList" : ["Torsemide 20mg PO daily at breakfast", "Torsemide 20mg PO BID", "Torsemide 40mg PO daily at breakfast", "Torsemide 40mg PO BID", "Torsemide 80mg PO daily at breakfast", "Torsemide 80mg PO BID"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFBumexOption": { "ButtonLabelList" : ["Bumetanide1", "Bumetanide1BID", "Bumetanide2", "Bumetanide2BID"], "ValueList" : ["Bumetanide 1mg PO daily at breakfast", "Bumetanide 1mg PO BID", "Bumetanide 2mg PO daily at breakfast", "Bumetanide 2mg PO BID"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFThiazideOption": { "ButtonLabelList" : ["Metolazone2.5", "Metolazone5", "Metolazone10"], "ValueList" : ["Metolazone 2.5mg PO daily at breakfast", "Metolazone 5mg PO daily at breakfast", "Metolazone 10mg PO daily at breakfast"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFNoDiureticOption": { "ButtonLabelList" : ["HypoVol", "Infection"], "ValueList" : ["Hold diuretics while hypovolemic", "Hold diuretics while active infection"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},

    ///////////////////
    // Beta Blockers
    "CHFMetoprololTarOption": { "ButtonLabelList" : ["MetopTar 12.5", "MetopTar 25", "MetopTar 50", "MetopTar 75", "MetopTar 100", "MetopTar 150", "Hold"], "ValueList" : ["Metoprolol Tartrate 12.5mg PO BID", "Metoprolol Tartrate 25mg PO BID", "Metoprolol Tartrate 50mg PO BID", "Metoprolol Tartrate 75mg PO BID", "Metoprolol Tartrate 100mg PO BID", "Metoprolol Tartrate 150mg PO BID", "Hold home Metoprolol due to hypotension"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFMetoprololSuccOption": { "ButtonLabelList" : ["MetopXL 25", "MetopXL 50", "MetopXL 75", "MetopXL 100", "MetopXL 200", "Hold"], "ValueList" : ["Metoprolol Succinate 25mg PO once daily", "Metoprolol Succinate 50mg PO once daily", "Metoprolol Succinate 75mg PO once daily", "Metoprolol Succinate 100mg PO once daily", "Metoprolol Succinate 200mg PO once daily", "Hold home Metoprolol due to hypotension"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFCarvedilolOption": { "ButtonLabelList" : ["Coreg 3.125", "Coreg 6.25", "Coreg 12.5", "Coreg 25", "Hold"], "ValueList" : ["Carvedilol 3.125mg PO BID", "Carvedilol 6.25mg PO BID", "Carvedilol 12.5mg PO BID", "Carvedilol 25mg PO BID", "Hold home Carvedilol due to hypotension"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFNSBBOption": { "ButtonLabelList" : ["See Cirrhosis"], "ValueList" : ["Non-specific Beta-Blocker as discussed for Cirrhosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFNoBetaBlockerOption": { "ButtonLabelList" : ["Brady", "Low BP"], "ValueList" : ["Hold betablockers while bradycardic", "Hold betablockers while hypotensive"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},

    ///////////////////
    // ACE/ARB
    "CHFLisinoprilOption": { "ButtonLabelList" : ["Lisinopril2.5", "Lisinopril5", "Lisinopril10", "Lisinopril20", "Lisinopril40", "Hold"], "ValueList" : ["Lisinopril 2.5mg PO daily", "Lisinopril 5mg PO daily", "Lisinopril 10mg PO daily", "Lisinopril 20mg PO daily", "Lisinopril 40mg PO daily", "Hold home Lisinopril due to AKI"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFLosartanOption": { "ButtonLabelList" : ["Losartan25", "Losartan50", "Losartan100", "Hold"], "ValueList" : ["Losartan 25mg PO daily", "Losartan 50mg PO daily", "Losartan 100mg PO daily", "Hold home Losartan due to AKI"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFARNIOption": { "ButtonLabelList" : ["ARNI-Low", "ARNI-High"], "ValueList" : ["valsartan/sacubitril (Entresto) 49/51 mg PO BID", "valsartan/sacubitril (Entresto) 97/103 mg PO BID"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFNoACEARBOption": { "ButtonLabelList" : ["AKI", "Allergy", "Low BP", "High K"], "ValueList" : ["Hold ACE/ARB due to AKI", "Hold ACE/ARB due to allergy to ACE", "Hold ACE/ARB due to low blood pressure", "Hold ACE/ARB due to Hyperkalemia"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},

    // Indications for SGLT2
    "CHFSGLT2IndicationsDM2Option" : { "ButtonLabelList" : ["DM2"], "ValueList" : ["Diabetes type 2"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFSGLT2IndicationsCKDOption" : { "ButtonLabelList" : ["CKD"], "ValueList" : ["CKD with eGFR over 30"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFSGLT2IndicationsHFrEFOption" : { "ButtonLabelList" : ["HFrEF"], "ValueList" : ["Heart failure with reduced ejection fraction"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFSGLT2IndicationsUACROver200Option" : { "ButtonLabelList" : ["Albuminuria"], "ValueList" : ["Albuminuria with urine albumin/Cr ratio over 200ug/g"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},

    // Contraindications for SGLT2
    "CHFSGLT2ContraindicationsGFRBelow30Option" : { "ButtonLabelList" : ["GFR below 30"], "ValueList" : ["eGFR below 30"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFSGLT2ContraindicationsDM1Option" : { "ButtonLabelList" : ["DM 1"], "ValueList" : ["Diabetes type 1"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFSGLT2ContraindicationsTransplantOption" : { "ButtonLabelList" : ["Transplant"], "ValueList" : ["renal transplant"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFSGLT2ContraindicationsDKAOption" : { "ButtonLabelList" : ["Past DKA"], "ValueList" : ["history of DKA"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFSGLT2ContraindicationsImunosuppressedOption" : { "ButtonLabelList" : ["imunosuppressed"], "ValueList" : ["imunosuppressed"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFSGLT2ContraindicationsPKDOption" : { "ButtonLabelList" : ["PKD"], "ValueList" : ["PKD"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFSGLT2ContraindicationsSLEOption" : { "ButtonLabelList" : ["SLE"], "ValueList" : ["Lupus"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFSGLT2ContraindicationsANCAOption" : { "ButtonLabelList" : ["ANCA"], "ValueList" : ["ANCA"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},

    ///////////////////
    // SGLT2
    "CHFSGLT2DapagliflozinOption": { "ButtonLabelList" : ["Dapagliflozin"], "ValueList" : ["Dapagliflozin 10mg PO daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFSGLT2EmpagliflozinOption" : { "ButtonLabelList" : ["Empagliflozin"], "ValueList" : ["Empagliflozin 10mg PO daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFSGLT2ReduceInsulinOption" : { "ButtonLabelList" : ["Reduce Insulin"], "ValueList" : ["Reduce Insulin 20 percent if GFR is over 45"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFSGLT2ExplainGFRDropOption" : { "ButtonLabelList" : ["Explain AKI"], "ValueList" : ["Expect 10-30 percent drop in eGFR due to hemodynamic effect of reduced filtration. This is not an acute kidney injury, and past studies have shown it is reversable by stopping the SGLT2 inhibitor. Essentially, an SGLT2 inhibitos just stops the hyperfiltration associated with glucosuria and unmasks the true eGFR."], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFNoSGLT2Option": { "ButtonLabelList" : ["UTI", "DM-1", "CKD4", "Transplant", "DKA", "PKD", "Immuno"], "ValueList" : ["Hold SGLT2 while urinary tract infection", "No SGLT2 because patient has diabetes type-1", "No SGLT2 because patient has eGFR below 30", "No SGLT2 because patient has transplant", "No SGLT2 because patient has past DKA", "No SGLT2 because patient has PKD", "No SGLT2 because patient is Immunosuppressed"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},

    ///////////////////
    // MRA
    "CHFSpironiolactoneOption": { "ButtonLabelList" : ["Spironolactone25", "Spironolactone50", "Spironolactone100", "Hold"], "ValueList" : ["Spironolactone 25mg PO daily", "Spironolactone 50mg PO daily", "Spironolactone 100mg PO daily", "Hold home Spironolactone due to AKI"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFAldoBlockRestrictionsOption": { "ButtonLabelList" : ["AldoBlockerLimits"], "ValueList" : [" (NYHA II-IV, CrCl over 30, Cr below 2.5, K below 5)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFNoMRAOption": { "ButtonLabelList" : ["AKI", "Low BP", "High K", "Postpone"], "ValueList" : ["Hold mineralocorticoid receptor antagonist due to AKI", "Hold mineralocorticoid receptor antagonist due to low blood pressure", "Hold mineralocorticoid receptor antagonist due to Hyperkalemia", "Postpone mineralocorticoid receptor antagonist until response to ACE/ARB is understood"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},

    ///////////////////
    // ICD
    "CHFICDOption": { "ButtonLabelList" : ["ICD"], "ValueList" : ["Refer to Cardiology for implantable cardioverter-defibrillator"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFICDIndicationsOption": { "ButtonLabelList" : ["Indications"], "ValueList" : [" (no MI within 40 days, NYHA I and LVEF below 30%, NYHA II-IV and LVEF below 35%, LVEF below 40% with nonsustained-VT)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},

    ///////////////////
    // Diet
    "CHF2gNaDietOption": { "ButtonLabelList" : ["2g Na Diet"], "ValueList" : ["2g Na diet"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFFluidRestrictOption": { "ButtonLabelList" : ["2L Fluids"], "ValueList" : ["2000mL daily fluid restriction"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFDietEdOption": { "ButtonLabelList" : ["Education"], "ValueList" : ["Nutrition consult for diet education"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFCompressionStockingsOption": { "ButtonLabelList" : ["Stockings"], "ValueList" : ["Compression stockings (20-40mm Hg) on discharge"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},

    ///////////////////
    // Monitor
    "CHFIOOption": { "ButtonLabelList" : ["Strict In/Out"], "ValueList" : ["Strict Intake/Output"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},
    "CHFDailyWeightOption": { "ButtonLabelList" : ["Daily Weight"], "ValueList" : ["Daily standing weight at noon"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CHFPlan"},





    ///////////////////////////////////////////////////////////
    // HYPERTENSION CONTROLS
    // ACC 2017 Guidelines
    // Patients with HFrEF and hypertension should be prescribed GDMT
    // titrated to attain systolic blood pressure less than 130 mm Hg.
    //    WriteComment("[Stage I (below 160/100) Stage II (over 160/100) Urgency Uncontrolled]. Resistant (on 3 agents including a diuretic)");
    ///////////////////////////////////////////////////////////

    ///////////////////
    "HtnUrgency": { "ButtonLabelList" : ["Urgency", "Emergency"], "ValueList" : ["Hypertensive Urgency", "Hypertensive Emergency"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},

    ///////////////////
    // Targets
    "HTNStageOption": { "ButtonLabelList" : ["Stage I", "Stage II", "Urgency", "Emergency", "Resistant"], "ValueList" : ["This is Stage I (130-139/80-89)", "This is Stage II (over 140/90)", "This is Hypertensive Urgency", "This is Hypertensive Emergency", "This is Resistant Hypertension (on 4 agents including a diuretic)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNPrimaryOption": { "ButtonLabelList" : ["Primary"], "ValueList" : ["This is primary hypertension, and the possible causes include: salt-sensitive, hyper-aldo, apoL1 mutation"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNCurrentBPOption": { "ButtonLabelList" : ["CurrentBP"], "ValueList" : ["Over the past 24hrs, systolic blood pressures have been: "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNHomeMedsOption": { "ButtonLabelList" : ["HomeMeds"], "ValueList" : ["Home medications: "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},

    ///////////////////
    "HTNACCTargetOption": { "ButtonLabelList" : ["ACC"], "ValueList" : ["Target BP below 130/80 (ACC/AHA)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNDiabetesTargetOption": { "ButtonLabelList" : ["Diabetes"], "ValueList" : ["The patient is diabetic, so target BP below 140/90 (Accord)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNRenalTargetOption": { "ButtonLabelList" : ["Renal"], "ValueList" : ["The patient has CKD, so target BP below 130/80 (ACC/AHA)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNSprintTargetOption": { "ButtonLabelList" : ["SPRINT"], "ValueList" : ["The patient is not diabetic or CKD, so target BP below 120/80 (SPRINT)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNEmergencyTargetOption": { "ButtonLabelList" : ["Emergency"], "ValueList" : ["In Hypertensive urgency, target 20% reduction in the first 24hrs, so goal BP=xxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNSepsisTargetOption": { "ButtonLabelList" : ["Sepsis"], "ValueList" : ["Hold antihypertensives in sepsis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},

    ///////////////////
    "HTNAmlodipineOption": { "ButtonLabelList" : ["Amlodipine5", "Amlodipine10"], "ValueList" : ["Amlodipine 5mg PO daily", "Amlodipine 10mg PO daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNNifedipineOption": { "ButtonLabelList" : ["Nifedipine30", "Nifedipine60", "Nifedipine90", "Nifedipine120"], "ValueList" : ["Nifedipine 30mg PO daily", "Nifedipine 60mg PO daily", "Nifedipine 90mg PO daily", "Nifedipine 120mg PO daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNDiltiazemOption": { "ButtonLabelList" : ["Diltiazem30", "Diltiazem60", "Diltiazem90", "Diltiazem120", "Diltiazem240", "Diltiazem360"], "ValueList" : ["Diltiazem 30mg daily", "Diltiazem 60mg daily", "Diltiazem 90mg daily", "Diltiazem ER 120mg PO daily", "Diltiazem ER 240mg PO daily", "Diltiazem ER 360mg PO daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},

    ///////////////////
    // Diuresis
    "HTNThiazideOption": { "ButtonLabelList" : ["HCTZ12.5", "HCTZ25", "Chlorthalidone12.5", "Chlorthalidone25", ], "ValueList" : ["Hydrochrolothiazide 12.5mg once daily", "Hydrochrolothiazide 25mg once daily", "Chlorthalidone 12.5mg once daily", "Chlorthalidone 25mg once daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNLasixPOOption": { "ButtonLabelList" : ["Lasix 20PO", "Lasix 20POBID", "Lasix 40PO", "Lasix 40POBID", "Lasix 80PO"], "ValueList" : ["Furosemide 20mg PO daily at breakfast", "Furosemide 20mg PO BID", "Furosemide 40mg PO daily at breakfast", "Furosemide 40mg PO BID", "Furosemide 80mg PO daily at breakfast"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNTorsemideOption": { "ButtonLabelList" : ["Torsemide20mg", "Torsemide20mgBID", "Torsemide40mg", "Torsemide40mgBID", "Torsemide80mg", "Torsemide80mgBID"], "ValueList" : ["Torsemide 20mg PO daily at breakfast", "Torsemide 20mg PO BID", "Torsemide 40mg PO daily at breakfast", "Torsemide 40mg PO BID", "Torsemide 80mg PO daily at breakfast", "Torsemide 80mg PO BID"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNSeeCHFOption": { "ButtonLabelList" : ["See CHF"], "ValueList" : ["Diuretics as discussed elsewhere for heart failure"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},

    ///////////////////
    // ACE/ARB
    "HTNLisinoprilOption": { "ButtonLabelList" : ["Lisinopril10", "Lisinopril20", "Lisinopril40", "Hold"], "ValueList" : ["Lisinopril 10mg PO daily", "Lisinopril 20mg PO daily", "Lisinopril 40mg PO daily", "Hold home Lisinopril due to AKI"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNLosartanOption": { "ButtonLabelList" : ["Losartan25", "Losartan50", "Losartan100", "Hold"], "ValueList" : ["Losartan 25mg PO daily", "Losartan 50mg PO daily", "Losartan 100mg PO daily", "Hold home Losartan due to AKI"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNSpironiolactoneOption": { "ButtonLabelList" : ["Spironolactone25", "Spironolactone50", "Spironolactone100", "Hold"], "ValueList" : ["Spironolactone 25mg PO daily", "Spironolactone 50mg PO daily", "Spironolactone 100mg PO daily", "Hold home Spironolactone due to AKI"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},

    ///////////////////
    // Beta Blockers
    "HTNMetoprololTarOption": { "ButtonLabelList" : ["MetopTar 12.5", "MetopTar 25", "MetopTar 50", "MetopTar 75", "MetopTar 100", "Hold"], "ValueList" : ["Metoprolol Tartrate 12.5mg PO BID", "Metoprolol Tartrate 25mg PO BID", "Metoprolol Tartrate 50mg PO BID", "Metoprolol Tartrate 75mg PO BID", "Metoprolol Tartrate 100mg PO BID", "Hold home Metoprolol due to hypotension"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNMetoprololSuccOption": { "ButtonLabelList" : ["MetopXL 25", "MetopXL 50", "MetopXL 75", "MetopXL 100", "MetopXL 200", "Hold"], "ValueList" : ["Metoprolol Succinate 25mg PO once daily", "Metoprolol Succinate 50mg PO once daily", "Metoprolol Succinate 75mg PO once daily", "Metoprolol Succinate 100mg PO once daily", "Metoprolol Succinate 200mg PO once daily", "Hold home Metoprolol due to hypotension"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNCarvedilolOption": { "ButtonLabelList" : ["Coreg 3.125", "Coreg 6.25", "Coreg 12.5", "Coreg 25", "Hold"], "ValueList" : ["Carvedilol 3.125mg PO BID", "Carvedilol 6.25mg PO BID", "Carvedilol 12.5mg PO BID", "Carvedilol 25mg PO BID", "Hold home Carvedilol due to hypotension"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNNSBBOption": { "ButtonLabelList" : ["See Cirrhosis"], "ValueList" : ["Non-specific Beta-Blocker as discussed for Cirrhosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},

    ///////////////////
    "HTNClonidineOption": { "ButtonLabelList" : ["Clonidine0.1", "Clonidine0.2", "Clonidine0.3"], "ValueList" : ["Clonidine 0.1mg PO TID", "Clonidine 0.2mg PO TID", "Clonidine 0.3mg PO TID"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNHydralazineOption": { "ButtonLabelList" : ["Hydralazine25", "Hydralazine50", "Hydralazine75", "Hydralazine100", "Hydralazine150"], "ValueList" : ["Hydralazine 25mg PO TID", "Hydralazine 50mg PO TID", "Hydralazine 75mg PO TID", "Hydralazine 100mg PO TID", "Hydralazine 150mg PO TID"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},

    ///////////////////
    "HTNPRNLabetalolOption": { "ButtonLabelList" : ["PRN Labetalol"], "ValueList" : ["PRN IV Labetalol 10mg for Systolic BP over 180 or diastolic over 100, hold for HR below 60"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNPRNClonidineOption": { "ButtonLabelList" : ["PRN Clonidine"], "ValueList" : ["PRN Clonidine 0.1mg for Systolic BP over 180 or diastolic over 100"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNUFWithDialysisOption": { "ButtonLabelList" : ["UF with HD"], "ValueList" : ["Ultrafiltration with dialysis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},

    ///////////////////
    "HTNCheckAldoRenin": { "ButtonLabelList" : ["AldoRenin"], "ValueList" : ["Check Aldosterone and Renin levels"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNRASDopplers": { "ButtonLabelList" : ["Dopplers"], "ValueList" : ["Check Renal Artery Dopplers"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNRuleOutOSA": { "ButtonLabelList" : ["OSA"], "ValueList" : ["Check for OSA"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNCheckTSHOption": { "ButtonLabelList" : ["TSH"], "ValueList" : ["Check TSH"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNMicroAlbuminOption": { "ButtonLabelList" : ["MicroAlbumin"], "ValueList" : ["Check urine albumin and creatinine"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},

    ///////////////////
    "HTNNicardipine": { "ButtonLabelList" : ["NicardipineDrip"], "ValueList" : ["Nicardipine drip, fixed rate, 2.5mg/hr, do not titrate"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNNTG": { "ButtonLabelList" : ["NTG Drip"], "ValueList" : ["Nitroglycerine drip"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},
    "HTNCheckDrugsOption": { "ButtonLabelList" : ["Drug Screen"], "ValueList" : ["Check urine drug screen"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HTNPlan"},



    ///////////////////////////////////////////////////////////
    // HypOnatremia
    ///////////////////////////////////////////////////////////
   "HypONaPseudoModifierOption": { "ButtonLabelList" : ["Pseudo"], "ValueList" : ["Pseudo-Hyponatremia"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaSIADHModifierOption": { "ButtonLabelList" : ["SIADH"], "ValueList" : ["Syndrome of Inappropriate Antidiuretic Hormone secretion (SIADH)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaVolumeModifierOption": { "ButtonLabelList" : ["HyperVolemic", "HypoVolemic"], "ValueList" : ["Hypervolemic Hyponatremia", "Hypovolemic Hyponatremia"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},

   // Status
   "HypONaShowCurrentNaOption": { "ButtonLabelList" : ["Current Na"], "ValueList" : ["Recent serum sodium="], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaShowAdjustedNaOption": { "ButtonLabelList" : ["Adjusted Na"], "ValueList" : ["Adjusted Sodium="], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaNeuroSxOption": { "ButtonLabelList" : ["No Neuro Sx", "Neuro Sx"], "ValueList" : ["The patient does not have any obvious neurologic symptoms", "The patient has neurologic symptoms"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
    "HypONaShowSOsmOption" : { "ButtonLabelList" : ["Serum Osm"], "ValueList" : ["Serum Osm = "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},

   // Explanation
   "HypONaExplainOption": { "ButtonLabelList" : ["Explain"], "ValueList" : ["Hyponatremia is an excess of free water, not a deficiency of sodium - the total body sodium is likely normal, but the kidneys are usually retaining too much free water which dilutes the blood and lowers sodium concentration."], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},


    // ADH Status
   "HypONaHighADHOption": { "ButtonLabelList" : ["High ADH", "Normal ADH"], "ValueList" : ["The patient is in a high ADH state", "The patient is in a normal ADH state"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaShowUOsmOption": { "ButtonLabelList" : ["U Osm"], "ValueList" : ["Recent Urine osmolality = "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaExplainHighUOsmOption": { "ButtonLabelList" : ["Explain U Osm"], "ValueList" : ["Urine Osm is a biomarker for ADH. When urine osm is high, the kidneys are usually retaining free water and there is an excess of ADH. This may be appropriate (in the case of hypovolemia) or inappropriate (in the case of SIADH). However, high urine osmolality may also be due to inappropriate solute wasting, such as hypo-aldosteronism. "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaShowFreeWaterClearanceOption": { "ButtonLabelList" : ["Show Clearance"], "ValueList" : ["Recent free water clearance = "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaExplainFreeWaterClearanceOption": { "ButtonLabelList" : ["Explain Clearance"], "ValueList" : ["Free water clearance is 24hr-Urine-Volume * (1 - ((Urine-Na + Urine-K) / (Serum-Na)). If Free water clearance is negative then the patient is retaining free water and serum Na concentration will drop, and if it is positive then the patient is wasting free water and serum Na concentration will rise."], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},



   // Aldo Status
   "HypONaAldoStatusOption": { "ButtonLabelList" : ["High Aldo", "Normal Aldo"], "ValueList" : ["The patient is in a high Aldo state, which suggests intravascular depletion and an appropriate high ADH state", "The patient is in a normal Aldo state, which suggests intravascular euvolemia and an inappropriatly high ADH state"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaExplainAldoOption": { "ButtonLabelList" : ["Explain Aldo"], "ValueList" : ["If the patient is intravascularly depleted, then both Aldosterone and ADH should be elevated. However, if Aldo is not high, then the patient is likely not intravascularly depleted, and so this is an inappropriatly high ADH"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},


   "HypONaResultofNaChallengeOption": { "ButtonLabelList" : ["Fluid Response"], "ValueList" : ["Serum sodium increased after giving fluids, consistent with volume depletion"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaShowUNaOption": { "ButtonLabelList" : ["U-Na Low"], "ValueList" : ["Urine sodium is low (below 40)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaShowUKOption": { "ButtonLabelList" : ["U-K High"], "ValueList" : ["Urine potassium is high"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaShowUrateOption": { "ButtonLabelList" : ["Urate high"], "ValueList" : ["Serum Uric acid is high which suggests concentration and hypovolemia"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaShowPhysExamOption": { "ButtonLabelList" : ["Hypervolemic", "Euvolemic"], "ValueList" : ["On physical exam, the patient appears hypervolemic with edema and pulmonary rales", "On physical exam, the patient appears hypovolemic or euvolemic with no edema or pulmonary rales"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaShowBicarbOption": { "ButtonLabelList" : ["Bicarb high"], "ValueList" : ["Serum bicarb is elevated"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},


   // Lung Disease
   "HypONaPneumoniaOption": { "ButtonLabelList" : ["Pneumonia"], "ValueList" : ["pneumonia"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaSepticEmboliOption": { "ButtonLabelList" : ["Septic Emboli"], "ValueList" : ["septic pulmonary emboli"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaLungCancerOption": { "ButtonLabelList" : ["Lung Cancer"], "ValueList" : ["lung cancer"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaInterstitialOption": { "ButtonLabelList" : ["Interstitial"], "ValueList" : ["Interstitial Lung Disease"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},

   // SIADH Meds
   "HypONaSSRIOption": { "ButtonLabelList" : ["SSRIs"], "ValueList" : ["an SSRI"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaCiprofloxacinOption": { "ButtonLabelList" : ["Ciprofloxacin"], "ValueList" : ["Ciprofloxacin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaCyclophosphamideOption": { "ButtonLabelList" : ["Cyclophosphamide"], "ValueList" : ["Cyclophosphamide"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaCisplatinOption": { "ButtonLabelList" : ["Cisplatin"], "ValueList" : ["Cisplatin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaImatinibOption": { "ButtonLabelList" : ["Imatinib"], "ValueList" : ["Imatinib"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},

   "HypONaMethotrexateOption": { "ButtonLabelList" : ["Methotrexate"], "ValueList" : ["Methotrexate"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaVincristineOption": { "ButtonLabelList" : ["Vincristine"], "ValueList" : ["Vincristine"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaHaloperidolOption": { "ButtonLabelList" : ["Haloperidol"], "ValueList" : ["Haloperidol"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaTCAsOption": { "ButtonLabelList" : ["TCAs"], "ValueList" : ["a TCA"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},

   // Malnutrition
   "HypONaShowBUBOption": { "ButtonLabelList" : ["Low BUN/BMI"], "ValueList" : ["BUN and BMI are low, suggesting malnutrition"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaLowOsmOption": { "ButtonLabelList" : ["Low UOsm"], "ValueList" : ["Urine osm is low, suggesting the kidneys are trying to waste free water"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaExplainLowOsmOption": { "ButtonLabelList" : ["Explain Low UOsm"], "ValueList" : ["The kidneys cannot excrete pure water, instead they need a minimal solute load to make urine and excrete free water. The minimal urine osmolality is typically 50 mOsm or more, so the patient does not take in enough solute then they cannot remove free water. It is ok to give tube feeds or salt tablets."], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},

   // Adrenal
   "HypONaLowAdrenalLowBPOption": { "ButtonLabelList" : ["Low BP"], "ValueList" : ["hypotension"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaLowAdrenalHighKOption": { "ButtonLabelList" : ["High K"], "ValueList" : ["hyperkalemia"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},

   // Causes
   "HypONaCHFOption": { "ButtonLabelList" : ["Heart Failure"], "ValueList" : ["Heart Failure with volume overload and third spacing"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaCirrhosisOption": { "ButtonLabelList" : ["Cirrhosis"], "ValueList" : ["Cirrhosis (third spacing and high ADH release)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
    "HypONaCausesHighIntakeOption" : { "ButtonLabelList" : ["High Intake"], "ValueList" : ["High free water intake (with tube feeds or IV fluids)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERnatremiaPlan"},
   "HypONaSIADHOption": { "ButtonLabelList" : ["SIADH"], "ValueList" : ["SIADH"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaHypoVolemiaOption": { "ButtonLabelList" : ["Hypovolemia"], "ValueList" : ["Hypovolemia"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaHypotensionOption": { "ButtonLabelList" : ["Hypotension"], "ValueList" : ["Hypotension"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaVolumeDepletionOption": { "ButtonLabelList" : ["Volume Depletion"], "ValueList" : ["Volume Depletion"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaOverDiuresisOption": { "ButtonLabelList" : ["Over Diuresis"], "ValueList" : ["Over Diuresis (specifically thiazides)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
    "HypONaHighIntakeOption" : { "ButtonLabelList" : ["High Intake"], "ValueList" : ["Excess free water intake (with tube feeds)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaMalnutritionOption": { "ButtonLabelList" : ["Malnutrition"], "ValueList" : ["Malnutrition"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaAdrenalOption": { "ButtonLabelList" : ["Low Adrenal"], "ValueList" : ["Adrenal insufficiency"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},


   // Target and  OverCorrect
   "HypONaDilyTargetOption": { "ButtonLabelList" : ["6mEq Daily", "8mEq Daily"], "ValueList" : ["Target 6 (six) mEq correction in 24hrs, so by xxx on xxx, the Na should be xxx", "Target 8 (eight) mEq correction in 24hrs, so by xxx on xxx, the Na should be xxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaD5WOption": { "ButtonLabelList" : ["PRN D5W"], "ValueList" : ["If Na corrects too rapidly, give PRN IV D5W 250mL for sodium over xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaDDAVPOption": { "ButtonLabelList" : ["PRN DDAVP"], "ValueList" : ["If Na corrects much too rapidly, give 1 microgram of DDAVP PRN (Desmopressin, an ADH/Vasopressin analog) for serum sodium over xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},


   // Workup
   "HypONaCheckNaQ6hOption": { "ButtonLabelList" : ["Check Na Q6h"], "ValueList" : ["Check Serum Sodium Q6h"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaCheckUOsmOption": { "ButtonLabelList" : ["Urine Osm"], "ValueList" : ["urine osmolality daily to monitor ADH response. Urine osmolality is a biomarker for ADH"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaCheckULytesOption": { "ButtonLabelList" : ["Urine Lytes"], "ValueList" : ["urine sodium and potassium daily to monitor free water clearance"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},



    "HypONaCheckSOsmOption" : { "ButtonLabelList" : ["Serum Osm"], "ValueList" : ["serum Osm to rule out hyperosmotic hyponatremia"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaCheckTSHOption": { "ButtonLabelList" : ["Check TSH"], "ValueList" : ["TSH (hypothyroid may cause a hypoosmolar hyponatremia, unclear mechanism)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},


   "HypONaCheckLipidsOption": { "ButtonLabelList" : ["Check Lipids"], "ValueList" : ["lipid panel, both hypertriglyceridemia and hypercholesterolemia can cause pseudo-hyponatremia"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaCheckUrateOption": { "ButtonLabelList" : ["Check Urate"], "ValueList" : ["serum uric acid to estimate volume status"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaAMcortisolOption": { "ButtonLabelList" : ["AM cortisol"], "ValueList" : ["AM cortisol to rule out adrenal insufficiency"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaNeuroChecksOption": { "ButtonLabelList" : ["Neuro checks"], "ValueList" : ["Neuro checks Q2h"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaSeizurePrecautionsOption": { "ButtonLabelList" : ["Seizure precautions"], "ValueList" : ["Seizure precautions"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},

   // Treat
    "HypoNaBolusOption" : { "ButtonLabelList" : ["Bolus LR", "Bolus NS"], "ValueList" : ["IV fluid bolus, 1L LR", "IV fluid bolus, 1L NS"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
    "HypoNaMaintFluidOption" : { "ButtonLabelList" : ["IV Drip LR", "IV Drip NS"], "ValueList" : ["IV fluids, LR at 100mL/hr for 24hrs", "IV fluids, NS at 100mL/hr for 24hrs"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},


   "HypONaFreeWaterRestrictionOption": { "ButtonLabelList" : ["Water Restrict"], "ValueList" : ["Free water restriction to 1.5L per day. This may require concentrating any medication drips"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaLasixOption": { "ButtonLabelList" : ["Furosemide"], "ValueList" : ["IV Furosemide 80mg once"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaStopThiazidesOption": { "ButtonLabelList" : ["Stop Thiazides"], "ValueList" : ["Avoid thiazides, as they worsen the hyponatremia. "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaExplainLasixOption": { "ButtonLabelList" : ["Explain Lasix"], "ValueList" : ["A loop diuretic will block Na/K/Cl reabsorption, so will wash out the interstitial gradient. As a result, free water is not reabsorbed even when Aquaporins are open, so the kidney wastes free water and serum Na concentrations rise. A Thiazide preserves interstitial gradient so aquaporins reabsorb free water, and this continues to dilute serum and lower the Na concentration level."], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},
   "HypONaExplainThiazidesOption": { "ButtonLabelList" : ["Explain Thiazides"], "ValueList" : ["A Thiazide preserves interstitial gradient so aquaporins reabsorb free water, while a loop diuretic will wash out the interstitial gradient and so free water is not reabsorbed even when Aquaporins are open. Thus, Thiazides preserve free water reabsorption and continue the lower sodium."], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},

    // Overcorrect
   "HypONaHTSOption": { "ButtonLabelList" : ["3% Saline"], "ValueList" : ["If symptomatic, then 100mL of 3 percent saline. Typically 100 mL of 3 percent Na will increase serum Na by 2-3 mEq"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyponatremiaPlan"},



    ///////////////////////////////////////////////////////////
    // Sepsis CONTROL PANEL
    ///////////////////////////////////////////////////////////
    "SepsisShowSOFAChange" : { "ButtonLabelList" : ["Show SOFA"], "ValueList" : ["Show SOFA"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisSepsisModifier" : { "ButtonLabelList" : ["SIRS", "Sepsis", "Severe Sepsis"], "ValueList" : ["SIRS", "Sepsis", "Severe Sepsis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisEndocarditisModifier" : { "ButtonLabelList" : ["Endocarditis"], "ValueList" : ["Infective Endocarditis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisPulmEmboliModifier" : { "ButtonLabelList" : ["Pulm Emboli"], "ValueList" : ["Septic Pulmonary Emboli"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisUTIModifier" : { "ButtonLabelList" : ["UTI"], "ValueList" : ["Urinary Tract Infection"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisPneumoniaModifier" : { "ButtonLabelList" : ["Pneumonia"], "ValueList" : ["Pneumonia"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},

    // SIRS Criteria
    "SepsisSIRSHROption" : { "ButtonLabelList" : ["HR over 90"], "ValueList" : ["HR over 90"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisSIRSTempOption" : { "ButtonLabelList" : ["Temp over 100.4"], "ValueList" : ["Temp over 100.4"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisSIRSRROption" : { "ButtonLabelList" : ["RR over 20"], "ValueList" : ["RR over 20"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisSIRSWBCOption" : { "ButtonLabelList" : ["WBC over 12"], "ValueList" : ["WBC over 12"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},

    // Source
    "SepsisUTISourceOption" : { "ButtonLabelList" : ["pneumonia"], "ValueList" : ["pneumonia"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisPneumoniaSourceOption" : { "ButtonLabelList" : ["UTI"], "ValueList" : ["Urinary Tract Infection"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisCellulitisSourceOption" : { "ButtonLabelList" : ["cellulitis"], "ValueList" : ["cellulitis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},

    // SOFA Current
    "SepsisSOFAOption_Current_PaO2FiO2" : { "ButtonLabelList" : ["Over 400", "300-400", "200-300", "100-200", "Below 100"], "ValueList" : ["Over 400", "300-400", "200-300", "100-200", "Below 100"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisSOFAOption_Current_Plts" : { "ButtonLabelList" : ["Over 150", "100-150", "50-100", "20-50", "Below 20"], "ValueList" : ["Over 150", "100-150", "50-100", "20-50", "Below 20"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisSOFAOption_Current_Bili" : { "ButtonLabelList" : ["Below 1.2", "1.2-1.9", "2.0-5.9", "6.0-11.9", "Over 12"], "ValueList" : ["Below 1.2", "1.2-1.9", "2.0-5.9", "6.0-11.9", "Over 12"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisSOFAOption_Current_MAP" : { "ButtonLabelList" : ["Over 70", "Below 70", "Dop below 5", "Norepi below 0.1", "Norepi above 0.1"], "ValueList" : ["Over 70", "Below 70", "Dop below 5", "Norepi below 0.1", "Norepi above 0.1"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisSOFAOption_Current_GCS" : { "ButtonLabelList" : ["15 (AOx3)", "13-14 (AOx1)", "10-12", "6-9", "Below 6"], "ValueList" : ["15 (AOx3)", "13-14 (AOx1)", "10-12", "6-9", "Below 6"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisSOFAOption_Current_Cr" : { "ButtonLabelList" : ["Below 1.2", "1.2-1.9", "2.0-3.4", "3.5-4.9", "Over 5.0"], "ValueList" : ["Below 1.2", "1.2-1.9", "2.0-3.4", "3.5-4.9", "Over 5.0"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},

    // SOFA Baseline
    "SepsisSOFAOption_Baseline_PaO2FiO2" : { "ButtonLabelList" : ["Over 400", "300-400", "200-300", "100-200", "Below 100"], "ValueList" : ["Over 400", "300-400", "200-300", "100-200", "Below 100"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisSOFAOption_Baseline_Plts" : { "ButtonLabelList" : ["Over 150", "100-150", "50-100", "20-50", "Below 20"], "ValueList" : ["Over 150", "100-150", "50-100", "20-50", "Below 20"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisSOFAOption_Baseline_Bili" : { "ButtonLabelList" : ["Below 1.2", "1.2-1.9", "2.0-5.9", "6.0-11.9", "Over 12"], "ValueList" : ["Below 1.2", "1.2-1.9", "2.0-5.9", "6.0-11.9", "Over 12"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisSOFAOption_Baseline_MAP" : { "ButtonLabelList" : ["Over 70", "Below 70", "Dop below 5", "Norepi below 0.1", "Norepi above 0.1"], "ValueList" : ["Over 70", "Below 70", "Dop below 5", "Norepi below 0.1", "Norepi above 0.1"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisSOFAOption_Baseline_GCS" : { "ButtonLabelList" : ["15 (AOx3)", "13-14 (AOx1)", "10-12", "6-9", "Below 6"], "ValueList" : ["15 (AOx3)", "13-14 (AOx1)", "10-12", "6-9", "Below 6"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisSOFAOption_Baseline_Cr" : { "ButtonLabelList" : ["Below 1.2", "1.2-1.9", "2.0-3.4", "3.5-4.9", "Over 5.0"], "ValueList" : ["Below 1.2", "1.2-1.9", "2.0-3.4", "3.5-4.9", "Over 5.0"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},

    // Workup
    "SepsisWUBloodCultureOption" : { "ButtonLabelList" : ["Blood Cx"], "ValueList" : ["blood cultures"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisWUUAOption" : { "ButtonLabelList" : ["UA"], "ValueList" : ["urinalysis with reflex culture"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisWUNaresOption" : { "ButtonLabelList" : ["Nares"], "ValueList" : ["MRSA Nares"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisWUSputumCultureOption" : { "ButtonLabelList" : ["Sputum Cx"], "ValueList" : ["sputum cultures"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisWURVPOption" : { "ButtonLabelList" : ["RVP"], "ValueList" : ["Resp viral panel"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisWUStoolCultureOption" : { "ButtonLabelList" : ["Stool Cx"], "ValueList" : ["stool culture"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisWUStrepUrineAntigenOption" : { "ButtonLabelList" : ["Urine Strep"], "ValueList" : ["urine strep antigen"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisWULegionellaUrineAntigenOption" : { "ButtonLabelList" : ["Urine Legionella"], "ValueList" : ["urine legionella antigen"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisWUCDiffOption" : { "ButtonLabelList" : ["C diff"], "ValueList" : ["stool C diff by PCR"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisWUBetaGlucanOption" : { "ButtonLabelList" : ["Beta Glucan"], "ValueList" : ["serum beta glucan"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisWUGalactomannanOption" : { "ButtonLabelList" : ["Galactomannan"], "ValueList" : ["serum Galactomannan"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},

    // Markers
    "SepsisWUProcalOption" : { "ButtonLabelList" : ["Procal"], "ValueList" : ["Procalcitonin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisWUCRPOption" : { "ButtonLabelList" : ["CRP"], "ValueList" : ["C-Reactive Protein"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisWULactateOption" : { "ButtonLabelList" : ["Lactate"], "ValueList" : ["serum lactate"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},

    // Imaging
    "SepsisWUXRayOption" : { "ButtonLabelList" : ["Chest XRay"], "ValueList" : ["Chest XRay"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisEchoOption" : { "ButtonLabelList" : ["Echo (TTE)"], "ValueList" : ["Echocardiogram (trans-thoracic)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisPanorexOption" : { "ButtonLabelList" : ["Panorex"], "ValueList" : ["Panorex"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisCTAHeadOption" : { "ButtonLabelList" : ["CTA Head"], "ValueList" : ["CTA Head and Neck to screen for mycotic aneurysms"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisCTAAbdomenOption" : { "ButtonLabelList" : ["CT Abdomen"], "ValueList" : ["CT Abdomen"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},

    // Fluids/Steroids
    "SepsisFluidBolusOption" : { "ButtonLabelList" : ["Bolus LR", "Bolus NS", "Bolus Bicarb"], "ValueList" : ["IV fluid bolus, 1L LR", "IV fluid bolus, 1L NS", "IV fluid bolus, 1L D5W with 150mEq bicarb"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisHighMaintFluidOption" : { "ButtonLabelList" : ["Bicarb 200", "Bicarb 150", "LR 200", "LR 150"], "ValueList" : ["D5W with 150mEq Bicarb at 200mL/hr for  hrs", "D5W with 150mEq Bicarb at 150mL/hr for  hrs", "LR at 200mL/hr for  hrs", "LR at 150mL/hr for  hrs"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisLowMaintFluidOption" : { "ButtonLabelList" : ["LR 125", "LR 100", "Bicarb 125", "Bicarb 100"], "ValueList" : ["LR at 125mL/hr", "LR at 100mL/hr", "D5W with 150mEq Bicarb at 125mL/hr", "D5W with 150mEq Bicarb at 100mL/hr"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisStressSteroidsOption" : { "ButtonLabelList" : ["Hydrocortisone"], "ValueList" : ["Stress dose Steroids: Hydrocortisone 50mg IV Q6h"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},

    // Antibiotics
    "SepsisVancOption" : { "ButtonLabelList" : ["Vanc"], "ValueList" : ["Vancomycin with pharmacy titration to levels (cover gram positives including MRSA)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisPipTazoOption" : { "ButtonLabelList" : ["Pip/Tazo"], "ValueList" : ["Pip/Tazo 3.375g IV Q6h (cover gram negatives and anaerobes)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisCefepimeOption" : { "ButtonLabelList" : ["Cefepime"], "ValueList" : ["Cefepimg 2g IV q8h"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisMetronidazoleOption" : { "ButtonLabelList" : ["Metronidazole"], "ValueList" : ["Metronidazole 500mg q6h"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisCeftriaxoneOption" : { "ButtonLabelList" : ["Ceftriaxone"], "ValueList" : ["Ceftriaxone 2g IV daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},

    // Hold Meds
    "SepsisHoldDiureticsOption" : { "ButtonLabelList" : ["Hold Diuretics"], "ValueList" : ["Hold Diuretics"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},
    "SepsisHoldBPMedsOption" : { "ButtonLabelList" : ["Hold antihypertensives"], "ValueList" : ["Hold antihypertensives"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "SepsisPlan"},




    ///////////////////////////////////////////////////////////
    // OSA 
    ///////////////////////////////////////////////////////////
    "ObstructiveSleepApneaPlan" : { "ButtonLabelList" : ["OSA"], "ValueList" : ["Obstructive Sleep Apnea"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},
    "OSAObesityHypoventillationPlan" : { "ButtonLabelList" : ["Obesity"], "ValueList" : ["Obesity Hypoventillation"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},
    "OSAHypercapneaPlan" : { "ButtonLabelList" : ["Hypercapnea"], "ValueList" : ["Chronic Hypercapnic Respiratory Failure"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},

    "OSAPossibleModifier" : { "ButtonLabelList" : ["Possible"], "ValueList" : ["Possible "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},

    // STOP-BANG
    "OSASnoringOption" : { "ButtonLabelList" : ["Snoring"], "ValueList" : ["Snoring"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},
    "OSATiredOption" : { "ButtonLabelList" : ["Tired"], "ValueList" : ["daytime fatigue"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},
    "OSAObservedApneaOption" : { "ButtonLabelList" : ["Observed apnea"], "ValueList" : ["observed apnea"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},
    "OSAHypertensionOption" : { "ButtonLabelList" : ["Hypertension"], "ValueList" : ["hypertension"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},
    "OSABMIOver35Option" : { "ButtonLabelList" : ["BMI over 35"], "ValueList" : ["BMI over 35"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},
    "OSAAgeOver50yoOption" : { "ButtonLabelList" : ["Over 50yo"], "ValueList" : ["over 50yo"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},
    "OSANeckOver16inOption" : { "ButtonLabelList" : ["Neck over 16in"], "ValueList" : ["neck circumference over 16in"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},
    "OSAMaleOption" : { "ButtonLabelList" : ["Male"], "ValueList" : ["male"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},

    // Past and Current Diagnosis
    "OSAPastDiagnosisOption" : { "ButtonLabelList" : ["Diagnosed", "CPAP Broken"], "ValueList" : ["The patient has a home CPAP machine", "The patient has had a home CPAP, but it is not working"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},
    "OSAABGResultsOption" : { "ButtonLabelList" : ["ABG Results"], "ValueList" : ["Arterial Blood Gas Results"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},

    // Diagnose
    "OSACheckPFTOption" : { "ButtonLabelList" : ["Check PFT"], "ValueList" : ["Check Pulmonary Function Tests"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},
    "OSACheckABGOption" : { "ButtonLabelList" : ["Check ABG"], "ValueList" : ["Check ABG twice, one at any time after noon and once immediately after waking up"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},
    "OSASleepStudyOption" : { "ButtonLabelList" : ["Sleep study"], "ValueList" : ["Refer to outpatient sleep study"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},
    "OSAOvernightOximetryOption" : { "ButtonLabelList" : ["Overnight oximetry"], "ValueList" : ["Overnight oximetry study"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},

    // Workup
    "OSAExplainSTOPBANGOption" : { "ButtonLabelList" : ["Explain STOPBANG"], "ValueList" : ["STOP-BANG score of 3 or more means high risk"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},
    "OSAGetEchoOption" : { "ButtonLabelList" : ["Get Echo"], "ValueList" : ["Get Echo to assess RV function"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},
    "OSAGetEKGOption" : { "ButtonLabelList" : ["Check EKG"], "ValueList" : ["Get EKG to assess possible LVH"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},

    // Treat
    "OSAContinueCPAPOption" : { "ButtonLabelList" : ["Home CPAP", "BiPAP"], "ValueList" : ["Continue CPAP at night (home setting xxx cm H2O)", "BiPAP at night"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},

    "OSAFlonaseOption" : { "ButtonLabelList" : ["Flonase"], "ValueList" : ["Flonase when using CPAP"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},

    "OSAInsuranceOption" : { "ButtonLabelList" : ["Insurance"], "ValueList" : ["Due to the progression of Chronic Respiratory Failure due to COPD, Chronic Heart Failure, and Obesity Hypoventillation, the patient will require frequent durations of non-invasive ventillator. Bi-Level Pap at home will not be sufficient as the patients severity of condition has progressed, therefore the patient needs aggressive target volume guarantee, advanced alarms that will alert the alert if the patient is disconnected, backup battery for portability. These are required to prevent risk of harm and hospital readmissions. The patient requires non-invasive ventillation 8-9 hours a day while sleeping. Patient is at increased risk of exacerbation leading to hospital readmissions or death without such therapy."], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "OSAPlan"},



    ///////////////////////////////////////////////////////////
    // ILLICITS/SUBSTANCE ABUSE
    ///////////////////////////////////////////////////////////
    // Modifiers
    "OpioidUseDisorderModifier" : { "ButtonLabelList" : ["Opioids"], "ValueList" : ["Opioid Use Disorder"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "CannabisUseDisorderModifier" : { "ButtonLabelList" : ["THC"], "ValueList" : ["Cannabis Use Disorder"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "MethUseDisorderModifier" : { "ButtonLabelList" : ["Meth"], "ValueList" : ["Stimulant Use Disorder - Amphetamine"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "CocaineUseDisorderModifier" : { "ButtonLabelList" : ["Cocaine"], "ValueList" : ["Stimulant Use Disorder - Cocaine"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "SedativeUseDisorderModifier" : { "ButtonLabelList" : ["Benzos"], "ValueList" : ["Sedative Use Disorder"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsSeverityModifier" : { "ButtonLabelList" : ["Mild 2-3", "Moderate 4-5", "Severe 6+"], "ValueList" : ["This is Mild (2-3 DSM 5 Criteria)", "This is Moderate (4-5 DSM 5 Criteria)", "This is Severe (6 or more DSM 5 Criteria)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},

    // DSM Criteria
    "IllicitsHazardousUseOption" : { "ButtonLabelList" : ["Hazardous use"], "ValueList" : ["Hazardous use"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsSocialProblemsOption" : { "ButtonLabelList" : ["Social problems"], "ValueList" : ["Social/interpersonal problems related to use"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsNeglectedRolesOption" : { "ButtonLabelList" : ["Neglected Roles"], "ValueList" : ["Neglected major roles to use"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsWithdrawalOption" : { "ButtonLabelList" : ["Withdrawal"], "ValueList" : ["Withdrawal"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsToleranceOption" : { "ButtonLabelList" : ["Tolerance"], "ValueList" : ["Tolerance"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsLargerAmountsOption" : { "ButtonLabelList" : ["Larger Amounts"], "ValueList" : ["Used larger amounts/longer"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsAttemptsToQuitOption" : { "ButtonLabelList" : ["Tried To Quit"], "ValueList" : ["Repeated attempts to quit/control use"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsTimeSpentOption" : { "ButtonLabelList" : ["Time Spent"], "ValueList" : ["Much time spent using"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsPsychPhysicalProblemsOption" : { "ButtonLabelList" : ["Physical Problems"], "ValueList" : ["Physical/psychological problems related to use"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsGaveUpActivitiesOption" : { "ButtonLabelList" : ["Gave Up Activities"], "ValueList" : ["Activities given up to use"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsCravingOption" : { "ButtonLabelList" : ["Craving"], "ValueList" : ["Craving"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},

    // UDS
    "Illicits_UDS_Heroin_Option" : { "ButtonLabelList" : ["Heroin"], "ValueList" : ["Heroin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "Illicits_UDS_Opioids_Option" : { "ButtonLabelList" : ["Opioids"], "ValueList" : ["Opioids"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "Illicits_UDS_THC_Option" : { "ButtonLabelList" : ["THC"], "ValueList" : ["THC"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "Illicits_UDS_Meth_Option" : { "ButtonLabelList" : ["Meth"], "ValueList" : ["Methamphetamine"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "Illicits_UDS_Cocaine_Option" : { "ButtonLabelList" : ["Cocaine"], "ValueList" : ["Cocaine"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "Illicits_UDS_Benzos_Option" : { "ButtonLabelList" : ["Benzos"], "ValueList" : ["Benzodiazepines"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},

    // History
    "IllicitsShowUDSOption" : { "ButtonLabelList" : ["Show UDS"], "ValueList" : ["On admission, Urine Drug Screen was positive for: "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsPastUDSOption" : { "ButtonLabelList" : ["Past UDS"], "ValueList" : ["Per the medical record, past Urine drug screens have been positive for: "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsShowPharmRecordsOption" : { "ButtonLabelList" : ["Pharm Records"], "ValueList" : ["Per pharmacy records, the patient has recently filled prescriptions for: "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsPatientReportsOption" : { "ButtonLabelList" : ["Patient Admits"], "ValueList" : ["The patient says they use the following medications without a prescription: "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},

    // Eval
    "IllicitsCheckUDSOption" : { "ButtonLabelList" : ["UDS"], "ValueList" : ["Urine Drug Screen"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsCheckHepatitisOption" : { "ButtonLabelList" : ["Hepatitis Screen"], "ValueList" : ["HAV, HBV, HCV screens"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsCheckHIVOption" : { "ButtonLabelList" : ["Check HIV"], "ValueList" : ["HIV, Syphilis screen"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsCheckHepImmpnityOption" : { "ButtonLabelList" : ["Check Hep Immun"], "ValueList" : ["HBV, and HAV immunity"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},

    // Symptoms
    "IllicitsHydroxyzineOption" : { "ButtonLabelList" : ["Hydroxyzine"], "ValueList" : ["Hydroxyzine 50-100mg PO Q6h prn anxiety/restlessness"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsTrazodoneOption" : { "ButtonLabelList" : ["Trazodone"], "ValueList" : ["Trazodone 50-150mg PO QHS PRN insomnia"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsLoperamideOption" : { "ButtonLabelList" : ["Loperamide"], "ValueList" : ["Loperamide 2-4mg PO Q4 PRN diarrhea"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsOndansetronOption" : { "ButtonLabelList" : ["Ondansetron"], "ValueList" : ["Ondansetron 4-8mg PO PRN nausea/vomiting"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsMethocarbamolOption" : { "ButtonLabelList" : ["Methocarbamol"], "ValueList" : ["Methocarbamol 500-750mg PO Q8h PRN muscle cramping"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsAcetaminophenOption" : { "ButtonLabelList" : ["Acetaminophen"], "ValueList" : ["Acetaminophen and Ibuprofen for myalgias or headache"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},

    // Consults
    "IllicitsAddictionMedOption" : { "ButtonLabelList" : ["Addiction Med"], "ValueList" : ["Addiction Medicine"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsMusicTherapyOption" : { "ButtonLabelList" : ["Music therapy"], "ValueList" : ["Music therapy"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsNarrativeMedOption" : { "ButtonLabelList" : ["Narrative Med"], "ValueList" : ["Narrative Medicine"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},
    "IllicitsChaplainOption" : { "ButtonLabelList" : ["Chaplain"], "ValueList" : ["Chaplain"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IllicitDrugsPlan"},







    ///////////////////////////////////////////////////////////
    // ANEMIA
    ///////////////////////////////////////////////////////////
    // Modifiers
    "AnemiaAcuteChronicModifier" : { "ButtonLabelList" : ["Acute", "Acute on Chronic", "Chronic"], "ValueList" : ["Acute", "Acute on Chronic", "Chronic"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaChronicDiseaseModifier" : { "ButtonLabelList" : ["ChronicDisease"], "ValueList" : ["Anemia of Chronic Inflammation"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCKDModifier" : { "ButtonLabelList" : ["CKD"], "ValueList" : ["Anemia of Chronic Kidney Disease"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaBloodLossModifier" : { "ButtonLabelList" : ["BloodLoss"], "ValueList" : ["Blood Loss Anemia"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaMicrocyticModifier" : { "ButtonLabelList" : ["Microcytic", "Macrocytic"], "ValueList" : ["Microcytic Anemia", "Macrocytic Anemia"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},

    // Status
    "AnemiaShowHgbOption" : { "ButtonLabelList" : ["Show Hgb"], "ValueList" : ["Latest Hgb is "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaShowMCVOption" : { "ButtonLabelList" : ["Show MCV"], "ValueList" : ["MCV is "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaShowBUNOption" : { "ButtonLabelList" : ["High BUN", "Low BUN"], "ValueList" : ["BUN is high, suggesting possible Hgb digestion and an upper GI bleed", "BUN is low, not consistent with Hgb digestion so suggesting a lower GI bleed"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},

    // Diff
    "AnemiaDiffBloodLossOption" : { "ButtonLabelList" : ["Blood Loss"], "ValueList" : ["Blood Loss"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaDiffHemolysisOption" : { "ButtonLabelList" : ["Hemolysis"], "ValueList" : ["Hemolysis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaDiffChronicdiseaseOption" : { "ButtonLabelList" : ["Chronic disease"], "ValueList" : ["Chronic disease"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaDiffUnderproductionOption" : { "ButtonLabelList" : ["Underproduction"], "ValueList" : ["Underproduction"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaDiffSequestrationOption" : { "ButtonLabelList" : ["Sequestration"], "ValueList" : ["Sequestration"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},

    //Status
    "AnemiaTIBCStatusOption" : { "ButtonLabelList" : ["TIBC Low", "TIBC Normal"], "ValueList" : ["TIBC is low", "TIBC is normal"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaTransferrinStatusOption" : { "ButtonLabelList" : ["Transferrin Low", "Transferrin Normal"], "ValueList" : ["Transferrin is low", "Transferrin is normal"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaFeSatStatusOption" : { "ButtonLabelList" : ["Iron Sat Low", "Iron Sat normal"], "ValueList" : ["Iron binding saturation is low", "Iron binding saturation is normal"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaHemoccultStatusOption" : { "ButtonLabelList" : ["Hemoccult Neg", "Hemoccult Pos"], "ValueList" : ["Hemoccult is negative", "Hemoccult is positive"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaHPyloriStatusOption" : { "ButtonLabelList" : ["H pylori Neg", "H pylori Pos"], "ValueList" : ["H pylori stool antigen is negative", "H pylori stool antigen is positive"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaB12StatusOption" : { "ButtonLabelList" : ["B12 WNL", "B12 Low"], "ValueList" : ["B12 is normal", "B12 is low"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaFolateStatusOption" : { "ButtonLabelList" : ["Folate WNL", "Folate Low"], "ValueList" : ["Folate is normal", "Folate is low"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},



    //Workup
    "AnemiaCheckINROption" : { "ButtonLabelList" : ["INR"], "ValueList" : ["INR"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckHemoccultOption" : { "ButtonLabelList" : ["Hemoccult"], "ValueList" : ["Hemoccult"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckReticulocyteCountOption" : { "ButtonLabelList" : ["Reticulocyte count"], "ValueList" : ["Reticulocyte count"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckTransferrinOption" : { "ButtonLabelList" : ["Transferrin"], "ValueList" : ["Transferrin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckIronBindingSaturationOption" : { "ButtonLabelList" : ["Iron sat"], "ValueList" : ["Iron binding saturation"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckFerritinOption" : { "ButtonLabelList" : ["Ferritin"], "ValueList" : ["Ferritin (below 15 is usually Fe deficiency, but Ferritin is also an acute phase reactant)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckTIBCOption" : { "ButtonLabelList" : ["TIBC"], "ValueList" : ["TIBC"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckB12Option" : { "ButtonLabelList" : ["B12"], "ValueList" : ["B12"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckFolateOption" : { "ButtonLabelList" : ["Folate"], "ValueList" : ["Folate"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckVitKOption" : { "ButtonLabelList" : ["Vit K"], "ValueList" : ["Vit K level"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckCopperOption" : { "ButtonLabelList" : ["Copper"], "ValueList" : ["copper level"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckZincOption" : { "ButtonLabelList" : ["Zinc"], "ValueList" : ["zinc level"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckHPyloriOption" : { "ButtonLabelList" : ["H pylori"], "ValueList" : ["H pylori stool antigen"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckHIVOption" : { "ButtonLabelList" : ["HIV"], "ValueList" : ["HIV"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckHBVOption" : { "ButtonLabelList" : ["HBV"], "ValueList" : ["Hep B antigen"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckEBVOption" : { "ButtonLabelList" : ["EBV"], "ValueList" : ["EBV"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckParvoOption" : { "ButtonLabelList" : ["Parvo"], "ValueList" : ["Parvo"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckPeripheralSmearOption" : { "ButtonLabelList" : ["Peripheral smear"], "ValueList" : ["Peripheral smear"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckFibrinogenOption" : { "ButtonLabelList" : ["Fibrinogen"], "ValueList" : ["Fibrinogen"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckDirectCoombsOption" : { "ButtonLabelList" : ["Direct Coombs"], "ValueList" : ["Direct Coombs"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckHaptoglobinOption" : { "ButtonLabelList" : ["Haptoglobin"], "ValueList" : ["Haptoglobin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckLDHOption" : { "ButtonLabelList" : ["LDH"], "ValueList" : ["LDH"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckWarmAgglutininsOption" : { "ButtonLabelList" : ["Warm Agglutinins"], "ValueList" : ["Warm Agglutinins"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckColdAgglutininsOption" : { "ButtonLabelList" : ["Cold Agglutinins"], "ValueList" : ["Cold Agglutinins"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckANAOption" : { "ButtonLabelList" : ["ANA"], "ValueList" : ["ANA"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaCheckCeliacOption" : { "ButtonLabelList" : ["Celiac"], "ValueList" : ["tissue transglutaminase antibodies and anti-gliaden for possible celiac"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},

    // Monitor
    "AnemiaMonitorHgbOption" : { "ButtonLabelList" : ["Hgb Q4h", "Hgb Q6h", "Hgb Q8h", "Hgb Q12h"], "ValueList" : ["Check Hgb Q4h", "Check Hgb Q6h", "Check Hgb Q8h", "Check Hgb Q12h"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaTrendLDHOption" : { "ButtonLabelList" : ["Daily LDH"], "ValueList" : ["Trend daily LDH"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaTrendHaptoglobinOption" : { "ButtonLabelList" : ["Daily Haptoglobin"], "ValueList" : ["Trend daily Haptoglobin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},

    // Treat
    "AnemiaTypeScreenOption" : { "ButtonLabelList" : ["Type and screen"], "ValueList" : ["Type and screen"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaPOIronOption" : { "ButtonLabelList" : ["PO Iron"], "ValueList" : ["Replace Iron (Ferrous Sulfate PO) and Folate (Folate 1mg PO daily)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaPRNTransfuseOption" : { "ButtonLabelList" : ["Transfuse at 7", "Transfuse at 8"], "ValueList" : ["Transfuse to keep Hgb over 7", "Transfuse to keep Hgb over 8 due to heart failure"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},
    "AnemiaPPIOption" : { "ButtonLabelList" : ["PPI", "IV PPI"], "ValueList" : ["Pantoprazole 40mg PO daily", "IV Pantoprazole - 40mg IV bid"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AnemiaPlan"},


    ///////////////////////////////////////////////////////////
    // GI BLEED
    ///////////////////////////////////////////////////////////
    // Modifiers
    "GIBleedUpperModifier" : { "ButtonLabelList" : ["Upper", "Lower"], "ValueList" : ["Upper", "Lower"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GIBleedPlan"},

    // Class
    "GIBleedSourceOfBleed" : { "ButtonLabelList" : ["Upper GI", "Lower GI"], "ValueList" : ["This is likely an upper GI bleed (variceal, gastritis)", "This may be a lower GI bleed (diverticular, lower variceal, hemorrhoid)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GIBleedPlan"},
    "GIBleedHemorrhageClassOption" : { "ButtonLabelList" : ["Class I", "Class II", "Class III", "Class IV"], "ValueList" : ["This is a Class I hemorrhage - No tachycardia and blood pressure is normal, blood loss less than 750mL or 15% total blood volume", "This is a Class II hemorrhage - Tachycardia (HR over 100) but blood pressure is normal, blood loss 750mL to 1500mL or 15 to 30% total blood volume", "This is a Class III hemorrhage - Tachycardia (HR over 120) and blood pressure is low, and urine output is decreased, blood loss 1500mL to 2000mL or 30% to 40% total blood volume", "This is a Class IV hemorrhage - Tachycardia (HR over 120) and blood pressure is low, and urine output is low, blood loss over 2000mL or over 40% total blood volume"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GIBleedPlan"},
    "GIBleedExplainHROption" : { "ButtonLabelList" : ["Explain HR"], "ValueList" : ["If this is an acute bleed, then estimate blood loss using vital signs, as the patient probably has not yet diluted remaining blood so hemoglobin will be normal"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GIBleedPlan"},

    // IV Fluids
    "GIBleedFluidBolusOption" : { "ButtonLabelList" : ["Bolus 1L LR", "Bolus 2L LR"], "ValueList" : ["IV fluid bolus, 1L LR", "IV fluid bolus, 2L LR"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GIBleedPlan"},
    "GIBleedMaintFluidOption" : { "ButtonLabelList" : ["IV Drip LR 100", "IV Drip LR 150", "IV Drip LR 200"], "ValueList" : ["Continuous IV fluids, LR at 100mL/hr", "Continuous IV fluids, LR at 150mL/hr", "Continuous IV fluids, LR at 200mL/hr", ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GIBleedPlan"},
    "GIBleedExplainFluidTargetsOption" : { "ButtonLabelList" : ["3 to 1 fluids"], "ValueList" : ["Replete 3mL of IV fluid per 1mL blood loss"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GIBleedPlan"},
    "GIBleedHoldDiureticsOption" : { "ButtonLabelList" : ["Hold Diuretics"], "ValueList" : ["Hold Diuretics"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GIBleedPlan"},

    // Basics
    "GIBleedTypeScreenOption" : { "ButtonLabelList" : ["Type/Screen"], "ValueList" : ["Type and Screen"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GIBleedPlan"},
    "GIBleedHgbFreqOption" : { "ButtonLabelList" : ["Hgb Q4hrs", "Hgb Q6hrs", "Hgb Q8hrs", "Hgb Q12hrs"], "ValueList" : ["Check Hgb/Hct Q4hrs", "Check Hgb/Hct Q6hrs", "Check Hgb/Hct Q8hrs", "Check Hgb/Hct Q12hrs"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GIBleedPlan"},
    "GIBleedTransfuseLevelOption" : { "ButtonLabelList" : ["Hgb over 7", "Hgb over 8"], "ValueList" : ["Transfuse to keep Hgb over 7", "Transfuse to keep Hgb over 8 due to heart failure"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GIBleedPlan"},

    // Workup
    "GIBleedINROption" : { "ButtonLabelList" : ["INR"], "ValueList" : ["INR"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GIBleedPlan"},
    "GIBleedBUNOption" : { "ButtonLabelList" : ["BUN"], "ValueList" : ["BUN (for possible digested blood)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GIBleedPlan"},
    "GIBleedHemoccultOption" : { "ButtonLabelList" : ["Hemoccult"], "ValueList" : ["Hemoccult"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GIBleedPlan"},
    "GIBleedHPyloriOption" : { "ButtonLabelList" : ["H. pylori"], "ValueList" : ["H. pylori"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GIBleedPlan"},

    // Imaging
    "GIBleedCTAngiographyOption" : { "ButtonLabelList" : ["CT Angiography"], "ValueList" : ["CT Angiography of abdomen"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GIBleedPlan"},
    "GIBleedCTEnterographyOption" : { "ButtonLabelList" : ["CT Enterography"], "ValueList" : ["CT Enterography"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GIBleedPlan"},

    // Treat
    "GIBleedPantoprazoleOption" : { "ButtonLabelList" : ["IV PPI", "PPI Drip"], "ValueList" : ["IV Pantoprazole - 40mg IV bid", "IV Pantoprazole - 80mg bolus followed by 8mh/hr continuous"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GIBleedPlan"},
    "GIBleedOctreotideOption" : { "ButtonLabelList" : ["Octreotide"], "ValueList" : ["Octreotide (a synthetic Somatostatin analog). 50 mcg bolus then 50 mcg/hr"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GIBleedPlan"},
    "GIBleedCeftriaxoneOption" : { "ButtonLabelList" : ["Ceftriaxone"], "ValueList" : ["Ceftriaxone 1g IV daily x7 days"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GIBleedPlan"},



    ///////////////////////////////////////////////////////////
    // Diabetes
    ///////////////////////////////////////////////////////////
    "Diabetes_Type_Modifier" : { "ButtonLabelList" : ["Type 1", "Type 2", "Type2-Insulin"], "ValueList" : [", Type 1", ", Type 2", ", Type 2, insulin requiring"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "Diabetes_Uncontrolled_Modifier" : { "ButtonLabelList" : ["Uncontrolled"], "ValueList" : [", Uncontrolled"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DiabetesHyperglycemiaModifier" : { "ButtonLabelList" : ["Hyperglycemia"], "ValueList" : [" with hyperglycemia"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},

    // Status
    "DiabetesStatusShowA1cOption" : { "ButtonLabelList" : ["A1c"], "ValueList" : ["Latest HgbA1c = " ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DiabetesStatusShowWhenDiagnosedOption" : { "ButtonLabelList" : ["When Diag"], "ValueList" : ["Diagnosed approximately xxx, if type 2 anticipate nephropathy, retinopathy, and gradual beta cell dysfunction over time" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DiabetesStatusShowHomeRegimenOption" : { "ButtonLabelList" : ["Home Regimen"], "ValueList" : ["Home Regimen is" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DiabetesStatusShowDailyStatusOption" : { "ButtonLabelList" : ["Daily Status"], "ValueList" : ["On Accucheck Glucose values= . Total daily insulin correction factor= " ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},

    // Workup
    "DiabetesWorkupGetA1cOption" : { "ButtonLabelList" : ["Get A1c"], "ValueList" : ["Check Hgb A1c"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DiabetesWorkupGetUrineAlbProtCrOption" : { "ButtonLabelList" : ["Get U Alb"], "ValueList" : ["Check Urine microalbumin/Cr ratio to screen for Diabetic Nephropathy"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},

    // Insulin
    "DiabetesInsulinHoldPOOption" : { "ButtonLabelList" : ["Hold PO Meds"], "ValueList" : ["Hold home PO Medications while inpatient"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DiabetesDMEducationOption" : { "ButtonLabelList" : ["DM Ed"], "ValueList" : ["Diabetes Education" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DiabetesNutritionEducationOption" : { "ButtonLabelList" : ["Nutrition Ed"], "ValueList" : ["Consult Nutrition for patient education on diet"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},

    // Insulin
    "DiabetesInsulinReducedHomeRegimenOption" : { "ButtonLabelList" : ["Halve home dose"], "ValueList" : ["We will dose 60% of home regimen while the patient is in the hospital, and is acutely ill and on a different diet"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DiabetesInsulinGlargineOption" : { "ButtonLabelList" : ["Glargine"], "ValueList" : ["Glargine xxx units QHS"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DiabetesInsulinLisproOption" : { "ButtonLabelList" : ["Lispro"], "ValueList" : ["Lispro xxx units TID with meals"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DiabetesInsulinSlidingScaleOption" : { "ButtonLabelList" : ["SSI"], "ValueList" : ["Sliding scale Insulin" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},

    // Indications for SGLT2
    "DMSGLT2IndicationsDM2Option" : { "ButtonLabelList" : ["DM2"], "ValueList" : ["Diabetes type 2"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DMSGLT2IndicationsCKDOption" : { "ButtonLabelList" : ["CKD"], "ValueList" : ["CKD with eGFR over 30"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DMSGLT2IndicationsHFrEFOption" : { "ButtonLabelList" : ["HFrEF"], "ValueList" : ["Heart failure with reduced ejection fraction"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DMSGLT2IndicationsUACROver200Option" : { "ButtonLabelList" : ["Albuminuria"], "ValueList" : ["Albuminuria with urine albumin/Cr ratio over 200ug/g"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},

    // Contraindications for SGLT2
    "DMSGLT2ContraindicationsGFRBelow30Option" : { "ButtonLabelList" : ["GFR below 30"], "ValueList" : ["eGFR below 30"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DMSGLT2ContraindicationsDM1Option" : { "ButtonLabelList" : ["DM 1"], "ValueList" : ["Diabetes type 1"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DMSGLT2ContraindicationsTransplantOption" : { "ButtonLabelList" : ["Transplant"], "ValueList" : ["renal transplant"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DMSGLT2ContraindicationsDKAOption" : { "ButtonLabelList" : ["Past DKA"], "ValueList" : ["history of DKA"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DMSGLT2ContraindicationsImunosuppressedOption" : { "ButtonLabelList" : ["imunosuppressed"], "ValueList" : ["imunosuppressed"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DMSGLT2ContraindicationsPKDOption" : { "ButtonLabelList" : ["PKD"], "ValueList" : ["PKD"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DMSGLT2ContraindicationsSLEOption" : { "ButtonLabelList" : ["SLE"], "ValueList" : ["Lupus"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DMSGLT2ContraindicationsANCAOption" : { "ButtonLabelList" : ["ANCA"], "ValueList" : ["ANCA"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},

    // SGLT2
    "DMSGLT2EmpagliflozinOption" : { "ButtonLabelList" : ["Empagliflozin"], "ValueList" : ["Empagliflozin 10mg PO daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DMSGLT2ReduceInsulinOption" : { "ButtonLabelList" : ["Reduce Insulin"], "ValueList" : ["Reduce Insulin 20 percent if GFR is over 45"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DMSGLT2ExplainGFRDropOption" : { "ButtonLabelList" : ["Explain AKI"], "ValueList" : ["Expect 10-30 percent drop in eGFR due to hemodynamic effect of reduced filtration. This is not an acute kidney injury, and past studies have shown it is reversable by stopping the SGLT2 inhibitor. Essentially, an SGLT2 inhibitos just stops the hyperfiltration associated with glucosuria and unmasks the true eGFR."], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},

    // Followup
    "DiabetesFollowupOphthoOption" : { "ButtonLabelList" : ["Ophtho"], "ValueList" : ["Outpatient followup with Ophthomology"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DiabetesFollowupPodiatryOption" : { "ButtonLabelList" : ["Podiatry"], "ValueList" : ["Outpatient followup with Podiatry"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},
    "DiabetesFollowupEndocrineOption" : { "ButtonLabelList" : ["Endocrine"], "ValueList" : ["Outpatient followup with Endocrinology"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DiabetesPlan"},



    ///////////////////////////////////////////////////////////
    // CKD
    ///////////////////////////////////////////////////////////
    "CKD_Stage_Modifier" : { "ButtonLabelList" : ["Stage IIIa", "Stage IIIb", "Stage IV", "Stage V"], "ValueList" : ["Stage IIIa", "Stage IIIb", "Stage IV", "Stage V"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKD_Diabetic_Modifier" : { "ButtonLabelList" : ["Diabetic"], "ValueList" : ["Diabetic Kidney Disease"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},

    ////////////////////
    // Cause
    "CKDCausesDiabetesOption" : { "ButtonLabelList" : ["Diabetes"], "ValueList" : ["Diabetes" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDCausesHypertensionOption" : { "ButtonLabelList" : ["Hypertension"], "ValueList" : ["Hypertension" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDCausesPastAKIOption" : { "ButtonLabelList" : ["Past AKI"], "ValueList" : ["Past AKI" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDCausesMedicationsOption" : { "ButtonLabelList" : ["Medications"], "ValueList" : ["Medications"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDCausesObstructionOption" : { "ButtonLabelList" : ["Obstruction"], "ValueList" : ["chronic obstruction"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},

    ////////////////////
    // Status
    "CKDCausesShowCrOption" : { "ButtonLabelList" : ["Show Cr"], "ValueList" : ["Serum Creatinine=" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDCausesShowGFROption" : { "ButtonLabelList" : ["Show GFR"], "ValueList" : [", baseline GFR="], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDCausesShowProtCrOption" : { "ButtonLabelList" : ["Show ProtCr"], "ValueList" : ["Urine Prot/Cr ratio is  suggesting approximately xxxx grams daily proteinuria"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDCausesShowAlbCrOption" : { "ButtonLabelList" : ["Show AlbCr"], "ValueList" : ["xxxx grams of the daily proteinuria is due to Albumin, the rest is other proteins" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKD_Male_Modifier" : { "ButtonLabelList" : ["Male", "Female"], "ValueList" : ["male", "female" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDCausesShow2YrRiskOption" : { "ButtonLabelList" : ["ESRD Risk"], "ValueList" : ["The risk of ESRD within two years is "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDCausesShow5YrRiskOption" : { "ButtonLabelList" : ["Show 5YrRisk"], "ValueList" : ["The risk of ESRD within five years is "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDCausesRiskPaperCitationOption" : { "ButtonLabelList" : ["Risk Paper"], "ValueList" : ["See Tangri N, Stevens LA, Griffith J, et al. A predictive model for progression of chronic kidney disease to kidney failure. JAMA. 2011;305(15) and Tangri N, Grams ME, Levey AS et al Multinational Assessment of Accuracy of Equations for Predicting Risk of Kidney Failure: A Meta-analysis JAMA. 2016;315(2):1-11"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDStatusTransplantOption" : { "ButtonLabelList" : ["Xplant None", "Xplant In-Process", "Xplant Listed", "Xplant Unlisted", "Xplant NotListed"], "ValueList" : ["The patient is has not been evaluated for renal transplant", "The patient is currently being evaluated for renal transplant", "The patient is currently listed for renal transplant", "The patient is currently unlisted for renal transplant but will be reevaluated", "The patient has been evaluated and is not a candidate for renal transplant" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDStatusTreatHTNOption" : { "ButtonLabelList" : ["Treat HTN"], "ValueList" : ["hypertension" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDStatusTreatDMOption" : { "ButtonLabelList" : ["Treat DM"], "ValueList" : ["diabetes" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},

    ////////////////////
    // Workup
    "CKDWorkupGetUrineAlbProtCrOption" : { "ButtonLabelList" : ["Get U Alb"], "ValueList" : ["UrineCreatinine, UrineAlbumin and a BMP and serum Phos, Ca, and Albumin to estimate risk of CKD progressing to ESRD" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDWorkupGetPTHOption" : { "ButtonLabelList" : ["Get PTH"], "ValueList" : ["PTH"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDWorkupGetVitDOption" : { "ButtonLabelList" : ["Get VitD"], "ValueList" : ["Vitamin D" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},

    ////////////////////
    // Indications for SGLT2
    "CKDSGLT2IndicationsDM2Option" : { "ButtonLabelList" : ["DM2"], "ValueList" : ["Diabetes type 2"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDSGLT2IndicationsCKDOption" : { "ButtonLabelList" : ["CKD"], "ValueList" : ["CKD with eGFR over 30"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDSGLT2IndicationsHFrEFOption" : { "ButtonLabelList" : ["HFrEF"], "ValueList" : ["Heart failure with reduced ejection fraction"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDSGLT2IndicationsUACROver200Option" : { "ButtonLabelList" : ["Albuminuria"], "ValueList" : ["Albuminuria with urine albumin/Cr ratio over 200ug/g"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},

    ////////////////////
    // Contraindications for SGLT2
    "CKDSGLT2ContraindicationsGFRBelow30Option" : { "ButtonLabelList" : ["GFR below 30"], "ValueList" : ["eGFR below 30"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDSGLT2ContraindicationsDM1Option" : { "ButtonLabelList" : ["DM 1"], "ValueList" : ["Diabetes type 1"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDSGLT2ContraindicationsTransplantOption" : { "ButtonLabelList" : ["Transplant"], "ValueList" : ["renal transplant"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDSGLT2ContraindicationsDKAOption" : { "ButtonLabelList" : ["Past DKA"], "ValueList" : ["history of DKA"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDSGLT2ContraindicationsImunosuppressedOption" : { "ButtonLabelList" : ["imunosuppressed"], "ValueList" : ["imunosuppressed"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDSGLT2ContraindicationsPKDOption" : { "ButtonLabelList" : ["PKD"], "ValueList" : ["PKD"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDSGLT2ContraindicationsSLEOption" : { "ButtonLabelList" : ["SLE"], "ValueList" : ["Lupus"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDSGLT2ContraindicationsANCAOption" : { "ButtonLabelList" : ["ANCA"], "ValueList" : ["ANCA"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},

    ////////////////////
    // SGLT2
    "CKDSGLT2EmpagliflozinOption" : { "ButtonLabelList" : ["Empagliflozin"], "ValueList" : ["Empagliflozin 10mg PO daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDSGLT2ReduceInsulinOption" : { "ButtonLabelList" : ["Reduce Insulin"], "ValueList" : ["Reduce Insulin 20 percent if GFR is over 45"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDSGLT2ExplainGFRDropOption" : { "ButtonLabelList" : ["Explain AKI"], "ValueList" : ["Expect 10-30 percent drop in eGFR due to hemodynamic effect of reduced filtration. This is not an acute kidney injury, and past studies have shown it is reversable by stopping the SGLT2 inhibitor. Essentially, an SGLT2 inhibitos just stops the hyperfiltration associated with glucosuria and unmasks the true eGFR."], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},

    ////////////////////
    // General
    "CKDStatusNoNSAIDsOption" : { "ButtonLabelList" : ["No NSAIDs"], "ValueList" : ["d/c NSAIDs"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDLisinoprilOption": { "ButtonLabelList" : ["Lisinopril2.5", "Lisinopril5", "Lisinopril10", "Lisinopril20", "Lisinopril40", "Hold"], "ValueList" : ["Lisinopril 2.5mg PO daily", "Lisinopril 5mg PO daily", "Lisinopril 10mg PO daily", "Lisinopril 20mg PO daily", "Lisinopril 40mg PO daily", "Hold home Lisinopril due to AKI"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDLosartanOption": { "ButtonLabelList" : ["Losartan25", "Losartan50", "Losartan100", "Hold"], "ValueList" : ["Losartan 25mg PO daily", "Losartan 50mg PO daily", "Losartan 100mg PO daily", "Hold home Losartan due to AKI"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDLowKDietOption": { "ButtonLabelList" : ["LowK Diet"], "ValueList" : ["Low Potassium Diet"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},

    ////////////////////
    // CKD 3b
    "CKD3bReduceMetforminOption" : { "ButtonLabelList" : ["Metformin"], "ValueList" : ["On discharge halve the dose of Metformin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKD3bStopEmpagliflozinOption" : { "ButtonLabelList" : ["Empagliflozin"], "ValueList" : ["d/c Empagliflozin" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},

    ////////////////////
    // CKD 4
    "CKD4StopMetforminOption" : { "ButtonLabelList" : ["DC Metformin"], "ValueList" : ["On discharge, discontinue Metformin" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKD4StopThiazidesOption" : { "ButtonLabelList" : ["Thiazides"], "ValueList" : ["Change Thiazides to Furosemide" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKD4ReduceGabapentinOption" : { "ButtonLabelList" : ["Gabapentin"], "ValueList" : ["Renally dose Gabapentin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKD4ReduceRanitidineOption" : { "ButtonLabelList" : ["Ranitidine"], "ValueList" : ["Renally dose Ranitidine"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKD4PhosBinderOption" : { "ButtonLabelList" : ["Bicarb"], "ValueList" : ["Sodium Bicarb 650mg PO TID for serum HCO3 below 20"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKD4BicarbOption" : { "ButtonLabelList" : ["Phos Binder"], "ValueList" : ["Sevelamer 800mg PO TID with meals"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},

    ////////////////////
    // Clinics
    "CKDFollowupRenalOption" : { "ButtonLabelList" : ["Renal Clinic"], "ValueList" : ["Renal CKD clinic"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},
    "CKDFollowupTransplantOption" : { "ButtonLabelList" : ["Transplant Clinic"], "ValueList" : ["Renal Transplant clinic for evaluation" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "CKDPlan"},




    ///////////////////////////////////////////////////////////
    // CORONARY ARTERY DISEASE
    ///////////////////////////////////////////////////////////

    ///////////////////
    // Past Workup
    "CADShowProcedureHistoryOption": { "ButtonLabelList" : ["Past PCI", "Past CABG"], "ValueList" : ["s/p percutaneus coronary intervention", "s/p Coronary Artery Bypass Graft"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CADPlan"},
    "CADShowEchoOption": { "ButtonLabelList" : ["Latest Echo"], "ValueList" : ["Latest Echocardiogram showed:"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CADPlan"},
    "CADHomeMedsOption": { "ButtonLabelList" : ["HomeMeds"], "ValueList" : ["Home medications: "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CADPlan"},

    ///////////////////
    // Beta Blockers
    "CADMetoprololTarOption": { "ButtonLabelList" : ["MetopTar 12.5", "MetopTar 25", "MetopTar 50", "MetopTar 75", "MetopTar 100", "Hold"], "ValueList" : ["Metoprolol Tartrate 12.5mg PO BID", "Metoprolol Tartrate 25mg PO BID", "Metoprolol Tartrate 50mg PO BID", "Metoprolol Tartrate 75mg PO BID", "Metoprolol Tartrate 100mg PO BID", "Hold home Metoprolol due to hypotension"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CADPlan"},
    "CADMetoprololSuccOption": { "ButtonLabelList" : ["MetopXL 25", "MetopXL 50", "MetopXL 75", "MetopXL 100", "MetopXL 200", "Hold"], "ValueList" : ["Metoprolol Succinate 25mg PO once daily", "Metoprolol Succinate 50mg PO once daily", "Metoprolol Succinate 75mg PO once daily", "Metoprolol Succinate 100mg PO once daily", "Metoprolol Succinate 200mg PO once daily", "Hold home Metoprolol due to hypotension"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CADPlan"},
    "CADCarvedilolOption": { "ButtonLabelList" : ["Coreg 3.125", "Coreg 6.25", "Coreg 12.5", "Coreg 25", "Hold"], "ValueList" : ["Carvedilol 3.125mg PO BID", "Carvedilol 6.25mg PO BID", "Carvedilol 12.5mg PO BID", "Carvedilol 25mg PO BID", "Hold home Carvedilol due to hypotension"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CADPlan"},
    "CADNSBBOption": { "ButtonLabelList" : ["See Cirrhosis"], "ValueList" : ["Non-specific Beta-Blocker as discussed for Cirrhosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CADPlan"},

    ///////////////////
    // ACE/ARB
    "CADLisinoprilOption": { "ButtonLabelList" : ["Lisinopril2.5", "Lisinopril5", "Lisinopril10", "Lisinopril20", "Lisinopril40", "Hold"], "ValueList" : ["Lisinopril 2.5mg PO daily", "Lisinopril 5mg PO daily", "Lisinopril 10mg PO daily", "Lisinopril 20mg PO daily", "Lisinopril 40mg PO daily", "Hold home Lisinopril due to AKI"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CADPlan"},
    "CADLosartanOption": { "ButtonLabelList" : ["Losartan25", "Losartan50", "Losartan100", "Hold"], "ValueList" : ["Losartan 25mg PO daily", "Losartan 50mg PO daily", "Losartan 100mg PO daily", "Hold home Losartan due to AKI"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CADPlan"},
    "CADSpironiolactoneOption": { "ButtonLabelList" : ["Spironolactone25", "Spironolactone50", "Spironolactone100", "Hold"], "ValueList" : ["Spironolactone 25mg PO daily", "Spironolactone 50mg PO daily", "Spironolactone 100mg PO daily", "Hold home Spironolactone due to AKI"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CADPlan"},
    "CADARNIOption": { "ButtonLabelList" : ["ARNI-Low", "ARNI-High"], "ValueList" : ["valsartan/sacubitril (Entresto) 49/51 mg PO BID", "valsartan/sacubitril (Entresto) 97/103 mg PO BID"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CADPlan"},

    ///////////////////
    // Statin/Aspirin
    "CADAtorvaOption": { "ButtonLabelList" : ["Atorva20", "Atorva40", "Atorva80"], "ValueList" : ["Atorvastatin 20mg PO daily", "Atorvastatin 40mg PO daily", "Atorvastatin 80mg PO daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CADPlan"},
    "CADAsaOption": { "ButtonLabelList" : ["Asa81"], "ValueList" : ["Aspirin 81mg PO daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CADPlan"},
    "CADRivaroxabanOption": { "ButtonLabelList" : ["Rivaroxaban"], "ValueList" : ["Rivaroxaban 2.5mg PO BID (COMPASS Trial protocol)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CADPlan"},
    "CADClopidogrelOption": { "ButtonLabelList" : ["Clopidogrel"], "ValueList" : ["Continue home Clopidogrel 75mg PO daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CADPlan"},





    ///////////////////////////////////////////////////////////
    // COPD CONTROLS
    ///////////////////////////////////////////////////////////

    ///////////////////
    "COPDRespFailureModifier": { "ButtonLabelList" : ["RespFailure"], "ValueList" : ["Acute on chronic hypoxic respiratory failure requiring supplemental oxygen"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDExacerbationOption": { "ButtonLabelList" : ["Exacerbation"], "ValueList" : ["Acute COPD Exacerbation"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDPossibleOption": { "ButtonLabelList" : ["Possible"], "ValueList" : ["Possible Chronic Obstructive Pulmonary Disease"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},

    ///////////////////
    // Staging
    "COPDHomeO2Option": { "ButtonLabelList" : ["1L home O2", "1L home O2 at night", "2L home O2", "2L home O2 at night", "3L home O2", "3L home O2 at night", "4L home O2", "4L home O2 at night", "5L home O2", "5L home O2 at night", "6L home O2", "6L home O2 at night"], "ValueList" : ["1L home O2", "1L home O2 at night", "2L home O2", "2L home O2 at night", "3L home O2", "3L home O2 at night", "4L home O2", "4L home O2 at night", "5L home O2", "5L home O2 at night", "6L home O2", "6L home O2 at night"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDHomeBiPAPOption": { "ButtonLabelList" : ["CPAP night", "BiPAP night"], "ValueList" : ["home CPAP at night", "home BiPAP at night"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDShowFEV1FVC": { "ButtonLabelList" : ["Show FEV1/FVC"], "ValueList" : ["FEV1/FVC="], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDShowFEV1": { "ButtonLabelList" : ["Show FEV1"], "ValueList" : ["FEV1="], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDShowEOS": { "ButtonLabelList" : ["Eos below 300", "Eos over 300"], "ValueList" : ["Serum Eosinophils below 300, suggesting limited response to steroids", "Serum Eosinophils over 300, suggesting good response to steroids"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDGOLDGroupNumber": { "ButtonLabelList" : ["GOLD 1", "GOLD 2", "GOLD 3", "GOLD 4"], "ValueList" : ["GOLD 1 (mild disease, FEV1 over 80 percent predicted)", "GOLD 2 (moderate disease, FEV1 between 50 and 80 percent predicted)", "GOLD 3 (severe disease, FEV1 between 30 and 50 percent predicted)", "GOLD 4 (very severe disease, FEV1 <30 percent predicted)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDGOLDGroup": { "ButtonLabelList" : ["Group A", "Group B", "Group C", "Group D"], "ValueList" : ["Group A", "Group B", "Group C", "Group D"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDGOLDClass": { "ButtonLabelList" : ["Class I", "Class II", "Class III", "Class IV"], "ValueList" : ["Class I", "Class II", "Class III", "Class IV"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},

    ///////////////////
    // Exacerbation
    "COPDTriggerMoreSputumOption": { "ButtonLabelList" : ["More Sputum"], "ValueList" : ["increased sputum"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDTriggerPurulentOption": { "ButtonLabelList" : ["Purulent"], "ValueList" : ["purulent sputum"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDTriggerDyspneaOption": { "ButtonLabelList" : ["Dyspnea"], "ValueList" : ["increased dyspnea"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},

    ///////////////////
    // Triggers
    "COPDTriggerInfectionOption": { "ButtonLabelList" : ["Infection"], "ValueList" : ["infection"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDTriggerSmokingOption": { "ButtonLabelList" : ["Smoking"], "ValueList" : ["Smoking"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDTriggerComplianceOption": { "ButtonLabelList" : ["Compliance"], "ValueList" : ["medication non-compliance"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDTriggerMedChangesOption": { "ButtonLabelList" : ["Med-Changes"], "ValueList" : ["medication changes"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},

    ///////////////////
    // Vitals
    "COPDCurrentO2SatsOption": { "ButtonLabelList" : ["O2 Sat"], "ValueList" : ["Current O2 Sat="], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDCurrentO2Option": { "ButtonLabelList" : ["1L O2 via NC", "2L O2 via NC", "3L O2 via NC", "4L O2 via NC", "5L O2 via NC", "6L O2 via NC", "50%% Venturi mask", "50%% non-rebreather", "20L High Flow Nasal Canula", "30L High Flow Nasal Canula", "40L High Flow Nasal Canula", "Room Air"], "ValueList" : ["1L O2 via NC", "2L O2 via NC", "3L O2 via NC", "4L O2 via NC", "5L O2 via NC", "6L O2 via NC", "50%% Venturi mask", "50%% non-rebreather", "20L High Flow Nasal Canula", "30L High Flow Nasal Canula", "40L High Flow Nasal Canula", "Room Air"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDCurrentCPAPOption": { "ButtonLabelList" : ["CPAP night", "BiPAP night"], "ValueList" : ["On home CPAP at night", "On home BiPAP at night"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDO2VBGOption": { "ButtonLabelList" : ["Latest VBG"], "ValueList" : ["Latest VBG="], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},

    ///////////////////
    // Workup
    "COPDXrayOption": { "ButtonLabelList" : ["Get Xray"], "ValueList" : ["Get Chest XRay"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDGetVBGOption": { "ButtonLabelList" : ["Get VBG"], "ValueList" : ["VBG"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDGetRVPOption": { "ButtonLabelList" : ["Get RVP"], "ValueList" : ["Influenza screen and Respiratory Viral Panel"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDCultureSputOption": { "ButtonLabelList" : ["Culture Sput"], "ValueList" : ["sputum culture"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDCultureBloodOption": { "ButtonLabelList" : ["Culture Blood"], "ValueList" : ["blood cultures"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDUrineAntigensOption": { "ButtonLabelList" : ["Urine Antigens"], "ValueList" : ["urine antigens for legionella, strep pneumo"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDProcalOption": { "ButtonLabelList" : ["Procal"], "ValueList" : ["ProCalcitonin to possibly rule out bacterial infection"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDPFTOption": { "ButtonLabelList" : ["PFT"], "ValueList" : ["Get Pulmonary Function Tests"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDCheckEosOption": { "ButtonLabelList" : ["Eos"], "ValueList" : ["CBC with diff including Eos"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDCheckA1ATOption": { "ButtonLabelList" : ["A1AT"], "ValueList" : ["alpha-1 antitrypsin level and phenotype"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDGetABGOption": { "ButtonLabelList" : ["ABG Q4h"], "ValueList" : ["Q4h VBG for any BiPAP during day"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},

    ///////////////////
    // Bronchodilators
    "COPDAlbuterolOption": { "ButtonLabelList" : ["Alb MDI PRN", "Alb Neb PRN"], "ValueList" : ["Rapid-Acting Bronchodilators: Albuterol MDI PRN Q4h", "Rapid-Acting Bronchodilators: Albuterol Nebulizer PRN Q4h"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDAlbuterolIpratropiumOption": { "ButtonLabelList" : ["PRN Alb/Ipra Neb", "Sched Alb/Ipra Neb"], "ValueList" : ["Rapid-Acting Bronchodilators: Albuterol/Ipratropium nebs Q4h PRN", "Rapid-Acting Bronchodilators: scheduled Albuterol/Ipratropium nebs Q4h"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDLAMAOOption": { "ButtonLabelList" : ["LAMA"], "ValueList" : ["Long-Acting Anti-muscarinic: Tiotropium daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDLABAOption": { "ButtonLabelList" : ["LABA"], "ValueList" : ["Long-Acting Bronchodilators: Mometasone/Formoterol BID"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDRoflumilastOption": { "ButtonLabelList" : ["Roflumilast"], "ValueList" : ["Roflumilast (selective PDE-4 inhibitor) 250 mcg PO daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDMagnesiumOption": { "ButtonLabelList" : ["Magnesium"], "ValueList" : ["Magnesium 2g IV"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},

    ///////////////////
    // AntiInflammatory
    "COPDPrednisoneOption": { "ButtonLabelList" : ["Prednisone"], "ValueList" : ["Prednisone 40mg PO x5days"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDPPIOption": { "ButtonLabelList" : ["PPI"], "ValueList" : ["Pantoprazole while on steroids"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDAzithroOption": { "ButtonLabelList" : ["Azithro"], "ValueList" : ["Azithromycin 500mg daily for 5 days (pneumonia and anti-inflammatory)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},

    ///////////////////
    // Oxygen
    "COPDGiveO2Option": { "ButtonLabelList" : ["Oxygen"], "ValueList" : ["Supplemental oxygen. Titrate O2 for SpO2 between 89 and 92%"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDBiPAPO2Option": { "ButtonLabelList" : ["BiPAP", "BiPAP Night"], "ValueList" : ["BiPAP for 4hrs then reassess", "BiPAP at night"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
    "COPDGuaifenesinOption": { "ButtonLabelList" : ["Guaifenesin"], "ValueList" : ["Guaifenesin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},






    ///////////////////////////////////////////////////////////
    // ESRD CONTROLS
    ///////////////////////////////////////////////////////////

    ///////////////////
    "ESRDAKIOption": { "ButtonLabelList" : ["Acute", "ESRD HD", "ESRD CAPD"], "ValueList" : ["Acute Kidney Injury on Dialysis", "End Stage Renal Disease on Hemodialysis", "End Stage Renal Disease on Peritoneal Dialysis"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},

    ///////////////////
    // Outpatient History
    "ESRDCauseofESRDOption": { "ButtonLabelList" : ["Diabetes", "Hypertension", "Unknown"], "ValueList" : ["Original cause of renal failure was Diabetes", "Original cause of renal failure was Hypertension", "Original cause of renal failure is Unknown"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDScheduleOption": { "ButtonLabelList" : ["Mon/Wed/Fri", "Tue/Thur/Sat"], "ValueList" : ["Mon/Wed/Fri", "Tue/Thur/Sat"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDHomeUnitOption": { "ButtonLabelList" : ["Home unit"], "ValueList" : ["at "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDNephrologistOption": { "ButtonLabelList" : ["Nephrologist"], "ValueList" : ["Outpatient nephrologist is Dr. xxxx"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDOnHDSinceOption": { "ButtonLabelList" : ["Started Date"], "ValueList" : ["On dialysis since xxx"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDMakesUrineOption": { "ButtonLabelList" : ["Makes urine", "anuric"], "ValueList" : ["The patient has residual Renal Function - makes urine daily", "The patient does not have any residual Renal Function - and is oligoric/anuric"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDDryWeightOption": { "ButtonLabelList" : ["Dry Weight kg", "Unknown"], "ValueList" : ["Dry Weight= kg", "Dry Weight is unknown"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDAccessOption": { "ButtonLabelList" : ["LUE AVF", "RUE AVF", "TDC"], "ValueList" : ["Access is LUE AVF", "Access is RUE AVF", "Access is TDC"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDPeritonitisOption": { "ButtonLabelList" : ["No peritonitis", "+peritonitis"], "ValueList" : ["No history of peritonitis", "Positive past history of peritonitis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDLastStoolOption": { "ButtonLabelList" : ["Last Stool"], "ValueList" : ["Last stool was xxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDCAPDTypeOption": { "ButtonLabelList" : ["Manual", "Cycler"], "ValueList" : ["The patient does manual exchanges during the day", "The patient uses a nocturnal cycler"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    ///////////////////
    // CAPD Dialysis
    "ESRDCAPD15PercentOption": { "ButtonLabelList" : ["1x2L 1.5%", "2x2L 1.5%", "3x2L 1.5%", "4x2L 1.5%", "5x2L 1.5%", "1x5L 1.5%", "2x5L 1.5%"], "ValueList" : ["One 2L bag of 1.5% Dextrose", "Two 2L bag of 1.5% Dextrose", "Three 2L bag of 1.5% Dextrose", "Four 2L bag of 1.5% Dextrose", "Five 2L bag of 1.5% Dextrose", "One 5L bag of 1.5% Dextrose", "Two 5L bag of 1.5% Dextrose"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDCAPD25PercentOption": { "ButtonLabelList" : ["1x2L 2.5%", "2x2L 2.5%", "3x2L 2.5%", "4x2L 2.5%", "5x2L 2.5%", "1x5L 2.5%", "2x5L 2.5%"], "ValueList" : ["One 2L bag of 2.5% Dextrose", "Two 2L bag of 2.5% Dextrose", "Three 2L bag of 2.5% Dextrose", "Four 2L bag of 2.5% Dextrose", "Five 2L bag of 2.5% Dextrose", "One 5L bag of 2.5% Dextrose", "Two 5L bag of 2.5% Dextrose"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDCAPD425PercentOption": { "ButtonLabelList" : ["1x2L 4.25%", "2x2L 4.25%", "3x2L 4.25%", "4x2L 4.25%", "5x2L 4.25%", "1x5L 4.25%", "2x5L 4.25%"], "ValueList" : ["One 2L bag of 4.25% Dextrose", "Two 2L bag of 4.25% Dextrose", "Three 2L bag of 4.25% Dextrose", "Four 2L bag of 4.25% Dextrose", "Five 2L bag of 4.25% Dextrose", "One 5L bag of 4.25% Dextrose", "Two 5L bag of 4.25% Dextrose"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDCAPDIcodextrinOption": { "ButtonLabelList" : ["1x2L Icodextrin", "2x2L Icodextrin", "3x2L Icodextrin", "4x2L Icodextrin", "5x2L Icodextrin", "1x5L Icodextrin", "2x5L Icodextrin"], "ValueList" : ["One 2L bag of Icodextrin", "Two 2L bag of Icodextrin", "Three 2L bag of Icodextrin", "Four 2L bag of Icodextrin", "Five 2L bag of Icodextrin", "One 5L bag of Icodextrin", "Two 5L bag of Icodextrin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    ///////////////////
    // Dialysis
    "ESRDDialysisPerRenalOutOption": { "ButtonLabelList" : ["Dialysis"], "ValueList" : ["Continue dialysis as per Nephrology"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "ESRDDialysisPerRenalOutOption" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDRenalVitaminsOption": { "ButtonLabelList" : ["RenalVits"], "ValueList" : ["Replace water soluble vitamins (vitamins B and C) that are dialyzed off"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDLasixPOOption": { "ButtonLabelList" : ["Lasix 80PO", "Lasix 100PO", "Lasix 120PO"], "ValueList" : ["Furosemide 80mg PO daily at breakfast", "Furosemide 100mg PO daily at breakfast", "Furosemide 120mg PO daily at breakfast"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDTorsemideOption": { "ButtonLabelList" : ["Torsemide80mg", "Torsemide100mg"], "ValueList" : ["Torsemide 80mg PO daily at breakfast", "Torsemide 100mg PO daily at breakfast"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    ///////////////////
    // Dialysis Meds
    "ESRDHoldBPMedsOption": { "ButtonLabelList" : ["Hold BP Meds"], "ValueList" : ["Hold blood pressure medications on days of dialysis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDMidodrineOption" : { "ButtonLabelList" : ["Midodrine 5mgTID", "Midodrine 10mgTID", "Midodrine 12mgTID", "Midodrine 15mgTID"], "ValueList" : ["Midodrine 5mg PO TID", "Midodrine 10mg PO TID", "Midodrine 12mg PO TID", "Midodrine 15mg PO TID"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDMiralaxOption": { "ButtonLabelList" : ["Miralax"], "ValueList" : ["Bowel regimen: Miralax 17gm PO scheduled"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDGentamycinOption": { "ButtonLabelList" : ["Gentamycin"], "ValueList" : ["Gentamycin 1% topical cream (not ointment) at PD site"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDHeparinInPDOption": { "ButtonLabelList" : ["Heparin In PD"], "ValueList" : ["If slow draining, add 500 units Heparin to each bag"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    ///////////////////
    // Diet
    "ESRDLowKDietOption": { "ButtonLabelList" : ["Low K Diet"], "ValueList" : ["Low K Diet"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDFluidRestrictOption": { "ButtonLabelList" : ["2L Fluids"], "ValueList" : ["2000mL daily fluid restriction"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},
    "ESRDDietEdOption": { "ButtonLabelList" : ["Education"], "ValueList" : ["Nutrition consult for diet education"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HemoDialysisPlan"},






    ///////////////////////////////////////////////////////////
    // NSTEMI
    ///////////////////////////////////////////////////////////

    ///////////////////
    "NSTEMITitleOption": { "ButtonLabelList" : ["Chest Pain", "Unstable Angina", "NSTEMI", "STEMI"], "ValueList" : ["Chest Pain", "Unstable Angina", "Non-ST Elevated Myocardial Infarction", "Acute Myocardial Infarction"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMICADOption": { "ButtonLabelList" : ["CAD"], "ValueList" : ["Coronary Artery Disease"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},

    ///////////////////
    // Inputs
    "NSTEMIMaleOption": { "ButtonLabelList" : ["Male", "Female"], "ValueList" : ["Male", "Female"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : 0, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},

    ///////////////////
    // Symptoms
    "NSTEMISubSternalOption": { "ButtonLabelList" : ["Substernal"], "ValueList" : ["substernal"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIExertionOption": { "ButtonLabelList" : ["Exertion"], "ValueList" : ["triggered by exertion"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIRestOption": { "ButtonLabelList" : ["Rest"], "ValueList" : ["relieved by rest"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},

    ///////////////////
    // Results
    "NSTEMITropOption": { "ButtonLabelList" : ["Show Trop"], "ValueList" : ["Troponins: "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMITropDeltaOption": { "ButtonLabelList" : ["Trop NoDelta", "TropDelta 0-10", "TropDelta 10%", "TropDelta Over20%"], "ValueList" : ["Troponins have no delta", "Troponin delta is below 10 percent", "Troponin delta is 10-20 percent", "Troponin delta is over 10 percent"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIEKGOption": { "ButtonLabelList" : ["EKG Normal", "EKG LVH", "EKG STDepress", "EKG STDepress"], "ValueList" : ["EKG shows no ischemia", "EKG shows LV hypertrophy but no ischemia", "EKG has ST-depression"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMITypeOption": { "ButtonLabelList" : ["Type 1", "Type 2", "Type 4a"], "ValueList" : ["This is likely a type 1 NSTEMI, due to plaque rupture or erosion,", "This is likely a type 2 NSTEMI, due to demand-induced ischemia", "This is likely a type 4a NSTEMI, with Troponin elevation after PCI"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},

    ///////////////////
    // Risks
    "NSTEMIRiskDiabetesOption": { "ButtonLabelList" : ["Diabetes"], "ValueList" : ["Diabetes"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIRiskHypertensionOption": { "ButtonLabelList" : ["Hypertension"], "ValueList" : ["Hypertension"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIRiskTobaccoOption": { "ButtonLabelList" : ["Tobacco"], "ValueList" : ["tobacco use"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIRiskHighLDLOption": { "ButtonLabelList" : ["High LDL"], "ValueList" : ["High LDL"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIRiskLowLDLOption": { "ButtonLabelList" : ["Low LDL"], "ValueList" : ["Low LDL"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIRiskMaleOver65Option": { "ButtonLabelList" : ["Male 65+yo"], "ValueList" : ["male 65yo or older"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIRiskObesityOption": { "ButtonLabelList" : ["Obese"], "ValueList" : ["obesity (BMI over 30)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIRiskFamilyHistoryOption": { "ButtonLabelList" : ["Family Hx"], "ValueList" : ["parent or sibling with CVD before age 65"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIRiskVascularDiseaseOption": { "ButtonLabelList" : ["CAD/PAD"], "ValueList" : ["prior MI/CVA/PVD"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},

    ///////////////////
    // HEART
    "NSTEMIHEARTHistoryOption": { "ButtonLabelList" : ["History-Low", "History-Med", "History-High"], "ValueList" : ["history slight suspicion", "history moderate suspicion", "history high suspicion"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIHEARTEKGOption": { "ButtonLabelList" : ["EKG Normal", "Norm ST, +LVH/LBBB", "ST Depress"], "ValueList" : ["EKG Normal", "Norm S-T segments but LVH or LBBB", "ST Depression"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIHEARTAGEOption": { "ButtonLabelList" : ["Below 45yo", "45-64yo", "Over 64yo"], "ValueList" : ["age below 45yo", "age 45-64yo", "age over 64yo"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIHEARTRiskOption": { "ButtonLabelList" : ["No Risks", "1-2 Risks", "3+ Risks"], "ValueList" : ["no risk factors", "1-2 risk factors", "3+ risk factors"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIHEARTTroponinsOption": { "ButtonLabelList" : ["Trop Normal", "Trop 1-2xUNL", "Trop 3xUNL"], "ValueList" : ["troponin normal", "troponin 1-2x upper normal limit", "troponin 3x upper normal limit"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},

    ///////////////////
    // TIMI
    "NSTEMITIMITroponinsOption": { "ButtonLabelList" : ["Troponins"], "ValueList" : ["elevated Troponins"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMITIMIEKGChangesOption": { "ButtonLabelList" : ["EKG changes"], "ValueList" : ["EKG changes"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMITIMI3RiskFactorsOption": { "ButtonLabelList" : ["3+ risk factors"], "ValueList" : ["3+ cardiac risk factors"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMITIMIOver65yoOption": { "ButtonLabelList" : ["Over 65yo"], "ValueList" : [">65yo"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMITIMIKnownCADOption": { "ButtonLabelList" : ["Known CAD"], "ValueList" : ["known CAD"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMITIMIOnAspirinOption": { "ButtonLabelList" : ["On aspirin"], "ValueList" : ["on aspirin"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMITIMI2Episodes24hrsOption": { "ButtonLabelList" : ["Twice in 24hrs"], "ValueList" : ["occurred twice in 24hrs"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},

    ///////////////////
    // Eval
    "NSTEMICheckEKGOption": { "ButtonLabelList" : ["Check EKG"], "ValueList" : ["EKG"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMICheckTroponinsOption": { "ButtonLabelList" : ["Check Troponins"], "ValueList" : ["Troponins"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIAMEKGOption": { "ButtonLabelList" : ["EKG in AM"], "ValueList" : ["EKG in morning"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIUDSOption": { "ButtonLabelList" : ["Check UDS"], "ValueList" : ["urine drugs of abuse screen"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIGetLipidOption": { "ButtonLabelList" : ["Get Lipid panel"], "ValueList" : ["lipid panel"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIGetA1cOption": { "ButtonLabelList" : ["Get HgbA1c"], "ValueList" : ["HgbA1c"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},

    ///////////////////
    // Anti-Platelet
    "NSTEMIAsaOption": { "ButtonLabelList" : ["Asa 325"], "ValueList" : ["Aspirin 325mg PO once then 81mg daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMITicagrelorOption": { "ButtonLabelList" : ["Ticagrelor"], "ValueList" : ["Ticagrelor (PGY12 blockade) with loading dose 180mg PO once, then 90mg BID "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIPlavixOption": { "ButtonLabelList" : ["Plavix"], "ValueList" : ["Clopidogrel (PGY12 blockade) with loading dose 300mg, then 150mg daily for 12 months "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},

    ///////////////////
    // Anti-Coag
    "NSTEMIHeparinDripOption": { "ButtonLabelList" : ["Heparin"], "ValueList" : ["Heparin drip if TIMI is over 5"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMILovenoxOption": { "ButtonLabelList" : ["Enoxaparin"], "ValueList" : ["Enoxaparin 1mg/kg subcu BID"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},

    ///////////////////
    // Management
    "NSTEMIStatinOption": { "ButtonLabelList" : ["Atorvastatin 80"], "ValueList" : ["Atorvastatin 80mg"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIMetoprololTarOption": { "ButtonLabelList" : ["MetopTar 12.5", "MetopTar 25", "MetopTar 50", "MetopTar 75", "MetopTar 100", "Hold"], "ValueList" : ["Metoprolol Tartrate 12.5mg PO BID", "Metoprolol Tartrate 25mg PO BID", "Metoprolol Tartrate 50mg PO BID", "Metoprolol Tartrate 75mg PO BID", "Metoprolol Tartrate 100mg PO BID", "Hold home Metoprolol due to hypotension"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIMetoprololSuccOption": { "ButtonLabelList" : ["MetopXL 25", "MetopXL 50", "MetopXL 75", "MetopXL 100", "MetopXL 200", "Hold"], "ValueList" : ["Metoprolol Succinate 25mg PO once daily", "Metoprolol Succinate 50mg PO once daily", "Metoprolol Succinate 75mg PO once daily", "Metoprolol Succinate 100mg PO once daily", "Metoprolol Succinate 200mg PO once daily", "Hold home Metoprolol due to hypotension"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMICarvedilolOption": { "ButtonLabelList" : ["Coreg 3.125", "Coreg 6.25", "Coreg 12.5", "Coreg 25", "Hold"], "ValueList" : ["Carvedilol 3.125mg PO BID", "Carvedilol 6.25mg PO BID", "Carvedilol 12.5mg PO BID", "Carvedilol 25mg PO BID", "Hold home Carvedilol due to hypotension"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},

    ///////////////////
    // ACE/ARB
    "NSTEMILisinoprilOption": { "ButtonLabelList" : ["Lisinopril2.5", "Lisinopril5", "Lisinopril10", "Lisinopril20", "Lisinopril40", "Hold"], "ValueList" : ["Lisinopril 2.5mg PO daily", "Lisinopril 5mg PO daily", "Lisinopril 10mg PO daily", "Lisinopril 20mg PO daily", "Lisinopril 40mg PO daily", "Hold home Lisinopril due to AKI"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMILosartanOption": { "ButtonLabelList" : ["Losartan25", "Losartan50", "Losartan100", "Hold"], "ValueList" : ["Losartan 25mg PO daily", "Losartan 50mg PO daily", "Losartan 100mg PO daily", "Hold home Losartan due to AKI"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMISpironiolactoneOption": { "ButtonLabelList" : ["Spironolactone25", "Spironolactone50", "Spironolactone100", "Hold"], "ValueList" : ["Spironolactone 25mg PO daily", "Spironolactone 50mg PO daily", "Spironolactone 100mg PO daily", "Hold home Spironolactone due to AKI"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIARNIOption": { "ButtonLabelList" : ["ARNI-Low", "ARNI-High"], "ValueList" : ["valsartan/sacubitril (Entresto) 49/51 mg PO BID", "valsartan/sacubitril (Entresto) 97/103 mg PO BID"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},

    ///////////////////
    // Workup
    "NSTEMIGetEchoOption": { "ButtonLabelList" : ["Get Echo"], "ValueList" : ["Get Echocardiogram"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIHTNControlOption": { "ButtonLabelList" : ["Treat HTN"], "ValueList" : ["Reduce afterload with hypertension management"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMICheckICDOption": { "ButtonLabelList" : ["Check ICD"], "ValueList" : ["Interrogate ICD"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},

    ///////////////////
    // Followup
    "NSTEMIStressTestOption": { "ButtonLabelList" : ["Inpt Stress", "Outpt Stress"], "ValueList" : ["Stress test as inpatient", "Stress test either as outpatient. Exercise if pt is able. EKG is resting EKG is normal."], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMITeleOption": { "ButtonLabelList" : ["Telemetry"], "ValueList" : ["Continuous bedside Telemetry"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},
    "NSTEMIHoldNSAIDsOption": { "ButtonLabelList" : ["Stop NSAIDs"], "ValueList" : ["Hold all non-sterodials while managing possible acute infarction"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NSTEMIPlan"},







    ///////////////////////////////////////////////////////////
    // DKA
    ///////////////////////////////////////////////////////////
    "DKATypeModifierOption" : { "ButtonLabelList" : ["DKA", "HHNS"], "ValueList" : ["Diabetic Ketoacidosis", "Hyperglycemic Hyperosmolar State"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},

    //////////////////////
    // Admission Stats
    "DKASeverityModifierOption" : { "ButtonLabelList" : ["Mild", "Moderate", "Severe"], "ValueList" : ["On admission, this was Mild (ABG pH 7.25 - 7.3)", "On admission, this was Moderate (ABG pH 7.0 - 7.24)", "On admission, this was Severe (ABG pH below 7.0)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAShowBicarbOption" : { "ButtonLabelList" : ["Bicarb"], "ValueList" : ["Bicarb = " ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAShowAnionGapOption" : { "ButtonLabelList" : ["Anion Gap"], "ValueList" : ["Anion Gap = " ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAShowBloodGasOption" : { "ButtonLabelList" : ["ABG"], "ValueList" : ["ABG = " ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAShowKetonesOption" : { "ButtonLabelList" : ["U Ketones"], "ValueList" : ["Urine Ketones are present" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAShowBetaHydroxyOption" : { "ButtonLabelList" : ["BetaOHButy"], "ValueList" : ["Beta Hydroxybutyrate=" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAShowGlucoseOption" : { "ButtonLabelList" : ["Glucose"], "ValueList" : ["serum Glucose=" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},

    ///////////////////////////
    // Baseline
    "DKAShowCausesOption" : { "ButtonLabelList" : ["Non-Compliance", "Infection"], "ValueList" : ["medication non-compliance", "infection"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAStatusShowA1cOption" : { "ButtonLabelList" : ["Show A1c"], "ValueList" : ["Latest HgbA1c = " ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAStatusShowWhenDiagnosedOption" : { "ButtonLabelList" : ["When Diag"], "ValueList" : ["Diagnosed approximately xxx, if type 2 anticipate nephropathy, retinopathy, and gradual beta cell dysfunction over time" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAStatusShowHomeRegimenOption" : { "ButtonLabelList" : ["Home Regimen"], "ValueList" : ["Home Regimen is" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAWorkupGetA1cOption" : { "ButtonLabelList" : ["Get A1c"], "ValueList" : ["Check Hgb A1c"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAWorkupGetLactateOption" : { "ButtonLabelList" : ["Get Lactate"], "ValueList" : ["Check serum lactate to rule out a more dangerous acidosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},

    //////////////////////
    // Fluids
    "DKAFluidBolusOption" : { "ButtonLabelList" : ["1L NS"], "ValueList" : ["Bolus 1L NS" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAFluidRateOption" : { "ButtonLabelList" : ["NS Rate"], "ValueList" : ["NS at 20 ml/kg/hr" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAHalfNSFluidRateOption" : { "ButtonLabelList" : ["1/2NS rate"], "ValueList" : ["1/2NS at 20 ml/kg/hr when serum sodium is below 133" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAD5HalfNSFluidRateOption" : { "ButtonLabelList" : ["D5W 1/2NS"], "ValueList" : ["D51/2NS at 150-200 ml/hr when serum glucose is below 200" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},

    //////////////////////
    // Insulin Drip
    "DKAInsulinDripBolusOption" : { "ButtonLabelList" : ["Insulin Bolus"], "ValueList" : ["Bolus Regular Insulin 0.1 unit per Kg once" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAInsulinDripOption" : { "ButtonLabelList" : ["Insulin Drip"], "ValueList" : ["Insulin drip, with starting rate 0.1 unit per Kg per hour"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAInsulinDripHoldParamsOption" : { "ButtonLabelList" : ["Hold Params"], "ValueList" : ["Do not start insulin until K is over 3.3"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAInsulinDripExpectGlcOption" : { "ButtonLabelList" : ["Expect Glc"], "ValueList" : ["Expect Glc to drop 50-75 mg/L per hour. Titrate insulin and D5 1/2NS drips to keep Glc between 150 and 200 until gap closes"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},

    //////////////////////
    // Transition to Subcu Insulin
    "DKAInsulinDripCriteriaOption" : { "ButtonLabelList" : ["Criteria"], "ValueList" : ["Start subcu insulin when anion gap closes, and patient is able to take PO food"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAInsulinDripStopDripTimeOption" : { "ButtonLabelList" : ["Stop Drip Time"], "ValueList" : ["Continue insulin drip for 2 hours after starting subcu insulin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},

    /////////////////////
    // Subcu Insulin
    "DKASubcuInsulinStartHomeOption" : { "ButtonLabelList" : ["Home Subcu"], "ValueList" : ["Start home insulin regimen" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKASubcuInsulinNewRegimenOption" : { "ButtonLabelList" : ["New Subcu"], "ValueList" : ["The patient is insulin naive, so start 0.5 units/kg, and divide this between half basal (glargine QHS) and the other half divided into 3 prandial doses" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKASlidingScaleInsulinOption" : { "ButtonLabelList" : ["Sliding Scale"], "ValueList" : ["Sliding scale insulin" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},

    //////////////////////
    // Electrolytes
    "DKAGetLabsOption" : { "ButtonLabelList" : ["Q4h Labs"], "ValueList" : ["Check Basic Metabolic Panel, Mg, Phos Q4h"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAPRNBicarbOption" : { "ButtonLabelList" : ["PRN Bicarb", "Hi PRN Bicarb"], "ValueList" : [" - If pH below 7.0, then give 50 mmol HCO3 in 200mL water with 10 mEq KCl", "If pH below 6.9, then give 100 mmol HCO3 in 400mL water with 20 mEq KCl"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAPRNKOption" : { "ButtonLabelList" : ["PRN K"], "ValueList" : ["Maintain Potassium between 4 and 5"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAPRNPhosOption" : { "ButtonLabelList" : ["PRN Phos"], "ValueList" : ["Give 30 mEq KPhos when serum PO4 is below 1.0 mg/dL" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},


    ///////////////////////////
    // Followup
    "DKADMEducationOption" : { "ButtonLabelList" : ["DM Ed"], "ValueList" : ["Diabetes Education" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKANutritionEducationOption" : { "ButtonLabelList" : ["Nutrition Ed"], "ValueList" : ["Consult Nutrition for patient education on diet"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAFollowupOphthoOption" : { "ButtonLabelList" : ["Ophtho"], "ValueList" : ["Outpatient followup with Ophthomology"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAFollowupPodiatryOption" : { "ButtonLabelList" : ["Podiatry"], "ValueList" : ["Outpatient followup with Podiatry"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},
    "DKAFollowupEndocrineOption" : { "ButtonLabelList" : ["Endocrine"], "ValueList" : ["Outpatient followup with Endocrinology"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : 0, "savedToggleState" : 0, "PlanSectionID" : "DKAPlan"},




    ///////////////////////////////////////////////////////////
    // Pneumonia CONTROL PANEL
    ///////////////////////////////////////////////////////////
    "PneumoniaHAPModifier" : { "ButtonLabelList" : ["CAP", "HAP", "VAP"], "ValueList" : ["Community-Acquired Pneumonia", "Healthcare-Associated Pneumonia", "Ventillator-Associated Pneumonia"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaRespFailureModifier": { "ButtonLabelList" : ["RespFailure"], "ValueList" : ["Acute hypoxic respiratory failure requiring supplemental oxygen"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PneumoniaPlan"},

    // Criteria
    "PneumoniaCoughOption" : { "ButtonLabelList" : ["Cough"], "ValueList" : ["Cough"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaDyspneaOption" : { "ButtonLabelList" : ["Dyspnea"], "ValueList" : ["Dyspnea"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaSputumChangesOption" : { "ButtonLabelList" : ["Sputum"], "ValueList" : ["sputum changes"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaFeversOption" : { "ButtonLabelList" : ["Fevers"], "ValueList" : ["Subjective Fevers"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaXRayOption" : { "ButtonLabelList" : ["XRay"], "ValueList" : ["Radiologic evidence (XRay, CT)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},

    // CURB65 Criteria
    "PneumoniaCURB65ConfusionOption" : { "ButtonLabelList" : ["confusion"], "ValueList" : ["confusion"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaCURB65BUNOver20Option" : { "ButtonLabelList" : ["BUN over 20"], "ValueList" : ["BUN over 20"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaCURB65RROver30Option" : { "ButtonLabelList" : ["RR over 30"], "ValueList" : ["RR over 30"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaCURB65BPBelow90Option" : { "ButtonLabelList" : ["BP below 90/60"], "ValueList" : ["BP below 90/60"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaCURB65AgeOver65yoOption" : { "ButtonLabelList" : ["Age over 65"], "ValueList" : ["Age over 65"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},

    // SIRS Criteria
    "PneumoniaSIRSHROption" : { "ButtonLabelList" : ["HR over 90"], "ValueList" : ["HR over 90"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaSIRSTempOption" : { "ButtonLabelList" : ["Temp over 100.4"], "ValueList" : ["Temp over 100.4"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaSIRSRROption" : { "ButtonLabelList" : ["RR over 20"], "ValueList" : ["RR over 20"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaSIRSWBCOption" : { "ButtonLabelList" : ["WBC over 12"], "ValueList" : ["WBC over 12"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},

    // Workup
    "PneumoniaWUNaresOption" : { "ButtonLabelList" : ["Chest XRay"], "ValueList" : ["Check MRSA Nares"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaWUXRayOption" : { "ButtonLabelList" : ["Chest XRay"], "ValueList" : ["Get Chest XRay"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaWUBloodCultureOption" : { "ButtonLabelList" : ["Blood Cx"], "ValueList" : ["blood"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaWUSputumCultureOption" : { "ButtonLabelList" : ["Sputum Cx"], "ValueList" : ["sputum"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaWURVPOption" : { "ButtonLabelList" : ["RVP"], "ValueList" : ["Resp viral panel"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaWUMRSANaresOption" : { "ButtonLabelList" : ["MRSA Nares"], "ValueList" : ["MRSA Nares (to rule out MRSA and stop Vanc)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaWUStrepUrineAntigenOption" : { "ButtonLabelList" : ["Urine Strep"], "ValueList" : ["urine strep antigen"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaWULegionellaUrineAntigenOption" : { "ButtonLabelList" : ["Urine Legionella"], "ValueList" : ["urine legionella antigen"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaWUProcalOption" : { "ButtonLabelList" : ["Procal"], "ValueList" : ["Procalcitonin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaWUCRPOption" : { "ButtonLabelList" : ["CRP"], "ValueList" : ["C-Reactive Protein"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaWULactateOption" : { "ButtonLabelList" : ["Lactate"], "ValueList" : ["serum lactate"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},

    // Causes
    "PneumoniaSwallowStudyOption" : { "ButtonLabelList" : ["Swallow Study"], "ValueList" : ["Swallow Study"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaPanorexOption" : { "ButtonLabelList" : ["Panorex"], "ValueList" : ["Get Panorex"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},

    // Antibiotics
    "PneumoniaCeftriaxoneOption" : { "ButtonLabelList" : ["Ceftriaxone"], "ValueList" : ["Ceftriaxone 2g IV daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaAzithromycinOption" : { "ButtonLabelList" : ["Azithromycin"], "ValueList" : ["Azithromycin 500mg IV"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaVancOption" : { "ButtonLabelList" : ["Vanc"], "ValueList" : ["Vancomycin with pharmacy titration to levels (cover gram positives including MRSA)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaPipTazoOption" : { "ButtonLabelList" : ["Pip/Tazo"], "ValueList" : ["Pip/Tazo 3.375g IV Q6h (cover gram negatives and anaerobes)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaCefepimeOption" : { "ButtonLabelList" : ["Cefepime"], "ValueList" : ["Cefepimg 2g IV q8h"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaMetronidazoleOption" : { "ButtonLabelList" : ["Metronidazole"], "ValueList" : ["Metronidazole 500mg q6h"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},

    // Misc
    "PneumoniaNebsOption" : { "ButtonLabelList" : ["Nebs"], "ValueList" : ["Albuterol/Ipratropium nebs Q4h PRN"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaGuaifenesinOption" : { "ButtonLabelList" : ["Guaifenesin"], "ValueList" : ["Guaifenesin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},
    "PneumoniaInspirometerOption" : { "ButtonLabelList" : ["Inspirometer"], "ValueList" : ["Inspirometer"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "PneumoniaPlan"},





    ///////////////////////////////////////////////////////////
    // Stroke CONTROLS
    ///////////////////////////////////////////////////////////

    ///////////////////
    "StrokeAcuteOption": { "ButtonLabelList" : ["Acute", "Chronic"], "ValueList" : ["Acute", "Chronic"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},

    ///////////////////
    // Symptoms
    "StrokeOnsetOption": { "ButtonLabelList" : ["Onset"], "ValueList" : ["onset: "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},

    ///////////////////
    // Imaging
    "StrokeImagingHeadCTOption": { "ButtonLabelList" : ["Head CT"], "ValueList" : ["Head CT without contrast"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},
    "StrokeImagingCTAOption": { "ButtonLabelList" : ["CTA"], "ValueList" : ["Carotid angiography"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},
    "StrokeImagingMRIOption": { "ButtonLabelList" : ["MRI"], "ValueList" : ["MRI brain"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},
    "StrokeImagingCarotidOption": { "ButtonLabelList" : ["Carotid"], "ValueList" : ["Carotid Dopplers"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},
    "StrokeImagingEchoOption": { "ButtonLabelList" : ["Echo"], "ValueList" : ["Echo with bubble study"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},

    ///////////////////
    // Causes
    "StrokeGetLDLOption": { "ButtonLabelList" : ["Get LDL"], "ValueList" : ["morning lipid panel"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},
    "StrokeGetA1cOption": { "ButtonLabelList" : ["Get A1c"], "ValueList" : ["HgbA1c"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},
    "StrokeGetINROption": { "ButtonLabelList" : ["Get INR"], "ValueList" : ["PT/INR"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},
    "StrokeGetSMEAROption": { "ButtonLabelList" : ["Get Smear"], "ValueList" : ["peripheral smear for schistocytes"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},
    "StrokeGetHaptoglobinsOption": { "ButtonLabelList" : ["Get Haptoglobins"], "ValueList" : ["haptoglobin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},
    "StrokeGetLDHOption": { "ButtonLabelList" : ["Get LDH"], "ValueList" : ["LDH"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},

    ///////////////////
    // Anticoag
    "StrokeHoldDay1Option": { "ButtonLabelList" : ["Day 1 Hold"], "ValueList" : ["Hold anticoagulation for 24hrs after admission if given tPA"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},
    "StrokeAsaOnDay2Option": { "ButtonLabelList" : ["Day 2 Asa"], "ValueList" : ["Aspirin 325mg on day 2 if no tPA but wait until day 3 if given tPA, then 81mg daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},
    "StrokeSCDsOption": { "ButtonLabelList" : ["SCDs"], "ValueList" : ["Compression devices for DVT prophylaxis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},

    ///////////////////
    // Hypertension
    "StrokeHTNDay1HoldOption": { "ButtonLabelList" : ["Day 1 Hold"], "ValueList" : ["Hold antihypertensives for first day, PRN Labetalol for BP over 220/120 (185/105 if tPA), hold for HR below 60"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},
    "StrokeHTNDay2ResumeOption": { "ButtonLabelList" : ["Day 2 Resume"], "ValueList" : ["Slowly resume antihypertensives after first day"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},

    ///////////////////
    // Dysphagia
    "StrokeDysphagiaNPOOption": { "ButtonLabelList" : ["NPO"], "ValueList" : ["NPO (with PO meds and sips of water OK) until Swallow study"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},
    "StrokeDysphagiaStudyOption": { "ButtonLabelList" : ["Swallow Study"], "ValueList" : ["Swallow Study"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},

    ///////////////////
    // Management
    "StrokeAsaOption": { "ButtonLabelList" : ["Asa 81"], "ValueList" : ["Asa 81mg daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},
    "StrokeStatinOption": { "ButtonLabelList" : ["Atorvastatin 80"], "ValueList" : ["Atorvastatin 80mg"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "StrokePlan"},



    ///////////////////////////////////////////////////////////
    // AFib CONTROLS
    ///////////////////////////////////////////////////////////

    ///////////////////
    "AFibParoxtsmalOption": { "ButtonLabelList" : ["Paroxysmal"], "ValueList" : ["Paroxysmal "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibRVROption": { "ButtonLabelList" : ["RVR"], "ValueList" : [" with Rapid Ventricular Rate"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},

    ///////////////////
    // Eval
    "AFibCheckEKGOption": { "ButtonLabelList" : ["Check EKG"], "ValueList" : ["Check EKG"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibGetEchoOption": { "ButtonLabelList" : ["Get Echo"], "ValueList" : ["Get Cardiac Echocardiogram to rule out valvular disease and assess chamber dilation"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibUDSOption": { "ButtonLabelList" : ["Check UDS"], "ValueList" : ["Check urine drugs of abuse screen"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibTSHOption": { "ButtonLabelList" : ["Check TSH"], "ValueList" : ["Check TSH to rule out thyroid causes"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibKMgOption": { "ButtonLabelList" : ["Check K,Mg"], "ValueList" : ["Check K and Mg, and supplement to keep K over 4"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},

    ///////////////////
    // CHADS2VASc
    "AFibCHADSVaSCValvularOption": { "ButtonLabelList" : ["Valvular"], "ValueList" : ["CHADSVaSC is not appropriate for valvular A-fib"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibCHADSVaSCCHFOption": { "ButtonLabelList" : ["CHF"], "ValueList" : ["CHF"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibCHADSVaSCHypertensionOption": { "ButtonLabelList" : ["Hypertension"], "ValueList" : ["Hypertension"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibCHADSVaSCOver75yoOption": { "ButtonLabelList" : ["Over75yo"], "ValueList" : ["Age over 75(2pts)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibCHADSVaSCDiabetesOption": { "ButtonLabelList" : ["Diabetes"], "ValueList" : ["Diabetes"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibCHADSVaSCPVDOption": { "ButtonLabelList" : ["PVD"], "ValueList" : ["PVD"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibCHADSVaSCOver65yoOption": { "ButtonLabelList" : ["Over65yo"], "ValueList" : ["Age over 65"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibCHADSVaSCStrokeOption": { "ButtonLabelList" : ["Stroke"], "ValueList" : ["Stroke(2pts)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibCHADSVaSCFemaleOption": { "ButtonLabelList" : ["Female"], "ValueList" : ["Female"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},

    ///////////////////
    // Has-BLED
    "AFibHasBLEDSBPOver160Option": { "ButtonLabelList" : ["SBPOver160"], "ValueList" : ["Hypertension (SBP over 160)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibHasBLEDESRDorCrOver2Option": { "ButtonLabelList" : ["ESRDorCrOver2.2"], "ValueList" : ["Renal disease (such as ESRD, transplant, CKD with Cr over 2.26)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibHasBLEDCirrhosisOption": { "ButtonLabelList" : ["Cirrhosis"], "ValueList" : ["Liver disease, (such as cirrhosis or tBili over 2x UNL)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},

    "AFibHasBLEDStrokeOption": { "ButtonLabelList" : ["Stroke"], "ValueList" : ["Stroke"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibHasBLEDPastBleedOption": { "ButtonLabelList" : ["Past Bleed"], "ValueList" : ["Prior major bleeding"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibHasBLEDLabileINROption": { "ButtonLabelList" : ["Labile INR"], "ValueList" : ["Labile INR"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibHasBLEDOver65yoOption": { "ButtonLabelList" : ["Over65yo"], "ValueList" : ["over 65yo"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibHasBLEDOnAntiPltOption": { "ButtonLabelList" : ["On Anti-Plt"], "ValueList" : ["On anti-platelet"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibHasBLEDEtOHOption": { "ButtonLabelList" : ["EtOH (8/wk)"], "ValueList" : ["Alcohol use (8+ drinks/week)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},

    ///////////////////
    // Risks
    "AFibRisksPastDVTOption": { "ButtonLabelList" : ["past DVT/PE"], "ValueList" : ["past DVT/PE"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibRisksPastCVAOption": { "ButtonLabelList" : ["past CVA"], "ValueList" : ["past CVA"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibRisksCADOption": { "ButtonLabelList" : ["CAD"], "ValueList" : ["coronary artery disease"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibRisksOCPOption": { "ButtonLabelList" : ["OCPs"], "ValueList" : ["oral contraceptives"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibRisksMiscarriageOption": { "ButtonLabelList" : ["Miscarriage"], "ValueList" : ["past miscarriages"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibRisksFamilyOption": { "ButtonLabelList" : ["Family"], "ValueList" : ["family history of clotting disorders"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},

    ///////////////////
    // Home Meds
    "AFibHomeCoumadinOption": { "ButtonLabelList" : ["Coumadin"], "ValueList" : ["Coumadin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibHomeApixibanOption": { "ButtonLabelList" : ["Apixiban"], "ValueList" : ["Apixiban"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},

    ///////////////////
    // Rate Control
    "AFibMetoprololTarOption": { "ButtonLabelList" : ["MetopTar 12.5", "MetopTar 25", "MetopTar 50", "MetopTar 75", "MetopTar 100", "Hold"], "ValueList" : ["Metoprolol Tartrate 12.5mg PO BID", "Metoprolol Tartrate 25mg PO BID", "Metoprolol Tartrate 50mg PO BID", "Metoprolol Tartrate 75mg PO BID", "Metoprolol Tartrate 100mg PO BID", "Hold home Metoprolol due to hypotension"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibMetoprololSuccOption": { "ButtonLabelList" : ["MetopXL 25", "MetopXL 50", "MetopXL 75", "MetopXL 100", "MetopXL 200", "Hold"], "ValueList" : ["Metoprolol Succinate 25mg PO once daily", "Metoprolol Succinate 50mg PO once daily", "Metoprolol Succinate 75mg PO once daily", "Metoprolol Succinate 100mg PO once daily", "Metoprolol Succinate 200mg PO once daily", "Hold home Metoprolol due to hypotension"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibCarvedilolOption": { "ButtonLabelList" : ["Coreg 3.125", "Coreg 6.25", "Coreg 12.5", "Coreg 25", "Hold"], "ValueList" : ["Carvedilol 3.125mg PO BID", "Carvedilol 6.25mg PO BID", "Carvedilol 12.5mg PO BID", "Carvedilol 25mg PO BID", "Hold home Carvedilol due to hypotension"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibDiltiazemPOOption": { "ButtonLabelList" : ["Diltiazem 30", "Diltiazem 60", "Diltiazem 90", "Diltiazem 120"], "ValueList" : ["Diltiazem 30mg PO daily", "Diltiazem 60mg PO daily", "Diltiazem 90mg PO daily", "Diltiazem 120mg PO daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},

    ///////////////////
    // Drip
    "AFibIVMetoprololOption": { "ButtonLabelList" : ["IV Metoprolol"], "ValueList" : ["IV Metoprolol 5mg IV Q15min for up to 3 doses"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibDiltiazemDripOption": { "ButtonLabelList" : ["Dilt Drip"], "ValueList" : ["Diltiazem drip fixed rate, 2.5/hr"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibAmiodaroneDripOption": { "ButtonLabelList" : ["Amiodarone"], "ValueList" : ["Amiodarone 150 mg IV bolus in 10 minutes, THEN. 1 mg/min IV for 6hrs, THEN. 0.5 mg/min IV for 18hrs"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibHRTargetOption": { "ButtonLabelList" : ["HR Target"], "ValueList" : ["Target heart rate below 110 bpm"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},

    ///////////////////
    // Anti-Plt
    "AFibAsaOption": { "ButtonLabelList" : ["Asa 81"], "ValueList" : ["Aspirin 81mg"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibApixabanOption": { "ButtonLabelList" : ["Apixaban"], "ValueList" : ["Apixaban (direct Xa inhibitor)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibRivaroxabanOption": { "ButtonLabelList" : ["Rivaroxaban"], "ValueList" : ["Rivaroxaban (direct Xa inhibitor)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibCoumadinOption": { "ButtonLabelList" : ["Coumadin"], "ValueList" : ["Coumadin mg PO daily"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibOnlyCoumadinOption": { "ButtonLabelList" : ["Only Coumadin"], "ValueList" : ["VitaminK Antagonists only since this is valvular"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},

    ///////////////////
    // Management
    "AFibManageOption": { "ButtonLabelList" : ["Electrolytes"], "ValueList" : ["Manage Electrolytes as discussed elsewhere"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibManageInfectionOption": { "ButtonLabelList" : ["Infection"], "ValueList" : ["Manage Infection as discussed elsewhere"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibManageCHFOption": { "ButtonLabelList" : ["CHF"], "ValueList" : ["Manage heart failure as discussed elsewhere"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},
    "AFibManageOSAOption": { "ButtonLabelList" : ["OSA"], "ValueList" : ["Manage OSA as discussed elsewhere"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AFibPlan"},




    ///////////////////////////////////////////////////////////
    // Asthma CONTROLS
    ///////////////////////////////////////////////////////////
    "AsthmaExacerbationOption": { "ButtonLabelList" : ["Exacerbation"], "ValueList" : ["Acute Exacerbation of Chronic Asthma"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},

    ///////////////////
    // Staging
    "AsthmaExacerbationTypeOption": { "ButtonLabelList" : ["Mild", "Moderate", "Severe"], "ValueList" : ["Acutely this is a Mild exacerbation (dyspnea with activity)", "Acutely this is a Moderate exacerbation (Dyspnea limits usual activity)", "Acutely this is a Severe exacerbation (Dyspnea at rest, interferes with speaking)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaTypeOption": { "ButtonLabelList" : ["Intermittent", "Mild Persistent", "Moderate Persistent", "Severe Persistent"], "ValueList" : ["At baseline, this is Intermittent asthma (use PRN albuterol less than 2x per week, less than 2 per nocturnal attacks per month)", "At baseline, this is Mild Persistent asthma (use PRN albuterol not daily, nocturnal attacks less frequently than weekly)", "At baseline, this is Moderate Persistent asthma (daily)", "At baseline, this is Severe Persistent (throughout the day)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},

    ///////////////////
    // Triggers
    "AsthmaTriggerInfectionOption": { "ButtonLabelList" : ["Infection"], "ValueList" : ["infection"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaTriggerSmokingOption": { "ButtonLabelList" : ["Smoking"], "ValueList" : ["smoking"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaTriggerComplianceOption": { "ButtonLabelList" : ["Compliance"], "ValueList" : ["medication non-compliance"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaTriggerMedChangesOption": { "ButtonLabelList" : ["Med-Changes"], "ValueList" : ["medication changes"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},

    ///////////////////
    // Vitals
    "AsthmaCurrentO2SatsOption": { "ButtonLabelList" : ["O2 Sat"], "ValueList" : ["Current O2 Sat="], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaCurrentO2Option": { "ButtonLabelList" : ["1L O2 via NC", "2L O2 via NC", "3L O2 via NC", "4L O2 via NC", "5L O2 via NC", "6L O2 via NC", "50%% Venturi mask", "50%% non-rebreather", "20L High Flow Nasal Canula", "30L High Flow Nasal Canula", "40L High Flow Nasal Canula", "Room Air"], "ValueList" : ["1L O2 via NC", "2L O2 via NC", "3L O2 via NC", "4L O2 via NC", "5L O2 via NC", "6L O2 via NC", "50%% Venturi mask", "50%% non-rebreather", "20L High Flow Nasal Canula", "30L High Flow Nasal Canula", "40L High Flow Nasal Canula", "Room Air"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaCurrentCPAPOption": { "ButtonLabelList" : ["CPAP night", "BiPAP night"], "ValueList" : ["On home CPAP at night", "On home BiPAP at night"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaO2VBGOption": { "ButtonLabelList" : ["Latest VBG"], "ValueList" : ["Latest VBG="], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},

    ///////////////////
    // Workup
    "AsthmaXrayOption": { "ButtonLabelList" : ["Get Xray"], "ValueList" : ["Get Chest XRay"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaGetABGOption": { "ButtonLabelList" : ["Get ABG"], "ValueList" : ["Check ABG (consider intubation if ABG has pH below 7.2, CO2 over 55 to 70mm Hg, or O2 below 60mm Hg)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},

    "AsthmaGetCBCOption": { "ButtonLabelList" : ["Get CBC"], "ValueList" : ["CBC with diff to measure Eosinophil level"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaGetRVPOption": { "ButtonLabelList" : ["Get RVP"], "ValueList" : ["Influenza screen and Respiratory Viral Panel"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaCultureSputOption": { "ButtonLabelList" : ["Culture Sput"], "ValueList" : ["sputum culture"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaCultureBloodOption": { "ButtonLabelList" : ["Culture Blood"], "ValueList" : ["blood cultures"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaUrineAntigensOption": { "ButtonLabelList" : ["Urine Antigens"], "ValueList" : ["urine antigens for legionella, strep pneumo"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaProcalOption": { "ButtonLabelList" : ["Procal"], "ValueList" : ["ProCalcitonin to possibly rule out bacterial infection"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},

    ///////////////////
    // Bronchodilators
    "AsthmaNebsOption": { "ButtonLabelList" : ["Nebs"], "ValueList" : ["Rapid-Acting Bronchodilators: Albuterol nebs PRN Q2h"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaHFAOption": { "ButtonLabelList" : ["HFA"], "ValueList" : ["Rapid-Acting Bronchodilators: Albuterol HFA inhaler Q4h"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaLABAOption": { "ButtonLabelList" : ["LABA PRN", "LABA Sched"], "ValueList" : ["Long-Acting Bronchodilators: Mometasone/Formoterol PRN", "Long-Acting Bronchodilators: Mometasone/Formoterol Scheduled"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaLAMAOOption": { "ButtonLabelList" : ["LAMA"], "ValueList" : ["Long-Acting Anti-muscarinic: Tiotropium daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},


    ///////////////////
    // AntiInflammatory
    "AsthmaPrednisoneOption": { "ButtonLabelList" : ["Prednisone", "Methylpred"], "ValueList" : ["Systemic Steroids: Prednisone 40mg PO x5 days", "Systemic Steroids: Methylprednisolone 80mg IV Q12h"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaPPIOption": { "ButtonLabelList" : ["PPI"], "ValueList" : ["Pantoprazole while on steroids"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaH1BlockerOption": { "ButtonLabelList" : ["Cetirizine", "Loratadine", "Fexofenadine"], "ValueList" : ["H1 blocker: Cetirizine (Zyrtec)", "H1 blocker: Loratadine (Claritin)", "H1 blocker: Fexofenadine (Allegra)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaH2BlockerOption": { "ButtonLabelList" : ["Famotidine", "Ranitidine"], "ValueList" : ["H2 blocker: Famotidine (Pepcid)", "H2 blocker: Ranitidine (Zantac)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaMagnesiumOption": { "ButtonLabelList" : ["Magnesium"], "ValueList" : ["Magnesium 2g IV"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},


    ///////////////////
    // Oxygen
    "AsthmaCPAPOption": { "ButtonLabelList" : ["CPAP", "CPAP Night"], "ValueList" : ["CPAP for 4hrs then reassess", "CPAP at night"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaGiveO2Option": { "ButtonLabelList" : ["Oxygen"], "ValueList" : ["Supplemental oxygen. Titrate O2 for SpO2 between 89 and 92%"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaGuaifenesinOption": { "ButtonLabelList" : ["Guaifenesin"], "ValueList" : ["Guaifenesin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},
    "AsthmaPneumovaxOption": { "ButtonLabelList" : ["Pneumovax"], "ValueList" : ["If this is an exacerbation, then give a Pneumonia vaccine before discharge"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "AsthmaPlan"},




    ///////////////////////////////////////////////////////////
    // RenalTransplant CONTROLS
    ///////////////////////////////////////////////////////////

    ///////////////////
    // History
    "RenalTransplantTypeOption": { "ButtonLabelList" : ["DDKT", "LDKT"], "ValueList" : ["Deceased Donor Kidney Transplant", "Living Donor Kidney Transplant"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "RenalTransplantPlan"},
    "RenalTransplantDateOption": { "ButtonLabelList" : ["Year"], "ValueList" : ["Transplanted in "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "RenalTransplantPlan"},
    "RenalTransplantNephrologistOption": { "ButtonLabelList" : ["Nephrologist"], "ValueList" : ["Outpatient transplant nephrologist is "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "RenalTransplantPlan"},
    "RenalTransplantBaselineCrOption": { "ButtonLabelList" : ["Baseline Cr"], "ValueList" : ["Baseline Cr = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "RenalTransplantPlan"},
    "RenalTransplantRecentTacLevelOption": { "ButtonLabelList" : ["Recent Tac Lvl"], "ValueList" : ["Recent Tacrolimus Level Cr = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "RenalTransplantPlan"},


    ///////////////////
    // Home IS
    "RenalTransplantTacroOption": { "ButtonLabelList" : ["Tacro 1/1", "Tacro 2/1", "Tacro 2/2", "Tacro 3/2", "Tacro 3/3", "Tacro 4/3", "Tacro 4/4"], "ValueList" : ["Tacrolimus 1mg PO QAM, 1mg PO QAM", "Tacrolimus 2mg PO QAM, 1mg PO QAM", "Tacrolimus 2mg PO QAM, 2mg PO QAM", "Tacrolimus 3mg PO QAM, 2mg PO QAM", "Tacrolimus 3mg PO QAM, 3mg PO QAM", "Tacrolimus 4mg PO QAM, 3mg PO QAM", "Tacrolimus 4mg PO QAM, 4mg PO QAM"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "RenalTransplantPlan"},
    "RenalTransplantMMFOption": { "ButtonLabelList" : ["MMF 500", "MMF 1000", "MMF 1500"], "ValueList" : ["MMF 500mg PO BID", "MMF 1000mg PO BID", "MMF 1500mg PO BID"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "RenalTransplantPlan"},
    "RenalTransplantAzathioprineOption": { "ButtonLabelList" : ["Aza"], "ValueList" : ["Azathioprine 50mg PO daily"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "RenalTransplantPlan"},
    "RenalTransplantPrednisoneOption": { "ButtonLabelList" : ["Pred 5", "Pred 10"], "ValueList" : ["Prednisone 5mg PO daily", "Prednisone 10mg PO daily"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "RenalTransplantPlan"},

    ///////////////////
    // Home IS
    "RenalTransplantIPTacroOption": { "ButtonLabelList" : ["Tacro 1/1", "Tacro 2/1", "Tacro 2/2", "Tacro 3/2", "Tacro 3/3", "Tacro 4/3", "Tacro 4/4", "Hold"], "ValueList" : ["Tacrolimus 1mg PO QAM, 1mg PO QAM", "Tacrolimus 2mg PO QAM, 1mg PO QAM", "Tacrolimus 2mg PO QAM, 2mg PO QAM", "Tacrolimus 3mg PO QAM, 2mg PO QAM", "Tacrolimus 3mg PO QAM, 3mg PO QAM", "Tacrolimus 4mg PO QAM, 3mg PO QAM", "Tacrolimus 4mg PO QAM, 4mg PO QAM", "Hold Tacrolimus"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "RenalTransplantPlan"},
    "RenalTransplantIPMMFOption": { "ButtonLabelList" : ["MMF 500", "MMF 1000", "MMF 1500", "Hold"], "ValueList" : ["MMF 500mg PO BID", "MMF 1000mg PO BID", "MMF 1500mg PO BID", "Hold MMF"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "RenalTransplantPlan"},
    "RenalTransplantIPAzathioprineOption": { "ButtonLabelList" : ["Aza", "Hold"], "ValueList" : ["Azathioprine 50mg PO daily", "Hold Azathioprine"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "RenalTransplantPlan"},
    "RenalTransplantIPPrednisoneOption": { "ButtonLabelList" : ["Pred 5", "Pred 10", "Hold"], "ValueList" : ["Prednisone 5mg PO daily", "Prednisone 10mg PO daily", "Hold Prednisone"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "RenalTransplantPlan"},

    ///////////////////
    // Monitor
    "RenalTransplantCheckTacLevelOption": { "ButtonLabelList" : ["Check Tac Level"], "ValueList" : ["Check Tacrolimus level daily"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "RenalTransplantPlan"},

    ///////////////////
    // AKI
    "RenalTransplantCheckDSAOption": { "ButtonLabelList" : ["Check DSA"], "ValueList" : ["Check Donor-Specific Antibodies"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "RenalTransplantPlan"},
    "RenalTransplantTransplantUSOption": { "ButtonLabelList" : ["Transplant US"], "ValueList" : ["Check transplant Ultrasound (mild hydro is usually normal"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "RenalTransplantPlan"},
    "RenalTransplantCheckCMVOption": { "ButtonLabelList" : ["Check CMV"], "ValueList" : ["Check CMV viral load"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "RenalTransplantPlan"},
    "RenalTransplantCheckEBVOption": { "ButtonLabelList" : ["Check EBV"], "ValueList" : ["Check EBV viral load"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "RenalTransplantPlan"},
    "RenalTransplantCheckBKOption": { "ButtonLabelList" : ["Check BK"], "ValueList" : ["Check BK Virus"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "RenalTransplantPlan"},




    ///////////////////////////////////////////////////////////
    // Nephrolithiasis
    ///////////////////////////////////////////////////////////
    // History
    "NephrolithiasisShowLatestStoneOption" : { "ButtonLabelList" : ["Latest Stone"], "ValueList" : ["Most recent stone was" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},
    "NephrolithiasisRateOption" : { "ButtonLabelList" : ["Rate Monthly", "Rate per Year", "Rate in years", "Stones per life"], "ValueList" : ["The patient has stones every month", "The patient has xxx stones per year", "The patient has one stone every xxx years", "The patient has had xxxx stones total"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},
    "NephrolithiasisStoneTypeOption" : { "ButtonLabelList" : ["Unknown Type", "Ca-Oxalate", "Ca-Phos", "Urate", "Ammonium-Phos"], "ValueList" : ["unknown type", "Ca-Oxalate", "Ca-Phos", "Urate", "Ammonium-Phos"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},

    // Urine labs
    "NephrolithiasisShowUrinepHOption" : { "ButtonLabelList" : ["Show UpH"], "ValueList" : ["Urine pH = xxxx - should be between 5.5 and 7.0" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},
    "NephrolithiasisShowUrineSedimentOption" : { "ButtonLabelList" : ["No Crystals", "Ca-Oxalate", "Ca-Phos", "Urate", "Ammonium-Phos", "Bactrim", "Acyclovir", "Methotraxate"], "ValueList" : ["On personal examination of the urine sediment, there were No crystals", "On personal examination of the urine sediment, there were Ca-Oxalate crystals (rods and envelopes)", "On personal examination of the urine sediment, there were Ca-Phos crystals (needles and stars)", "On personal examination of the urine sediment, there were Urate crystals (flattened football)", "On personal examination of the urine sediment, there were Ammonium-Phos crystals (Coffin-lid)", "On personal examination of the urine sediment, there were Bactrim crystals (star-shaped)", "On personal examination of the urine sediment, there were Acyclovir crystals (needle)", "On personal examination of the urine sediment, there were Methotraxate crystals (brown cuboid)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},

    // 24hr Labs
    "Nephrolithiasis24hrUrineVolumeOption" : { "ButtonLabelList" : ["24hr Vol"], "ValueList" : ["volume xxx mL/day - should be MORE than 2000 mL/day" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},
    "Nephrolithiasis24hrUrineCalciumOption" : { "ButtonLabelList" : ["24hr Cal"], "ValueList" : ["Calcium xxx mg/day - should be LESS than 200 mg/day in women, 250 in men" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},
    "Nephrolithiasis24hrUrineCitrateOption" : { "ButtonLabelList" : ["24hr Citrate"], "ValueList" : ["Citrate - pending - should be MORE than 450 mg/day"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},
    "Nephrolithiasis24hrUrinePhosOption" : { "ButtonLabelList" : ["24hr Phos"], "ValueList" : ["Phos - pending - should be LESS than 1100 mg/day" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},
    "Nephrolithiasis24hrUrineSodiumOption" : { "ButtonLabelList" : ["24hr Sodium"], "ValueList" : ["Sodium xxx mg/day - should be LESS than 2000 mg/day, but lower is always better" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},
    "Nephrolithiasis24hrUrineChlorideOption" : { "ButtonLabelList" : ["24hr Chloride"], "ValueList" : ["Chloride xxx mg/day - should be LESS than 200 mEq/day" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},
    "Nephrolithiasis24hrUrineUrateOption" : { "ButtonLabelList" : ["24hr Urate"], "ValueList" : ["Uric Acid - pending - should be LESS than 750 mg/day in women and 800 mg/day in men" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},
    "Nephrolithiasis24hrUrineOxalateOption" : { "ButtonLabelList" : ["24hr Oxalate"], "ValueList" : ["Oxalate - pending - should be LESS than 40 mg/day" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},
    "Nephrolithiasis24hrUrineSulfateOption" : { "ButtonLabelList" : ["24hr Sulfate"], "ValueList" : ["Sulfate - pending - should be LESS than 30 mmol/day" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},

    // Workup
    "NephrolithiasisGetUAOption" : { "ButtonLabelList" : ["Get UA"], "ValueList" : ["Check Urinalysis" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},
    "NephrolithiasisGet24hrOption" : { "ButtonLabelList" : ["Get 24hr"], "ValueList" : ["Collect 24hour urine for Creatinine, Sodium, Calcium, Phos, Oxalate, Citrate, Chloride" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},
    "NephrolithiasisGetUSOption" : { "ButtonLabelList" : ["Renal US"], "ValueList" : ["Get Renal US" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},
    "NephrolithiasisGetCTOption" : { "ButtonLabelList" : ["Get 24hr"], "ValueList" : ["Get CT Stone Protocol" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},
    // Treat
    "NephrolithiasisLowNaDietOption" : { "ButtonLabelList" : ["Low Na diet"], "ValueList" : ["Low Na diet" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},
    "Nephrolithiasis2LPOFluidOption" : { "ButtonLabelList" : ["2L PO fluid"], "ValueList" : ["Increase PO water intake to maintain 2 liters urine daily" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},
    "NephrolithiasisKCitrateOption" : { "ButtonLabelList" : ["K-citrate"], "ValueList" : ["K-citrate (polycitra-K 5mL) tid" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},
    "NephrolithiasisThiazideOption" : { "ButtonLabelList" : ["Thiazide"], "ValueList" : ["Hydrochlorothiazide (increase Ca reabsorption in DCT and reduce calciuria" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},
    "NephrolithiasisFollowupRenalOption" : { "ButtonLabelList" : ["Renal Clinic"], "ValueList" : ["Followup with Renal clinic on discharge" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephrolithiasisPlan"},



    ///////////////////////////////////////////////////////////
    // Nephrotic
    ///////////////////////////////////////////////////////////
    "NephroticSyndromeOption" : { "ButtonLabelList" : ["Syndrome", "Proteinuria"], "ValueList" : ["Nephrotic Syndrome", "Nephrotic Proteinuria"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticShowUrineProtCreatRatioOption" : { "ButtonLabelList" : ["Show UPCR"], "ValueList" : ["Urine Random Protein-Creatinine ratio ="], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticShowUrineAlbCreatRatioOption" : { "ButtonLabelList" : ["Show UACR"], "ValueList" : ["Urine Random Albumin-Creatinine ratio ="], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticShowSerumAlbuminOption" : { "ButtonLabelList" : ["Show S-Albumin"], "ValueList" : ["Serum Albumin="], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticExplainRatioOption" : { "ButtonLabelList" : ["Explain Ratio"], "ValueList" : ["A patient typically produces around 1.0 grams of daily urine creatinine from normal muscle breakdown, so the protein/creatinine ratio is also an estimate of the daily urine proteinuria in grams. Proteinuria over 3.5 g/day is nephrotic."], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},

    // Etiology
    "NephroticDiffDiabetesOption" : { "ButtonLabelList" : ["Diabetes"], "ValueList" : ["Diabetes"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticDiffSLEOption" : { "ButtonLabelList" : ["SLE"], "ValueList" : ["Lupus Nephritis"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticDiffHepBOption" : { "ButtonLabelList" : ["Hep B"], "ValueList" : ["Hep B"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticDiffHepCOption" : { "ButtonLabelList" : ["Hep C"], "ValueList" : ["Hep C"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticDiffHIVOption" : { "ButtonLabelList" : ["HIV"], "ValueList" : ["HIV"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticDiffAmyloidosis" : { "ButtonLabelList" : ["Amyloidosis"], "ValueList" : ["Amyloidosis"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticDiffPreeclampsiaOption" : { "ButtonLabelList" : ["Preeclampsia"], "ValueList" : ["Preeclampsia"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticDiffFSGSOption" : { "ButtonLabelList" : ["FSGS"], "ValueList" : ["Focal Segmental glomerulosclerosis"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticDiffMembranousOption" : { "ButtonLabelList" : ["Membranous"], "ValueList" : ["Membranous nephropathy"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticDiffMinimalChangeOption" : { "ButtonLabelList" : ["Minimal change"], "ValueList" : ["Minimal change nephropathy"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticDiffNSAIDsOption" : { "ButtonLabelList" : ["NSAIDs"], "ValueList" : ["NSAIDs"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticDiffTamoxifenOption" : { "ButtonLabelList" : ["Tamoxifen"], "ValueList" : ["Tamoxifen"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticDiffLithiumOption" : { "ButtonLabelList" : ["Lithium"], "ValueList" : ["Lithium"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},


    // Work up
    "NephroticWorkupA1cOption" : { "ButtonLabelList" : ["A1c"], "ValueList" : ["A1c"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticWorkupLightChainsOption" : { "ButtonLabelList" : ["Light Chains"], "ValueList" : ["serum and urine free light chains (kappa and lambda)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticWorkupSPEPOption" : { "ButtonLabelList" : ["SPEP"], "ValueList" : ["SPEP and UPEP"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticWorkupRheumatoidFactorOption" : { "ButtonLabelList" : ["RF"], "ValueList" : ["Rheumatoid Factor to rule out cryoglobulinemia"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticWorkupCryoglobulinsOption" : { "ButtonLabelList" : ["Cryos"], "ValueList" : ["Cryoglobulins to rule out cryoglobulinemia"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticWorkupANAOption" : { "ButtonLabelList" : ["ANA"], "ValueList" : ["ANA"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticWorkupC3C4Option" : { "ButtonLabelList" : ["C3 and C4"], "ValueList" : ["C3 and C4 complement levels"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticWorkupAntiGBMOption" : { "ButtonLabelList" : ["anti-GBM"], "ValueList" : ["anti-GBM antibody"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticWorkupPLA2ROption" : { "ButtonLabelList" : ["PLA2R"], "ValueList" : ["PLA2R antibody (70% sensitive in Ideopathic Membranous GN but may also present in secondary)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticWorkupHIVOption" : { "ButtonLabelList" : ["HIV"], "ValueList" : ["HIV Screen"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticWorkupHepBOption" : { "ButtonLabelList" : ["Hep B"], "ValueList" : ["Hepatitis B"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticWorkupHepCOption" : { "ButtonLabelList" : ["Hep C"], "ValueList" : ["Hepatitis C antibodies"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticWorkupSyphilisOption" : { "ButtonLabelList" : ["Syphilis"], "ValueList" : ["Syphilis screen"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},

    // Treat
    "NephroticTreatLasixPOOption": { "ButtonLabelList" : ["Lasix 20PO", "Lasix 20POBID", "Lasix 40PO", "Lasix 40POBID", "Lasix 80PO", "Lasix 80POBID"], "ValueList" : ["Furosemide 20mg PO daily at breakfast", "Furosemide 20mg PO BID", "Furosemide 40mg PO daily at breakfast", "Furosemide 40mg PO BID", "Furosemide 80mg PO daily at breakfast", "Furosemide 80mg PO BID"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticTreatACEOption" : { "ButtonLabelList" : ["Lisinopril"], "ValueList" : ["Start Lisinopril"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticTreatAnticoagulationOption" : { "ButtonLabelList" : ["Anticoag"], "ValueList" : ["Start anticoagulation, Coumadin with target INR 2-3"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticTreatCriteriaAnticoagulationOption" : { "ButtonLabelList" : ["AnticoagCriteria"], "ValueList" : ["Start Anticoagulation if Albumin below 2.0 (target INR 2-3) and any of following: proteinuria over 10g/day, BMI over 35, NYHA 3 or 4 or prolonged immobilization (see KDIGO 2012 Guidelines on GN). Thromboembolism is most common with membranous nephropathy, and there is less data for thrombosis with other forms of nephrotic proteinuria in DM but if albumin is persistently below 1.5 we have to consider anticoagulation"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticTreatExplainACEOption" : { "ButtonLabelList" : ["Explain ACE"], "ValueList" : ["(an ACEi increases chance of spontaneous remission, and will reduce proteinuria, which is inflammatory, and so it protects renal function)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticTreatCancerScreenOption" : { "ButtonLabelList" : ["Cancer Screen"], "ValueList" : ["Age-appropriate cancer screening (membranous is often secondary to malignancy)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticTreatCheckTSHOption" : { "ButtonLabelList" : ["Check TSH"], "ValueList" : ["TSH and Vitamin D (binding proteins are lost in proteinuria)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},
    "NephroticTreatCheckLDLOption" : { "ButtonLabelList" : ["Check LDL"], "ValueList" : ["LDL"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "NephroticPlan"},



    ///////////////////////////////////////////////////////////
    // Obesity
    ///////////////////////////////////////////////////////////
    "ObesityClassOption" : { "ButtonLabelList" : ["Class 1", "Class 2", "Class 3"], "ValueList" : ["Obesity, class 1 (BMI 30-35)", "Obesity, class 2 (BMI 35-40)", "Obesity, class 3 (BMI over 40)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "ObesityPlan"},

    "ObesityShowBMIOption" : { "ButtonLabelList" : ["Show BMI"], "ValueList" : ["BMI = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "ObesityPlan"},
    "ObesityComplicatesOption" : { "ButtonLabelList" : ["Complicates"], "ValueList" : ["This complicates care"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "ObesityPlan"},
    "ObesityNoMRIOption" : { "ButtonLabelList" : ["No MRI"], "ValueList" : ["This prevents MRI (max weight 205kg)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "ObesityPlan"},
    "NoCTOption" : { "ButtonLabelList" : ["No CT"], "ValueList" : ["This prevents CT (max weight 300kg)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "ObesityPlan"},
    "ObesityNoIROption" : { "ButtonLabelList" : ["No IR"], "ValueList" : ["This prevents CT (max weight 225kg)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "ObesityPlan"},

    "ObesityConsultNutritionOption" : { "ButtonLabelList" : ["Consult Nutrition"], "ValueList" : ["Consult Nutrition"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "ObesityPlan"},
    "ObesityBariatricBedOption" : { "ButtonLabelList" : ["Bariatric Bed"], "ValueList" : ["Bariatric Bed"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "ObesityPlan"},

    "ObesityScreenLipidsOption" : { "ButtonLabelList" : ["Lipids"], "ValueList" : ["Check fasting lipid panel and LDL Direct"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "ObesityPlan"},
    "ObesityCheckA1cOption" : { "ButtonLabelList" : ["A1c"], "ValueList" : ["Check HgbA1c"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "ObesityPlan"},


    ///////////////////////////////////////////////////////////
    // Tobacco
    ///////////////////////////////////////////////////////////
    "TobaccoPacksPerDayOption" : { "ButtonLabelList" : ["1ppd", "0.5ppd", "2ppd"], "ValueList" : ["Currently smokes 1ppd", "Currently smokes 0.5ppd", "Currently smokes 2ppd"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "TobaccoPlan"},
    "TobaccoStartedSmokingOption" : { "ButtonLabelList" : ["Start Age"], "ValueList" : ["Started smoking at xxx years old"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "TobaccoPlan"},
    "TobaccoCounseledCessationOption" : { "ButtonLabelList" : ["Counsel"], "ValueList" : ["Counseled cessation"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "TobaccoPlan"},
    "TobaccoNicotinePatchOption" : { "ButtonLabelList" : ["Patch"], "ValueList" : ["Patch"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "TobaccoPlan"},
    "TobaccoNicotineGumOption" : { "ButtonLabelList" : ["Gum"], "ValueList" : ["Gum"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "TobaccoPlan"},
    "TobaccoDeclinesNicotineReplacementOption" : { "ButtonLabelList" : ["Declines"], "ValueList" : ["The patient declines nicotine replacement"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "TobaccoPlan"},
    "TobaccoLatestChestCTOption" : { "ButtonLabelList" : ["Last CT"], "ValueList" : ["Last CT Chest was in "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "TobaccoPlan"},
    "TobaccoScreenCTOption" : { "ButtonLabelList" : ["Screen CT"], "ValueList" : ["Low Power Chest CT for lung cancer screen"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "TobaccoPlan"},



    ///////////////////////////////////////////////////////////
    // Alcohol
    ///////////////////////////////////////////////////////////
    "EtOHWithdrawalsModifier" : { "ButtonLabelList" : ["Withdrawals"], "ValueList" : ["Alcohol Dependance with Withdrawals"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EtOHPlan"},
    "EtOHDailyUseOption" : { "ButtonLabelList" : ["Daily use", "6 beers", "12 beers", "18 beers", "24 beers", "One Pint", "Two Pint", "One Fifth"], "ValueList" : ["Drinks daily", "Drinks 6 beers daily", "Drinks 12 beers daily", "Drinks 18 beers daily", "Drinks 24 beers daily", "Drinks one pint liquor daily", "Drinks two pints liquor daily", "Drinks one Fifth liquor daily"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EtOHPlan"},
    "EtOHLastUseOption" : { "ButtonLabelList" : ["Last Drink"], "ValueList" : ["last drink was xxxxx"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EtOHPlan"},
    "EtOHPastSeizuresOption" : { "ButtonLabelList" : ["Seizures"], "ValueList" : [" with seizures"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EtOHPlan"},
    "EtOHPastWithdrawalsOption" : { "ButtonLabelList" : ["Withdrawals"], "ValueList" : ["Past history of DT withdrawals"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EtOHPlan"},
    "EtOHCIWAOption" : { "ButtonLabelList" : ["CIWA"], "ValueList" : ["PRN Lorazepam per CIWA protocol"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EtOHPlan"},
    "EtOHThiamineOption" : { "ButtonLabelList" : ["Thiamine"], "ValueList" : ["Thiamine 100mg daily"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EtOHPlan"},
    "EtOHVitaminsOption" : { "ButtonLabelList" : ["Vitamin"], "ValueList" : ["Prenatal vitamin (with Folate) daily"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EtOHPlan"},
    //WriteAction("Consider Baclofen to reduce EtOH craving (5mg PO TID x3 days, then 10mg PO TID daily)");
    //Chlorthiazepoxide
    "EtOHAABookOption" : { "ButtonLabelList" : ["AA Book"], "ValueList" : ["I have counselled cessation and provided the patient with the Alcoholics Anonymous book (the Big Book)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EtOHPlan"},



    ///////////////////////////////////////////////////////////
    // Malnutrition
    ///////////////////////////////////////////////////////////
    "MalnutritionMalnutritionOption" : { "ButtonLabelList" : ["Malnutrition"], "ValueList" : ["Calorie and Protein Malnutrition (Present on admission)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MalnutritionPlan"},
    "MalnutritionUnderweightOption" : { "ButtonLabelList" : ["Underweight"], "ValueList" : ["Underweight (Present on Admission)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MalnutritionPlan"},
    "MalnutritionWtLossOption" : { "ButtonLabelList" : ["Wt Loss"], "ValueList" : ["Chronic illness weight loss (Present on Admission)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MalnutritionPlan"},
    "MalnutritionFatLossOption" : { "ButtonLabelList" : ["Fat Loss"], "ValueList" : ["Subcutaneous fat loss and muscle loss (Present on Admission)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MalnutritionPlan"},
    "MalnutritionShowBMIOption" : { "ButtonLabelList" : ["Show BMI"], "ValueList" : ["On admission, BMI = xxx"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MalnutritionPlan"},
    "MalnutritionShowPrealbuminOption" : { "ButtonLabelList" : ["Show Prealbumin"], "ValueList" : ["Prealbumin = xxxx"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MalnutritionPlan"},
    "MalnutritionComplicatesCareOption" : { "ButtonLabelList" : ["Complicates care"], "ValueList" : ["This complicates all aspects of care"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MalnutritionPlan"},
    "MalnutritionNutritionConsultOption" : { "ButtonLabelList" : ["Nutrition consult"], "ValueList" : ["Nutrition consult"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MalnutritionPlan"},
    "MalnutritionSupplementsOption" : { "ButtonLabelList" : ["Supplements"], "ValueList" : ["Nutrition supplements with all meals (Boost drink and pudding)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MalnutritionPlan"},
    "MalnutritionMultivitaminOption" : { "ButtonLabelList" : ["Multivitamin"], "ValueList" : ["Replace water soluble vitamins (vitamins B and C)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MalnutritionPlan"},
    "MalnutritionDronabinolOption" : { "ButtonLabelList" : ["Dronabinol"], "ValueList" : ["Dronabinol"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MalnutritionPlan"},



    ///////////////////////////////////////////////////////////
    // Weakness
    ///////////////////////////////////////////////////////////
   "WeaknessWeaknessOption" : { "ButtonLabelList" : ["Weakness"], "ValueList" : ["Weakness"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
   "WeaknessMyopathyOption" : { "ButtonLabelList" : ["Crit Illness"], "ValueList" : ["Critical Illness Myopathy"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
   "WeaknessFallsOption" : { "ButtonLabelList" : ["Falls"], "ValueList" : ["Gait instability with falls"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessReducedMobilityOption" : { "ButtonLabelList" : ["Mobility"], "ValueList" : ["Reduced Mobility"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessDebilityOption" : { "ButtonLabelList" : ["Debility"], "ValueList" : ["Debility"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},

    "WeaknessCFSScoreScaleOption" : { "ButtonLabelList" : ["Very Fit", "Fit", "Managing", "Very Mild Frailty", "Mild Frailty", "Moderate Frailty", "Dependence in ADLs", "Bed-ridden", "Terminally Ill"], "ValueList" : ["Clinical Frailty Scale Level 1 - Very Fit - daily vigorous activity. This may include patients on chronic BP meds", "Clinical Frailty Scale Level 2 - Fit - less frequent or less vigorous activity", "Clinical Frailty Scale Level 3 - Managing Well. less frequent or less vigorous activity but some medical symptoms although these do not limit activity.", "Clinical Frailty Scale Level 4 – Living with Very Mild Frailty. Some symptoms with activity, such as fatigue. Incomplete symptom control. May require help with heavy housework, or difficulty climbing stairs.", "Clinical Frailty Scale Level 5 – Living with Mild Frailty. Does not attempt heavy housework or climbing stairs", "Clinical Frailty Scale Level 6 – Living with Moderate Frailty, dependence now extends past instrumental ADLs to intermediate ones, notably including dependence in bathing", "Clinical Frailty Scale Level 7 – Living with Severe Frailty. Dependence in some ADLs.", "Clinical Frailty Scale Level 8 – Living with Very Severe Frailty. Bed-ridden for periods, such as acute illness.", "Clinical Frailty Scale Level 9 – Terminally Ill. Independant of activity status"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessFRAILScaleFatigueOption" : { "ButtonLabelList" : ["Always Tired", "Not Tired"], "ValueList" : ["Fatigue most or all of the time", "Fatigue some or less of the time"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessFRAILScaleResistanceOption" : { "ButtonLabelList" : ["10 Stairs", "Cant do stairs"], "ValueList" : ["No difficulty walking up 10 steps without resting", "Difficulty walking up 10 steps without resting"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessFRAILScaleWalk100YdsOption" : { "ButtonLabelList" : ["Walk 100yds", "Cant walk 100yds"], "ValueList" : ["No difficulty walking several hundred yards", "Difficulty walking several hundred yards"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessFRAILScaleChronicIllnessOption" : { "ButtonLabelList" : ["Chronic Illness", "Fewer 5 Illnesses"], "ValueList" : ["Fewer than 5 chronic illnesses", "5 or more chronic illnesses"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessFRAILScaleWtLossOption" : { "ButtonLabelList" : ["Wt Loss", "No Sig Wt Loss"], "ValueList" : ["No significant weight loss in past year", "Lost more than five percent of weight in past year"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},

    "WeaknessEtiologyOrthostatic" : { "ButtonLabelList" : ["Orthostatic"], "ValueList" : ["orthostatic hypotension"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessEtiologyNeuropathy" : { "ButtonLabelList" : ["Neuropathy"], "ValueList" : ["diabetic neuropathy"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessEtiologyVision" : { "ButtonLabelList" : ["Vision"], "ValueList" : ["reduced vision"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessEtiologyAMS" : { "ButtonLabelList" : ["AMS"], "ValueList" : ["chronic encephalopathy"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessEtiologyMeds" : { "ButtonLabelList" : ["Meds"], "ValueList" : ["medications"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},

    "WeaknessCheckOrthostaticsOption" : { "ButtonLabelList" : ["Orthostatics"], "ValueList" : ["orthostatics"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessCheckHeadCTOption" : { "ButtonLabelList" : ["Head CT"], "ValueList" : ["Head CT"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessCheckCTSpineOption" : { "ButtonLabelList" : ["CT Spine"], "ValueList" : ["CT Spine"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessCheckABIOption" : { "ButtonLabelList" : ["ABI"], "ValueList" : ["ABIs (for claudication)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessCheckEKGOption" : { "ButtonLabelList" : ["EKG"], "ValueList" : ["EKG (for arrhythmia)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessCheckKOption" : { "ButtonLabelList" : ["Potassium"], "ValueList" : ["Potassium"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessCheckVitDOption" : { "ButtonLabelList" : ["VitD"], "ValueList" : ["VitD"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessCheckB12Option" : { "ButtonLabelList" : ["B12"], "ValueList" : ["B12"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessCheckThiamineOption" : { "ButtonLabelList" : ["Thiamine"], "ValueList" : ["Thiamine"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessCheckCPKOption" : { "ButtonLabelList" : ["CPK"], "ValueList" : ["CPK"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessCheckTSHOption" : { "ButtonLabelList" : ["TSH"], "ValueList" : ["TSH and free T4"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},

    // Hold sedating meds
    "Weakness_HOLD_OPIOIDS_OPTION" : { "ButtonLabelList" : ["Opioids"], "ValueList" : ["Opioids"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "Weakness_HOLD_BENZOS_OPTION" : { "ButtonLabelList" : ["Benzos"], "ValueList" : ["Benzodiazepines"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "Weakness_HOLD_BETA_BLOCKERS_OPTION" : { "ButtonLabelList" : ["Beta Blockers"], "ValueList" : ["Beta Blockers"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "Weakness_HOLD_ANTIHISTAMINES_OPTION" : { "ButtonLabelList" : ["Hydroxyzine"], "ValueList" : ["Hydroxyzine"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "Weakness_HOLD_PROMETHAZINE_OPTION" : { "ButtonLabelList" : ["Promethazine"], "ValueList" : ["Promethazine"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},

    "WeaknessIVFluids" : { "ButtonLabelList" : ["IV Fluids"], "ValueList" : ["IV Fluids"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessCholecal" : { "ButtonLabelList" : ["Cholecal"], "ValueList" : ["Cholecal 2000 IU PO daily"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessThiamine" : { "ButtonLabelList" : ["Thiamine"], "ValueList" : ["Thiamine 100mg PO daily"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessPTOption" : { "ButtonLabelList" : ["PT"], "ValueList" : ["Physical Therapy"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessPrecautionsOption" : { "ButtonLabelList" : ["Fall Precautions"], "ValueList" : ["Fall Precautions"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},
    "WeaknessUpInChairOption" : { "ButtonLabelList" : ["Up In Chair"], "ValueList" : ["Up In Chair TID"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "WeaknessPlan"},



    ///////////////////////////////////////////////////////////
    // LOW Potassium
    ///////////////////////////////////////////////////////////
    "LowPotassiumShowKOption" : { "ButtonLabelList" : ["Show K"], "ValueList" : ["Recent serum Potassium = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumShowMgOption" : { "ButtonLabelList" : ["Show Mg"], "ValueList" : ["Recent serum Magnesium = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumShowUrClOption" : { "ButtonLabelList" : ["Show Ur-Cl"], "ValueList" : ["Recent urine Chloride = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumShowTTKGOption" : { "ButtonLabelList" : ["Show TTKG"], "ValueList" : ["Urine Trans-tubular Potassium Gradient is "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumExplainLowTTKGOption" : { "ButtonLabelList" : ["ExplainLowTTKG", "ExplainHighTTKG"], "ValueList" : ["TTKG is below 3, so the kidneys are compensating and this is less likely nephrogenic", "TTKG is above 3, then the kidneys are not compensating and are wasting K, so this may be nephrogenic"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumShowFEKOption" : { "ButtonLabelList" : ["Show FEK"], "ValueList" : ["Fractional Excretion Potassium = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumExplainFEKGOption" : { "ButtonLabelList" : ["Explain FEK"], "ValueList" : ["Fractional Excretion of Potassium over 10 percent in hypokalemic patients suggests renal etiology (such as hyperAldo)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumInterpretUrClOption" : { "ButtonLabelList" : ["Ur-Cl is Low", "Ur-Cl is high"], "ValueList" : ["Urine chloride is below 25 in an alkalotic patient, so the kidneys are retaining volume, and so Aldo is high", "Urine chloride is above 25, so the kidneys are not retaining volume, and Aldo is unlikely high"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumExplainUrClOption" : { "ButtonLabelList" : ["Explain Ur-Cl"], "ValueList" : ["We look at Urine chloride because if a patient is alkalotic, then the kidneys will waste bicarb, as HCO3-, but this is an anion so to keep urine electrically neutral it wastes a cation, sodium, or NaHCO3. So, Na will be high in an alkalotic patient, so to assess volume status look at urine Cl. If the kidneys hold onto Na for retaining volume in response to high Aldo, then they also retain an anion Cl-. So urine Cl- tells us how much Na is being wasted for volume management independant of how much Na is being wasted for acid/base management"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumCausesDiarrheaOption" : { "ButtonLabelList" : ["Diarrhea"], "ValueList" : ["diarrhea"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumCausesRenalOption" : { "ButtonLabelList" : ["Renal"], "ValueList" : ["renal loss"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumCausesDiureticsOption" : { "ButtonLabelList" : ["Diuretics"], "ValueList" : ["diuretics"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumCausesLowMgOption" : { "ButtonLabelList" : ["Low Mg"], "ValueList" : ["low Mg"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumCausesHighAldoOption" : { "ButtonLabelList" : ["High Aldo"], "ValueList" : ["high Aldo"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumCausesHyperAaldoOption" : { "ButtonLabelList" : ["Primary Aldo"], "ValueList" : ["primary hyper-aldo"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumCausesRASOption" : { "ButtonLabelList" : ["RAS"], "ValueList" : ["renal artery stenosis"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumCausesMalnutritionOption" : { "ButtonLabelList" : ["Malnutrition"], "ValueList" : ["Malnutrition"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumCausesTubeFeedsOption" : { "ButtonLabelList" : ["Tube feeds"], "ValueList" : ["Low-K Tube feeds"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumCheckMgOption" : { "ButtonLabelList" : ["Check Mg"], "ValueList" : ["serum Mg"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumCheckUrChlorideOption" : { "ButtonLabelList" : ["Check Ur-Cl"], "ValueList" : ["urine Chloride"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumCheckULytesOption" : { "ButtonLabelList" : ["Check ULytes"], "ValueList" : ["urine K and Osm and serum Osm to compute KKTG"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumRepleteKOption" : { "ButtonLabelList" : ["Replete K"], "ValueList" : ["Monitor and replete Potassium"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},
    "LowPotassiumRepleteMgOption" : { "ButtonLabelList" : ["Replete Mg"], "ValueList" : ["Monitor and replete Magnesium"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypokalemiaPlan"},



    ///////////////////////////////////////////////////////////
    // High Potassium
    ///////////////////////////////////////////////////////////
    "HighPotassiumShowKOption" : { "ButtonLabelList" : ["Show K"], "ValueList" : ["Recent serum potassium = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyperkalemiaPlan"},
    "HighPotassiumShowEKGOption" : { "ButtonLabelList" : ["EKG Normal", "EKG Peaked"], "ValueList" : ["The EKG does not show signs of hyperkalemia", "The EKG shows peaked T-waves"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyperkalemiaPlan"},
    "HighPotassiumShowTTKGOption" : { "ButtonLabelList" : ["Show TTKG"], "ValueList" : ["Urine Trans-tubular Potassium Gradient is "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyperkalemiaPlan"},
    "HighPotassiumExplainLowTTKGOption" : { "ButtonLabelList" : ["ExplainLowTTKG", "ExplainHighTTKG"], "ValueList" : ["TTKG is below 10, so the kidneys are not compensating and this may be nephrogenic", "TTKG is above 10, then the kidneys are compensating and this is less likely nephrogenic"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyperkalemiaPlan"},
    "HighPotassiumShowFEKOption" : { "ButtonLabelList" : ["Show FEK"], "ValueList" : ["Fractional Excretion Potassium = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyperkalemiaPlan"},
    "HighPotassiumExplainFEKGOption" : { "ButtonLabelList" : ["Explain FEK"], "ValueList" : ["Fractional Excretion of Potassium below 6 percent in hyperkalemic patients suggests renal etiology (such as hypoAldo)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyperkalemiaPlan"},

    "HighPotassiumEtiologyRTA4Option" : { "ButtonLabelList" : ["RTA 4"], "ValueList" : ["RTA type 4 (hypo-Aldo)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyperkalemiaPlan"},
    "HighPotassiumEtiologySeizuresOption" : { "ButtonLabelList" : ["Seizures"], "ValueList" : ["seizures"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyperkalemiaPlan"},
    "HighPotassiumEtiologyTumorLysisOption" : { "ButtonLabelList" : ["Tumor Lysis"], "ValueList" : ["Tumor Lysis"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyperkalemiaPlan"},
    "HighPotassiumEtiologySaltSubstituteOption" : { "ButtonLabelList" : ["Salt-substitute"], "ValueList" : ["Salt-substitute (this is often Potassium Chloride)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyperkalemiaPlan"},
    "HighPotassiumEtiologyDigoxinOption" : { "ButtonLabelList" : ["Digoxin"], "ValueList" : ["Digoxin (inhibits Na/K-ATPase so leaves K outside the cell)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyperkalemiaPlan"},
    "HighPotassiumCheckEKGOption" : { "ButtonLabelList" : ["Check EKG"], "ValueList" : ["Check EKG"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyperkalemiaPlan"},
    "HighPotassiumCheckULytesOption" : { "ButtonLabelList" : ["Check ULytes"], "ValueList" : ["Check urine K and Osm and serum Osm to compute KKTG"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyperkalemiaPlan"},
    "HighPotassiumCaIVOption" : { "ButtonLabelList" : ["Ca IV"], "ValueList" : ["Calcium Gluconate 2g once"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyperkalemiaPlan"},
    "HighPotassiumBinderResinOption" : { "ButtonLabelList" : ["Zirconium", "Kayexalate", "Patiromer"], "ValueList" : ["Zirconium cyclosilicate (Lokelma) 10g PO BID. This removes potassium from the body, and takes effect in 1-6 hrs", "Sodium polystyrene sulfonate (Kayexalate). This removes potassium from the body, but is slow to take effect", "Patiromer (Veltassa) 16.8 g/day. This removes potassium from the body"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyperkalemiaPlan"},
    "HighPotassiumInsulinD50WOption" : { "ButtonLabelList" : ["Insulin/D50W", "Insulin/D10W"], "ValueList" : ["50mL D50W with 10u Regular Insulin, then follow with D10W at 70 mL/hr for the next several hours. This will only shift potassium intracellularly", "50mL D10W 250mL bolus, with 10u Regular Insulin, then follow with D10W 50mL/hr for 4 hours for the next several hours. This will only shift potassium intracellularly"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyperkalemiaPlan"},
    "HighPotassiumFurosemideOption" : { "ButtonLabelList" : ["Furosemide"], "ValueList" : ["Furosemide 40mg IV once"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyperkalemiaPlan"},
    "HighPotassiumBicarbonateOption" : { "ButtonLabelList" : ["Bicarbonate IV", "Bicarbonate PO"], "ValueList" : ["Sodium Bicarbonate IV at 100mL/hr- shift potassium into cells", "Sodium Bicarbonate 650mg PO TID - shift potassium into cells"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyperkalemiaPlan"},
    "HighPotassiumAlbuterolOption" : { "ButtonLabelList" : ["Albuterol"], "ValueList" : ["Albuterol - shift potassium into cells but at a very high dose. 10-20mg in 4mL solution (a typical asthma dose is 2.5mg)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HyperkalemiaPlan"},


    ///////////////////////////////////////////////////////////
    // High Sodium
    ///////////////////////////////////////////////////////////
    "HighNaExplainOption" : { "ButtonLabelList" : ["Explain"], "ValueList" : ["Hypernatremia is a deficiency of free water, not an excess of sodium, so the serum is over-concentrated"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERnatremiaPlan"},
    "HighNaShowNaOption" : { "ButtonLabelList" : ["Show Na"], "ValueList" : ["Current sodium = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERnatremiaPlan"},
    "HighNaFreeWaterDeficitOption" : { "ButtonLabelList" : ["Water Deficit"], "ValueList" : ["Free Water Deficit is "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERnatremiaPlan"},
    "HighNaShowUrineOsmOption" : { "ButtonLabelList" : ["Show U-Osm"], "ValueList" : ["Current urine Osm = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERnatremiaPlan"},
    "HighNaShowUrineNaOption" : { "ButtonLabelList" : ["Show U-Na"], "ValueList" : ["Current urine sodium = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERnatremiaPlan"},
    "HighNaCausesDiarreaOption" : { "ButtonLabelList" : ["Diarrea"], "ValueList" : ["Osmotic diarrea (loses free water)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERnatremiaPlan"},
    "HighNaCausesTPNOption" : { "ButtonLabelList" : ["TPN"], "ValueList" : ["Osmotic diuresis (TPN)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERnatremiaPlan"},
    "HighNaCausesBurnsOption" : { "ButtonLabelList" : ["Burns"], "ValueList" : ["Water loss (burns)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERnatremiaPlan"},
    "HighNaCausesLowIntakeOption" : { "ButtonLabelList" : ["Low intake"], "ValueList" : ["Insufficient water intake (tube feeds, low PO intake)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERnatremiaPlan"},
    "HighNaCausesPostATNOption" : { "ButtonLabelList" : ["Post ATN"], "ValueList" : ["Post ATN diuresis"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERnatremiaPlan"},
    "HighNaCausesLithiumOption" : { "ButtonLabelList" : ["Lithium"], "ValueList" : ["Diabetes Insipidis (Lithium)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERnatremiaPlan"},
    "HighNaCausesCisplatinOption" : { "ButtonLabelList" : ["Cisplatin"], "ValueList" : ["Diabetes Insipidis (Cisplatin)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERnatremiaPlan"},
    "HighNaGetUOsmOption" : { "ButtonLabelList" : ["Get UOsm"], "ValueList" : ["Measure Urine osmolality"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERnatremiaPlan"},
    "HighNaGetULytesOption" : { "ButtonLabelList" : ["Get ULytes"], "ValueList" : ["Measure Urine Na and K"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERnatremiaPlan"},
    "HighNaGiveD5WOption" : { "ButtonLabelList" : ["Give D5W"], "ValueList" : ["IV Free Water - D5W at 75 mL/hr for a total of xxx mL"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERnatremiaPlan"},
    "HighNaTubeFeedFreeWaterOption" : { "ButtonLabelList" : ["TF Water"], "ValueList" : ["Increase Free Water with tube feeds to xxxx mL every xxx hours"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERnatremiaPlan"},
    "HighNaDDAVPOption" : { "ButtonLabelList" : ["DDAVP"], "ValueList" : ["If this is due to DI (serum Na is high with Polyuria) then consider DDAVP 0.5mcg (Desmopressin, an ADH/Vasopressin analog)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERnatremiaPlan"},




    ///////////////////////////////////////////////////////////
    // LOW Mg
    ///////////////////////////////////////////////////////////
    "LowMgShowMgOption" : { "ButtonLabelList" : ["Show Mg"], "ValueList" : ["Mg = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypomagnesemiaPlan"},
    "LowMgCheckUrineOption" : { "ButtonLabelList" : ["Check Urine"], "ValueList" : ["Check urine Cr and Magnesium"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypomagnesemiaPlan"},
    "LowMgRepleteOption" : { "ButtonLabelList" : ["Replete"], "ValueList" : ["Monitor and replete"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypomagnesemiaPlan"},


    ///////////////////////////////////////////////////////////
    // Low Phos
    ///////////////////////////////////////////////////////////
    "LowPhosShowPhosOption" : { "ButtonLabelList" : ["Show Phos"], "ValueList" : ["Phos = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoPhosPlan"},
    "LowPhosShowCalciumOption" : { "ButtonLabelList" : ["Show Ca"], "ValueList" : ["Ca = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoPhosPlan"},
    "LowPhosShowPTHOption" : { "ButtonLabelList" : ["Show PTH"], "ValueList" : ["PTH = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoPhosPlan"},
    "LowPhosCheckUrineOption" : { "ButtonLabelList" : ["Check Urine"], "ValueList" : ["Check urine Phos and Cr"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoPhosPlan"},
    "LowPhosCheckPTHOption" : { "ButtonLabelList" : ["Check PTH"], "ValueList" : ["Check PTH"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoPhosPlan"},
    "LowPhosShowFEPhosOption" : { "ButtonLabelList" : ["Show FE-Phos"], "ValueList" : ["Fractional Excretion Phosphorus = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoPhosPlan"},
    "LowPhosExplainFEPhosOption" : { "ButtonLabelList" : ["Explain FE-Phos"], "ValueList" : ["Fractional Excretion of Phosphorus over 20 percent in hypophosphatemic patients suggests renal etiology"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoPhosPlan"},
    "LowPhosTreatIVOption" : { "ButtonLabelList" : ["IV Phos"], "ValueList" : ["NaPhos 12mmol x2 doses"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoPhosPlan"},
    "LowPhosTreatPOOption" : { "ButtonLabelList" : ["PO Phos"], "ValueList" : ["PhosNak 1 tab PO BID"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoPhosPlan"},
    "LowPhosRepleteOption" : { "ButtonLabelList" : ["Replete"], "ValueList" : ["Monitor and replete"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoPhosPlan"},
    "LowPhosFixCalOption" : { "ButtonLabelList" : ["Fix Ca"], "ValueList" : ["Treat elevated Calcium. Do not replete Phos because Phos is low due to chelation with Calcium"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoPhosPlan"},


    ///////////////////////////////////////////////////////////
    // Low Ca
    ///////////////////////////////////////////////////////////
    "LowCalciumShowCaOption" : { "ButtonLabelList" : ["Show Ca"], "ValueList" : ["Ca = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoCalcemiaPlan"},
    "LowCalciumShowiCalOption" : { "ButtonLabelList" : ["Show iCal"], "ValueList" : ["ionized Ca = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoCalcemiaPlan"},
    "LowCalciumShowVitDOption" : { "ButtonLabelList" : ["Show VitD"], "ValueList" : ["VitD = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoCalcemiaPlan"},
    "LowCalciumShowFECaOption" : { "ButtonLabelList" : ["Show FE-Ca"], "ValueList" : ["Fractional Excretion Calcium = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoCalcemiaPlan"},
    "LowCalciumExplainFECaOption" : { "ButtonLabelList" : ["Explain FE-Ca"], "ValueList" : ["Fractional Excretion of Calcium over 1 percent in hypocalcemic patients suggests renal etiology (such as Familial Hypocalciuric Hypercalcaemia)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoCalcemiaPlan"},

    "LowCalciumCheckiCalOption" : { "ButtonLabelList" : ["Check iCal"], "ValueList" : ["ionized Calcium"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoCalcemiaPlan"},
    "LowCalciumCheckVitaminOption" : { "ButtonLabelList" : ["Check VitD"], "ValueList" : ["Vitamin D"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoCalcemiaPlan"},
    "LowCalciumCheckPTHOption" : { "ButtonLabelList" : ["Check PTH"], "ValueList" : ["PTH"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoCalcemiaPlan"},
    "LowCalciumCheckUrineOption" : { "ButtonLabelList" : ["Check Urine"], "ValueList" : ["urine Cr and Calcium"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoCalcemiaPlan"},
    "LowCalciumReplaceCaOption" : { "ButtonLabelList" : ["Give Ca", "Give Ca"], "ValueList" : ["IV Calcium Gluconate", "PO Calcium"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoCalcemiaPlan"},
    "LowCalciumGiveVitDOption" : { "ButtonLabelList" : ["Give VitD"], "ValueList" : ["Cholecalciferol 2000 IU PO daily"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypoCalcemiaPlan"},




    ///////////////////////////////////////////////////////////
    // High Ca
    ///////////////////////////////////////////////////////////
    "HighCalciumShowCaOption" : { "ButtonLabelList" : ["Show Ca"], "ValueList" : ["Ca = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERCalcemiaPlan"},
    "HighCalciumShowiCalOption" : { "ButtonLabelList" : ["Show iCal"], "ValueList" : ["ionized Ca = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERCalcemiaPlan"},
    "HighCalciumShowVitDOption" : { "ButtonLabelList" : ["Show VitD"], "ValueList" : ["VitD = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERCalcemiaPlan"},
    "HighCalciumShow125VitDOption" : { "ButtonLabelList" : ["Show 1,25VitD"], "ValueList" : ["1,25 VitD = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERCalcemiaPlan"},
    "HighCalciumShowFECaOption" : { "ButtonLabelList" : ["Show FE-Ca"], "ValueList" : ["Fractional Excretion Calcium = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERCalcemiaPlan"},
    "HighCalciumExplainFECaOption" : { "ButtonLabelList" : ["Explain FE-Ca"], "ValueList" : ["Fractional Excretion of Calcium under 1 percent in hypercalcemic patients suggests renal etiology"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERCalcemiaPlan"},
    "HighCalciumCheckiCalOption" : { "ButtonLabelList" : ["Check iCal"], "ValueList" : ["ionized Calcium"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERCalcemiaPlan"},
    "HighCalciumCheckVitaminOption" : { "ButtonLabelList" : ["Check VitD"], "ValueList" : ["Vitamin D Level"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERCalcemiaPlan"},
    "HighCalciumCheck125VitaminOption" : { "ButtonLabelList" : ["Check 1,25 VitD"], "ValueList" : ["1,25 Vitamin D Level"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERCalcemiaPlan"},
    "HighCalciumCheckPTHrPOption" : { "ButtonLabelList" : ["Check PTHrP"], "ValueList" : ["PTHrP"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERCalcemiaPlan"},
    "HighCalciumCheckPTHOption" : { "ButtonLabelList" : ["Check PTH"], "ValueList" : ["PTH"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERCalcemiaPlan"},
    "HighCalciumIVFluidsOption" : { "ButtonLabelList" : ["IV Fluids"], "ValueList" : ["IV Fluids - NS @200mL/hr"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERCalcemiaPlan"},
    "HighCalciumPamidronateOption" : { "ButtonLabelList" : ["Pamidronate"], "ValueList" : ["Pamidronate 90mg once"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERCalcemiaPlan"},
    "HighCalciumDiureticsOption" : { "ButtonLabelList" : ["Diuretics"], "ValueList" : ["Lasix 40mg PO daily"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypERCalcemiaPlan"},



    ///////////////////////////////////////////////////////////
    // BPH
    ///////////////////////////////////////////////////////////

    "BPH_HOME_TAMSULOSIN_OPTION" : { "ButtonLabelList" : ["Tamsulosin 0.4", "Tamsulosin 0.8"], "ValueList" : ["Tamsulosin 0.4", "Tamsulosin 0.8"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BPHPlan"},
    "BPH_HOME_FINASTERIDE_OPTION" : { "ButtonLabelList" : ["Finasteride"], "ValueList" : ["Finasteride"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BPHPlan"},
    "BPH_HOME_IO_CATH_OPTION" : { "ButtonLabelList" : ["IO Cath"], "ValueList" : ["in and out cath"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BPHPlan"},
    "BPH_SYMPTOMS_STRAINING_OPTION" : { "ButtonLabelList" : ["straining"], "ValueList" : ["straining"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BPHPlan"},
    "BPH_SYMPTOMS_WEAK_STREAM_OPTION" : { "ButtonLabelList" : ["weak stream"], "ValueList" : ["weak stream"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BPHPlan"},
    "BPH_SYMPTOMS_SLOW_STREAM_OPTION" : { "ButtonLabelList" : ["slow stream"], "ValueList" : ["slow stream"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BPHPlan"},
    "BPH_SYMPTOMS_FREQUENCY_OPTION" : { "ButtonLabelList" : ["frequency"], "ValueList" : ["nocturnal frequency"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BPHPlan"},
    "BPH_TREAT_TAMSULOSIN_OPTION" : { "ButtonLabelList" : ["Tamsulosin 0.4", "Tamsulosin 0.8"], "ValueList" : ["Tamsulosin 0.4mg daily", "Tamsulosin 0.8mg daily"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BPHPlan"},
    "BPH_TREAT_FINASTERIDE_OPTION" : { "ButtonLabelList" : ["Finasteride"], "ValueList" : ["Finasteride 5mg daily"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BPHPlan"},
    "BPH_TREAT_IOCATH_OPTION" : { "ButtonLabelList" : ["IO Cath"], "ValueList" : ["I/O cath Q6h PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BPHPlan"},
    "BPH_TREAT_FOLEY_OPTION" : { "ButtonLabelList" : ["Foley"], "ValueList" : ["Foley"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BPHPlan"},
    "BPH_CHECK_PSA_OPTION" : { "ButtonLabelList" : ["Check PSA"], "ValueList" : ["Check PSA"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BPHPlan"},
    "BPH_SHOW_PSA_OPTION" : { "ButtonLabelList" : ["Show PSA"], "ValueList" : ["PSA = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BPHPlan"},



    ///////////////////////////////////////////////////////////
    // VIT D
    ///////////////////////////////////////////////////////////

    "LOWVITD_VITDLEVEL_OPTION" : { "ButtonLabelList" : ["Show level"], "ValueList" : ["Vit D level = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "VitDPlan"},
    "LOWVITD_SHOW_TSCORE_OPTION" : { "ButtonLabelList" : ["Show TScore"], "ValueList" : ["Latest T-score = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "VitDPlan"},
    "LOWVITD_HOME_MEDS_OPTION" : { "ButtonLabelList" : ["Ca-VitD", "Cholecal 1K", "Colecal 2K", "Ergocal 50k"], "ValueList" : ["Ca-VitD", "Cholecal 1K", "Colecal 2K", "Ergocal 50k"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "VitDPlan"},
    "LOWVITD_TREAT_OPTION" : { "ButtonLabelList" : ["Cholecal 1K", "Colecal 2K", "Ergocal 50k"], "ValueList" : ["Cholecalciferol 1000 IU daily", "Cholecalciferol 2000 IU daily", "Ergocalciferol 50000 IU every Mon/Thu"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "VitDPlan"},



    ///////////////////////////////////////////////////////////
    // Oncology
    ///////////////////////////////////////////////////////////
    "ONCOLOGY_CANCER_TYPE_MODIFIER" : { "ButtonLabelList" : ["Lung", "Prostate", "Colon", "Esophogeal"], "ValueList" : ["Lung Cancer", "Prostate Cancer", "Colon Cancer", "Esophogeal Cancer"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_NEWLY_DIAGNOSED_MODIFIER" : { "ButtonLabelList" : ["New"], "ValueList" : [" (newly diagnosed)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_METASTATIC_MODIFIER" : { "ButtonLabelList" : ["Metastatic"], "ValueList" : ["Metastatic "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},

    "ONCOLOGY_STAGE_MODIFIER" : { "ButtonLabelList" : ["Stage I", "Stage II", "Stage III", "Stage IV"], "ValueList" : [" (stage I)", " (stage II)", " (stage III)", " (stage IV)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},

    "ONCOLOGY_STATUS_WHEN_DIAG_OPTION" : { "ButtonLabelList" : ["When Diag"], "ValueList" : ["Diagnosed in"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_STATUS_SP_SURGERY_OPTION" : { "ButtonLabelList" : ["s/p Surgery"], "ValueList" : ["s/p Surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_STATUS_SP_CHEMO_OPTION" : { "ButtonLabelList" : ["s/p Chemo"], "ValueList" : ["s/p Chemo"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_STATUS_SP_XRT_OPTION" : { "ButtonLabelList" : ["s/p Rad"], "ValueList" : ["s/p Rad"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_STATUS_ECOG_OPTION" : { "ButtonLabelList" : ["ECOG 0", "ECOG 1", "ECOG 2", "ECOG 3", "ECOG 4"], "ValueList" : ["ECOG grade 0 (fully active)", "ECOG grade 1 (cant do strenuous work)", "ECOG grade 2(care for self but cant work)", "ECOG grade 3(limited self care, out of bed/chair less than 50percent)", "ECOG grade 4(disabled, confined to chair/bed) 5(dead)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_STATUS_BASELINE_URATE_OPTION" : { "ButtonLabelList" : ["Show Urate"], "ValueList" : ["Baseline Uric Acid=xxxx"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_STATUS_BASELINE_LDH_OPTION" : { "ButtonLabelList" : ["Show LDH"], "ValueList" : ["Baseline LDH=xxxxx"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_STAGING_MRI_BRAIN_OPTION" : { "ButtonLabelList" : ["MRI Brain"], "ValueList" : ["MRI Brain to screen for mets"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_STAGING_CT_OPTION" : { "ButtonLabelList" : ["CT Chest/abdom"], "ValueList" : ["CT Chest/abdom/pelvis to screen for mets"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},

    "ONCOLOGY_TLS_GET_LDH_OPTION" : { "ButtonLabelList" : ["Get LDH"], "ValueList" : ["Check serum LDH"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_TLS_GET_URATE_OPTION" : { "ButtonLabelList" : ["Get Urate"], "ValueList" : ["Check serum Urate"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_TLS_Allopurinol_OPTION" : { "ButtonLabelList" : ["Allopurinol"], "ValueList" : ["Allopurinol 100mg TID"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_TLS_Rasburicase_OPTION" : { "ButtonLabelList" : ["Rasburicase"], "ValueList" : ["Rasburicase 0.15 mg/kg once (contraindicated if G6PD deficiency)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_TLS_IV_Fluids_OPTION" : { "ButtonLabelList" : ["IVF NS"], "ValueList" : ["IV Fluids - NS at 150 mL/hr"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_TLS_DONT_ALKALINIZE_OPTION" : { "ButtonLabelList" : ["Dont alkalinize"], "ValueList" : ["Do not alkalinize the urine - it increases risks for CaPhos stones"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},

    "ONCOLOGY_HYPERCALCEMIA_IVF_OPTION" : { "ButtonLabelList" : ["IVF NS"], "ValueList" : ["IV Fluids - NS at 150 mL/hr"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_HYPERCALCEMIA_Bisphosphonate_OPTION" : { "ButtonLabelList" : ["Pamidronate"], "ValueList" : ["Pamidronate 90mg once"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},

    "ONCOLOGY_ONDANSETRON_PRN_OPTION" : { "ButtonLabelList" : ["PRN Zofran"], "ValueList" : ["Ondansetron 4mg IV Q4h PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_ONDANSETRON_SCHEDULED_OPTION" : { "ButtonLabelList" : ["Sched Zofran"], "ValueList" : ["Ondansetron 8mg PO Q8h scheduled"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_Prochlorperazine_OPTION" : { "ButtonLabelList" : ["PRN Compazine"], "ValueList" : ["Prochlorperazine 5mg IV PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_Phenergan_OPTION" : { "ButtonLabelList" : ["PRN Phenergan"], "ValueList" : ["Promethazine 25 mg PO PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},

    "ONCOLOGY_MORPHINE_ER_OPTION" : { "ButtonLabelList" : ["Morphine ER 15", "Morphine ER 30", "Morphine ER 45", "Morphine ER 60"], "ValueList" : ["Morphine ER 15mg PO Q12h Scheduled", "Morphine ER 30mg PO Q12h Scheduled", "Morphine ER 45mg PO Q12h Scheduled", "Morphine ER 60mg PO Q12h Scheduled"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_OXYCODONE_LR_OPTION" : { "ButtonLabelList" : ["Oxycodone LR 10", "Oxycodone LR 20", "Oxycodone LR 30"], "ValueList" : ["Oxycodone LR 10mg PO Q12h scheduled", "Oxycodone LR 20mg PO Q12h scheduled", "Oxycodone LR 30mg PO Q12h scheduled"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_FENTANYL_OPTION" : { "ButtonLabelList" : ["Fentanyl 25", "Fentanyl 50", "Fentanyl 75", "Fentanyl 100"], "ValueList" : ["Fentanyl 25mcg patch daily", "Fentanyl 50mcg patch daily", "Fentanyl 75mcg patch daily", "Fentanyl 100mcg patch daily"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_Prednisone_OPTION" : { "ButtonLabelList" : ["Prednisone"], "ValueList" : ["Prednisone 40mg PO daily for bone pain"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_MORPHINE_IR_OPTION" : { "ButtonLabelList" : ["PRN Morphine"], "ValueList" : ["Morphine IR 25mg PO Q4h PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_Oxycodone_OPTION" : { "ButtonLabelList" : ["Oxycodone 5", "Oxycodone 10", "Oxycodone 15"], "ValueList" : ["Oxycodone 5mg PO Q4h PRN", "Oxycodone 10mg PO Q4h PRN", "Oxycodone 15mg PO Q4h PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_Dilaudid_PO_OPTION" : { "ButtonLabelList" : ["Dilaudid 2 PO", "Dilaudid 4 PO"], "ValueList" : ["Hydromorphone 2mg PO Q2h PRN", "Hydromorphone 4mg PO Q2h PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_Dilaudid_IV_OPTION" : { "ButtonLabelList" : ["Dilaudid 0.25", "Dilaudid 0.5", "Dilaudid 1.0", "Dilaudid 2.0"], "ValueList" : ["Hydromorphone 0.25mg IV PRN Q2h", "Hydromorphone 0.5mg IV PRN Q2h", "Hydromorphone 1mg IV PRN Q2h", "Hydromorphone 2mg IV PRN Q2h"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_PCA_OPTION" : { "ButtonLabelList" : ["PCA"], "ValueList" : ["Continue Hydromorphone PCA"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},

    "ONCOLOGY_DOCSENNA_OPTION" : { "ButtonLabelList" : ["Doc/Senna 1 BID", "Doc/Senna 2 BID"], "ValueList" : ["Docusate/Senna 1 tab PO BID", "Docusate/Senna 2 tabs PO BID"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_MIRALAX_OPTION" : { "ButtonLabelList" : ["Miralax daily", "Miralax BID"], "ValueList" : ["Miralax 17g PO daily", "Miralax 17g PO BID"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_MgCitrate_OPTION" : { "ButtonLabelList" : ["MgCitrate"], "ValueList" : ["MgCitrate PO PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_Lactulose_OPTION" : { "ButtonLabelList" : ["Lactulose 15 BID", "Lactulose 15 TID", "Lactulose 30 BID", "Lactulose 30 TID", "Lactulose 45 BID", "Lactulose 45 TID"], "ValueList" : ["Lactulose 15mL PO BID", "Lactulose 15mL PO TID", "Lactulose 30mL PO BID", "Lactulose 30mL PO TID", "Lactulose 45mL PO BID", "Lactulose 45mL PO TID"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},

    "ONCOLOGY_Acyclovir_OPTION" : { "ButtonLabelList" : ["Acyclovir"], "ValueList" : ["Acyclovir acyclovir 400 mg tid for Opportunistic Infection prophylaxis"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},
    "ONCOLOGY_Bactrim_OPTION" : { "ButtonLabelList" : ["Bactrim"], "ValueList" : ["Trim/Sulfa 80-160 mg TMP PO qDay for Opportunistic Infection Prophylaxis"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "OncologyPlan"},




    ///////////////////////////////////////////////////////////
    // Hepatitis C
    ///////////////////////////////////////////////////////////

    "HEPC_ANTIBODY_POSITIVE_MODIFIER" : { "ButtonLabelList" : ["Antibody"], "ValueList" : ["Hepatitic C Antibody Positive"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepCPlan"},

    "HEPC_STATUS_VL_OPTION" : { "ButtonLabelList" : ["ViralLoad"], "ValueList" : ["Viral load = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepCPlan"},
    "HEPC_STATUS_GENOTYPE_OPTION" : { "ButtonLabelList" : ["Genotype"], "ValueList" : ["Viral Genotype 1a"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepCPlan"},
    "HEPC_STATUS_HAV_OPTION" : { "ButtonLabelList" : ["HAV Immune", "HepA Not Immune"], "ValueList" : ["HepA IgG positive", "HepA IgG negative"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepCPlan"},
    "HEPC_STATUS_HBV_OPTION" : { "ButtonLabelList" : ["HBV Immune", "HBV Not Immune"], "ValueList" : ["HepBs IgG positive", "HepBs IgG negative"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepCPlan"},
    "HEPC_STATUS_HIV_OPTION" : { "ButtonLabelList" : ["HIV Negative", "HIV Negative"], "ValueList" : ["HIV Negative", "HIV Positive"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepCPlan"},

    "HEPC_CHECK_VIRAL_LOAD_OPTION" : { "ButtonLabelList" : ["PCR"], "ValueList" : ["HCV viral load"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepCPlan"},
    "HEPC_CHECK_GENOTYPE_OPTION" : { "ButtonLabelList" : ["Genotype"], "ValueList" : ["HCV Genotype"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepCPlan"},
    "HEPC_CHECK_HIV_OPTION" : { "ButtonLabelList" : ["HIV"], "ValueList" : ["HIV screen"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepCPlan"},
    "HEPC_CHECK_HAV_OPTION" : { "ButtonLabelList" : ["HAV"], "ValueList" : ["HepA IgG"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepCPlan"},
    "HEPC_CHECK_HBV_OPTION" : { "ButtonLabelList" : ["HBV"], "ValueList" : ["HepBs IgG"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepCPlan"},

    "HEPC_TREAT_HAV_VACCINE_OPTION" : { "ButtonLabelList" : ["HAV Vaccine"], "ValueList" : ["HAV vaccine before discharge"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepCPlan"},
    "HEPC_TREAT_HBV_VACCINE_OPTION" : { "ButtonLabelList" : ["HBV Vaccine"], "ValueList" : ["HBV vaccine before discharge"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepCPlan"},
    "HEPC_TREAT_GI_CLINIC_OPTION" : { "ButtonLabelList" : ["GI Clinic"], "ValueList" : ["Outpatient followup with hepatology clinic"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepCPlan"},




    ///////////////////////////////////////////////////////////
    // Palliative
    ///////////////////////////////////////////////////////////

    "PALLIATIVE_STATUS_HEALTH_CARE_REP_OPTION" : { "ButtonLabelList" : ["POA", "No POA"], "ValueList" : ["The patient has a health care representative", "The patient does not have a health care representative"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},
    "PALLIATIVE_STATUS_LIVING_WILL_OPTION" : { "ButtonLabelList" : ["Living Will", "No Living Will"], "ValueList" : ["The patient has an advance directive", "The patient does not have an advance directive"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},
    "PALLIATIVE_STATUS_CODE_DOCUMENTED_OPTION" : { "ButtonLabelList" : ["Code Doc"], "ValueList" : ["Code status has been discussed and is documented"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},
    "PALLIATIVE_STATUS_DNR_OPTION" : { "ButtonLabelList" : ["DNR", "No DNR"], "ValueList" : ["The patient does NOT want CPR if needed", "The patient wants CPR if needed"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},
    "PALLIATIVE_STATUS_DNI_OPTION" : { "ButtonLabelList" : ["DNI", "No DNI"], "ValueList" : ["The patient does NOT want intubation if needed", "The patient wants intubation if needed"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},
    "PALLIATIVE_STATUS_FEEDING_OPTION" : { "ButtonLabelList" : ["Feeding", "No Feeding"], "ValueList" : ["The patient wants a feeding tubes in the future if needed", "The patient does not want feeding tubes in the future if needed"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},
    "PALLIATIVE_STATUS_COMFORT_OPTION" : { "ButtonLabelList" : ["Comfort Care"], "ValueList" : ["The patient is comfort care"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},

    "PALLIATIVE_Glycopyrrolate_OPTION" : { "ButtonLabelList" : ["Glycopyrrolate"], "ValueList" : ["Glycopyrrolate (Robinul) for secretions"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},
    "PALLIATIVE_Lorazepam_OPTION" : { "ButtonLabelList" : ["Lorazepam"], "ValueList" : ["Lorazepam 1-2mg Q2h PRN for pain or anxiety"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},

    "PALLIATIVE_ONDANSETRON_PRN_OPTION" : { "ButtonLabelList" : ["PRN Zofran"], "ValueList" : ["Ondansetron 4mg IV Q4h PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},
    "PALLIATIVE_ONDANSETRON_SCHEDULED_OPTION" : { "ButtonLabelList" : ["Sched Zofran"], "ValueList" : ["Ondansetron 8mg PO Q8h scheduled"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},
    "PALLIATIVE_Prochlorperazine_OPTION" : { "ButtonLabelList" : ["PRN Compazine"], "ValueList" : ["Prochlorperazine 5mg IV PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},
    "PALLIATIVE_Phenergan_OPTION" : { "ButtonLabelList" : ["PRN Phenergan"], "ValueList" : ["Promethazine 25 mg PO PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},

    "PALLIATIVE_MORPHINE_ER_OPTION" : { "ButtonLabelList" : ["Morphine ER 15", "Morphine ER 30", "Morphine ER 45", "Morphine ER 60"], "ValueList" : ["Morphine ER 15mg PO Q12h Scheduled", "Morphine ER 30mg PO Q12h Scheduled", "Morphine ER 45mg PO Q12h Scheduled", "Morphine ER 60mg PO Q12h Scheduled"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},
    "PALLIATIVE_OXYCODONE_LR_OPTION" : { "ButtonLabelList" : ["Oxycodone LR 10", "Oxycodone LR 20", "Oxycodone LR 30"], "ValueList" : ["Oxycodone LR 10mg PO Q12h scheduled", "Oxycodone LR 20mg PO Q12h scheduled", "Oxycodone LR 30mg PO Q12h scheduled"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},
    "PALLIATIVE_FENTANYL_OPTION" : { "ButtonLabelList" : ["Fentanyl 25", "Fentanyl 50", "Fentanyl 75", "Fentanyl 100"], "ValueList" : ["Fentanyl 25mcg patch daily", "Fentanyl 50mcg patch daily", "Fentanyl 75mcg patch daily", "Fentanyl 100mcg patch daily"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},
    "PALLIATIVE_Prednisone_OPTION" : { "ButtonLabelList" : ["Prednisone"], "ValueList" : ["Prednisone 40mg PO daily for bone pain"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},

    "PALLIATIVE_MORPHINE_IR_OPTION" : { "ButtonLabelList" : ["PRN Morphine"], "ValueList" : ["Morphine IR 25mg PO Q4h PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},
    "PALLIATIVE_Oxycodone_OPTION" : { "ButtonLabelList" : ["Oxycodone 5", "Oxycodone 10", "Oxycodone 15"], "ValueList" : ["Oxycodone 5mg PO Q4h PRN", "Oxycodone 10mg PO Q4h PRN", "Oxycodone 15mg PO Q4h PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},
    "PALLIATIVE_Dilaudid_PO_OPTION" : { "ButtonLabelList" : ["Dilaudid 2 PO", "Dilaudid 4 PO"], "ValueList" : ["Hydromorphone 2mg PO Q2h PRN", "Hydromorphone 4mg PO Q2h PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},
    "PALLIATIVE_Dilaudid_IV_OPTION" : { "ButtonLabelList" : ["Dilaudid 0.25", "Dilaudid 0.5", "Dilaudid 1.0", "Dilaudid 2.0"], "ValueList" : ["Hydromorphone 0.25mg IV PRN Q2h", "Hydromorphone 0.5mg IV PRN Q2h", "Hydromorphone 1mg IV PRN Q2h", "Hydromorphone 2mg IV PRN Q2h"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},
    "PALLIATIVE_PCA_OPTION" : { "ButtonLabelList" : ["PCA"], "ValueList" : ["Continue PCA"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},

    "PALLIATIVE_DOCSENNA_OPTION" : { "ButtonLabelList" : ["Doc/Senna 1 BID", "Doc/Senna 2 BID"], "ValueList" : ["Docusate/Senna 1 tab PO BID", "Docusate/Senna 2 tabs PO BID"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},
    "PALLIATIVE_MIRALAX_OPTION" : { "ButtonLabelList" : ["Miralax daily", "Miralax BID"], "ValueList" : ["Miralax 17g PO daily", "Miralax 17g PO BID"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},
    "PALLIATIVE_MgCitrate_OPTION" : { "ButtonLabelList" : ["MgCitrate"], "ValueList" : ["MgCitrate PO PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},
    "PALLIATIVE_Lactulose_OPTION" : { "ButtonLabelList" : ["Lactulose 15 BID", "Lactulose 15 TID", "Lactulose 30 BID", "Lactulose 30 TID", "Lactulose 45 BID", "Lactulose 45 TID"], "ValueList" : ["Lactulose 15mL PO BID", "Lactulose 15mL PO TID", "Lactulose 30mL PO BID", "Lactulose 30mL PO TID", "Lactulose 45mL PO BID", "Lactulose 45mL PO TID"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PalliativePlan"},


    ///////////////////////////////////////////////////////////
    // Hypothyroid
    ///////////////////////////////////////////////////////////

    "HYPOTHYROID_TREAT_LEVOTHYROXINE_OPTION" : { "ButtonLabelList" : ["Levothy 0.25", "Levothy 0.5", "Levothy 0.75", "Levothy 1.0", "Levothy 1.25", "Levothy 1.5"], "ValueList" : ["Levothyroxine 0.25mg PO daily", "Levothyroxine 0.5mg PO daily", "Levothyroxine 0.75mg PO daily", "Levothyroxine 1.0mg PO daily", "Levothyroxine 1.25mg PO daily", "Levothyroxine 1.5mg PO daily"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HypothyroidPlan"},



    ///////////////////////////////////////////////////////////
    // Pre-Op
    ///////////////////////////////////////////////////////////

    "PREOP_SURGERY_URGENCY_OPTION" : { "ButtonLabelList" : ["Emergent", "Urgent", "Time-sensitive", "Elective"], "ValueList" : ["The surgery is emergent(less than 6hrs)", "The surgery is urgent(6-24hrs)", "The surgery is time-sensitive(1-6 weeks)", "The surgery is elective"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_SURGERY_RISK_OPTION" : { "ButtonLabelList" : ["Low Risk", "Elevated Risk"], "ValueList" : ["The surgery is low risk(cataracts, colonoscopy, dental)", "The surgery is elevated risk(ortho, vascular, thoracic, abdominal)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_PATIENT_FUNCTIONAL_STATUS_OPTION" : { "ButtonLabelList" : ["Excellent", "Good", "Moderate", "Poor"], "ValueList" : ["The patient's functional status is Excellent(over 10 Mets)", "The patient's functional status is Good(7-10 Mets)", "The patient's functional status is Moderate(4-6 Mets)", "The patient's functional status is Poor(below 4 Mets)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_MI_IN_60DAYS_OPTION" : { "ButtonLabelList" : ["No MI 60days", "Recent MI"], "ValueList" : ["No MI in the past 60 days", "The patient most recently had an MI on: xxxx (allow over 60 days before non-emergent surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},

    "PREOP_CARDIAC_RISK_FACTORS_CHF_OPTION" : { "ButtonLabelList" : ["CHF"], "ValueList" : ["Heart Failure"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_CARDIAC_RISK_FACTORS_CAD_OPTION" : { "ButtonLabelList" : ["CAD"], "ValueList" : ["CAD"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_CARDIAC_RISK_FACTORS_CVA_OPTION" : { "ButtonLabelList" : ["Stroke"], "ValueList" : ["stroke"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_CARDIAC_RISK_FACTORS_IDDM_OPTION" : { "ButtonLabelList" : ["IDDM"], "ValueList" : ["insulin-dependant Diabetes"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_CARDIAC_RISK_FACTORS_CrOver2_OPTION" : { "ButtonLabelList" : ["Cr over 2.0"], "ValueList" : ["CKD with Cr over 2.0"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_CARDIAC_RISK_FACTORS_High_Risk_OR_OPTION" : { "ButtonLabelList" : ["Hight Risk OR"], "ValueList" : ["High risk surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},

    "PREOP_AKI_RISKS_Cr_12_21_OPTION" : { "ButtonLabelList" : ["Cr 1.2-2.1"], "ValueList" : ["Preop Cr 1.2-2.1"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_AKI_RISKS_Cr_over_21_OPTION" : { "ButtonLabelList" : ["Cr over 2.1"], "ValueList" : ["Preop Cr over 2.1"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_AKI_RISKS_CHF_OPTION" : { "ButtonLabelList" : ["CHF"], "ValueList" : ["Heart Failure"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_AKI_RISKS_EF_below_35_OPTION" : { "ButtonLabelList" : ["EF below 35"], "ValueList" : ["LVEF below 35"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_AKI_RISKS_IABP_OPTION" : { "ButtonLabelList" : ["IABP"], "ValueList" : ["IABP"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_AKI_RISKS_COPD_OPTION" : { "ButtonLabelList" : ["COPD"], "ValueList" : ["COPD"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_AKI_RISKS_IDDM_OPTION" : { "ButtonLabelList" : ["IDDM"], "ValueList" : ["insulin-dependant Diabetes"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_AKI_RISKS_PAST_CARDIAC_SURGERY_OPTION" : { "ButtonLabelList" : ["s/p Cardiac Surg"], "ValueList" : ["Past Cardiac Surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_AKI_RISKS_PAST_CABG_OPTION" : { "ButtonLabelList" : ["s/p CABG"], "ValueList" : ["Past CABG"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_AKI_RISKS_PAST_VALVULAR_SURGERY_OPTION" : { "ButtonLabelList" : ["s/p Valve Surg"], "ValueList" : ["Past Valvular surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_AKI_RISKS_Emergency_Surgery_OPTION" : { "ButtonLabelList" : ["Emergent OR"], "ValueList" : ["Emergency Surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_AKI_RISKS_Female_OPTION" : { "ButtonLabelList" : ["Female"], "ValueList" : ["Female"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},

    "PREOP_AKI2_RISKS_Over_55yo_OPTION" : { "ButtonLabelList" : ["Over 55yo"], "ValueList" : ["Age over 55"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_AKI2_RISKS_Male_OPTION" : { "ButtonLabelList" : ["Male"], "ValueList" : ["Male"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_AKI2_RISKS_CHF_OPTION" : { "ButtonLabelList" : ["CHF"], "ValueList" : ["Heart Failure"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_AKI2_RISKS_Ascites_OPTION" : { "ButtonLabelList" : ["Ascites"], "ValueList" : ["Ascites"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_AKI2_RISKS_HTN_OPTION" : { "ButtonLabelList" : ["HTN"], "ValueList" : ["Hypertension"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_AKI2_RISKS_IDDM_OPTION" : { "ButtonLabelList" : ["IDDM"], "ValueList" : ["insulin-dependant Diabetes"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_AKI2_RISKS_Emergent_Surgery_OPTION" : { "ButtonLabelList" : ["Emergent OR"], "ValueList" : ["Emergency Surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_AKI2_RISKS_Intraperitoneal_OPTION" : { "ButtonLabelList" : ["Intraperitoneal"], "ValueList" : ["Intraperitoneal surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_AKI2_RISKS_Preop_Cr_11_OPTION" : { "ButtonLabelList" : ["Preop Cr over 1.1"], "ValueList" : ["Preop Cr 1.2 or higher"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},

    "PREOP_Show_NSQIP_Risk_OPTION" : { "ButtonLabelList" : ["NSQIP Risk"], "ValueList" : ["The risk of cardiac event based on NSQIP Risk Calculator is xxxx (https://riskcalculator.facs.org/RiskCalculator/PatientInfo.jsp)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},

    "PREOP_OTHER_CARDIAC_RISKS_Symptomatic_CHF_OPTION" : { "ButtonLabelList" : ["CHF Symptomatic"], "ValueList" : ["The 30-day rate of cardiovascular event is 49 percent for patients with symptomatic HF (2014 ACC/AHA Pre-op guidelines)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_OTHER_CARDIAC_RISKS_Asymptomatic_LV_Dysfunction_OPTION" : { "ButtonLabelList" : ["No Symptoms CHF"], "ValueList" : ["The 30-day rate of cardiovascular event is 23 percent for asymptomativ LV dysfunction (2014 ACC/AHA Pre-op guidelines)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},

    "PREOP_CHECK_EKG_OPTION" : { "ButtonLabelList" : ["EKG"], "ValueList" : ["Check EKG (within 1 month of surgery if elevated risk surgery and either history of CAD or CHF or symptoms)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_CHECK_Echo_OPTION" : { "ButtonLabelList" : ["Echo"], "ValueList" : ["Cardiac Echo (if no Echo in the past year and suspected valvular stenosis or known HF)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_CHECK_BMP_OPTION" : { "ButtonLabelList" : ["BMP"], "ValueList" : ["Check BMP (if history of CKD)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_CHECK_NECK_XR_OPTION" : { "ButtonLabelList" : ["Neck XR"], "ValueList" : ["Cervical spine XRay (history of Rheumatoid arthritis)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},

    "PREOP_BP_TARGET_OPTION" : { "ButtonLabelList" : ["BP Below 180/110"], "ValueList" : ["Maintain BP below 180/110"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_START_BETA_BLOCKER_OPTION" : { "ButtonLabelList" : ["Start BetaBlocker"], "ValueList" : ["Start beta blocker because 3 or more cardiac risk factors (DM, CHF, CAD, CKD, CVA) and at least 2-7 days before surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},

    "PREOP_NO_CATH_OPTION" : { "ButtonLabelList" : ["No Cath"], "ValueList" : ["No cardiac cath for routine screening, only cath if it would be indicated otherwise (such as STEMI)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_Stress_Test_OPTION" : { "ButtonLabelList" : ["Stress Test"], "ValueList" : ["Workup dyspnea of unknown origin or worsening symptoms, with Cardiac Stress Test (including Pharmacological or exercise)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_MITRAL_REPAIR_OPTION" : { "ButtonLabelList" : ["Mitral Repair"], "ValueList" : ["There is symptomatic mitral stenosis, consider balloon or open commissurotomy before elective procedure (2014 ACC/AHA Pre-op guidelines)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},

    "PREOP_ANTICOAG_HOLD_ANTICOAG_OPTION" : { "ButtonLabelList" : ["Hold Anticoag"], "ValueList" : ["Hold anti-coagulants (Coumadin or Factor Xa inhibitors) for 48hrs prior to surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_ANTICOAG_HOLD_ASPIRIN_OPTION" : { "ButtonLabelList" : ["Hold Asa"], "ValueList" : ["Hold Aspirin for non-carotid surgery (no coronary stents, or stents older than 6 weeks before urgent surgery)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_ANTICOAG_HOLD_PLAVIX_OPTION" : { "ButtonLabelList" : ["Hold Plavix"], "ValueList" : ["Hold Clopidogrel (stents older than 6 weeks before surgery)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_ANTICOAG_Check_PTT_OPTION" : { "ButtonLabelList" : ["Check PTT"], "ValueList" : ["Check PTT for Dabiigatran or PT for Apixiban or Rivaroxiban."], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_ANTICOAG_HOLD_COUMADIN_OPTION" : { "ButtonLabelList" : ["Hold Coumadin"], "ValueList" : ["Stop Coumadin 5 days before surgery and resume day after surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_ANTICOAG_BRIDGE_HEPARIN_OPTION" : { "ButtonLabelList" : ["Bridge Heparin"], "ValueList" : ["Bridge with Heparin"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},

    "PREOP_DAY_OF_SURGERY_BETA_BLOCKER_OPTION" : { "ButtonLabelList" : ["Beta Blocker"], "ValueList" : ["Continue beta blocker day of surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_DAY_OF_SURGERY_HOLD_SSRI_OPTION" : { "ButtonLabelList" : ["Hold SSRI"], "ValueList" : ["Hold SSRI on day of surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_DAY_OF_SURGERY_HALF_INSULIN_OPTION" : { "ButtonLabelList" : ["Half Insulin"], "ValueList" : ["Give one-half insulin dose on day of surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_DAY_OF_SURGERY_HOLD_ACE_OPTION" : { "ButtonLabelList" : ["Hold ACE"], "ValueList" : ["Hold ACE-inhibitor or ARB on day of surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_DAY_OF_SURGERY_HOLD_DIURETICS_OPTION" : { "ButtonLabelList" : ["Hold Diuretics"], "ValueList" : ["Hold diuretics on day of surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_DAY_OF_SURGERY_CONTINUE_NARCOTICS_OPTION" : { "ButtonLabelList" : ["Continue Narcs"], "ValueList" : ["Continue benzos, Hydrocodone, Seizure medications day of surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_DAY_OF_SURGERY_CONTINUE_STATINS_OPTION" : { "ButtonLabelList" : ["Continue Statins"], "ValueList" : ["May start a statin before surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_DAY_OF_SURGERY_HOLD_NSAIDS_OPTION" : { "ButtonLabelList" : ["Hold NSAIDs"], "ValueList" : ["Hold all NSAIDs 3 days before surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_DAY_OF_SURGERY_HOLD_PO_DIABETES_MEDS_OPTION" : { "ButtonLabelList" : ["Hold PO DM"], "ValueList" : ["Hold PO diabetic meds (metformin, glyburide) day of surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_SCREEN_MRSA_OPTION" : { "ButtonLabelList" : ["MRSA Screen"], "ValueList" : ["Screen for MRSA colonization with nares swab"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},
    "PREOP_DECOLONIZE_MRSA_OPTION" : { "ButtonLabelList" : ["Decolonize MRSA"], "ValueList" : ["MRSA decolonization with intra-nasal mupirocin"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreopPlan"},


    // EncephalopathyPlan
    "AMS_ACUTE_MODIFIER" : { "ButtonLabelList" : ["AcuteOnChronic", "Acute", "Chronic"], "ValueList" : ["Acute on Chronic ", "Acute ", "Chronic "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},

    "AMS_CHECK_HEAD_CT_OPTION" : { "ButtonLabelList" : ["Head CT"], "ValueList" : ["Head CT"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_CHECK_EEG_OPTION" : { "ButtonLabelList" : ["EEG"], "ValueList" : ["EEG"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_CHECK_Prolactin_OPTION" : { "ButtonLabelList" : ["Prolactin"], "ValueList" : ["Prolactin (rule out seizures)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},

    "AMS_INTOXICATION_CHECK_EtOH_OPTION" : { "ButtonLabelList" : ["EtOH"], "ValueList" : ["serum EtOH and serum volatile screen"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_INTOXICATION_CHECK_UDS_OPTION" : { "ButtonLabelList" : ["UDS"], "ValueList" : ["urine drug screen"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_INTOXICATION_CHECK_Serum_OSM_OPTION" : { "ButtonLabelList" : ["S-Osm"], "ValueList" : ["serum Osmolality"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_INTOXICATION_CHECK_acetaminophen_OPTION" : { "ButtonLabelList" : ["Apap"], "ValueList" : ["acetaminophen level"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_INTOXICATION_CHECK_LEAD" : { "ButtonLabelList" : ["Lead"], "ValueList" : ["serum lead level"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_INTOXICATION_CHECK_HEAVY_METALS" : { "ButtonLabelList" : ["Heavy Metals"], "ValueList" : ["serum Heavy Metals level"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_INTOXICATION_CHECK_Salicylate_OPTION" : { "ButtonLabelList" : ["Asa"], "ValueList" : ["salicylate level"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_CHECK_VMG_OPTION" : { "ButtonLabelList" : ["VBG"], "ValueList" : ["VBG"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_CHECK_CO_OPTION" : { "ButtonLabelList" : ["CO"], "ValueList" : ["Carboxyhemoglobin level"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},


    "AMS_CHECK_Blood_CX_OPTION" : { "ButtonLabelList" : ["Blood Cx"], "ValueList" : ["blood cultures"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_CHECK_Urine_CX_OPTION" : { "ButtonLabelList" : ["Urine Cx"], "ValueList" : ["Urinalysis and Urine Culture"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_CHECK_CXR_OPTION" : { "ButtonLabelList" : ["CXR"], "ValueList" : ["Chest XRay"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_CHECK_RPR_OPTION" : { "ButtonLabelList" : ["RPR"], "ValueList" : ["Syphilis screen"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},


    "AMS_CHECK_Glucose_OPTION" : { "ButtonLabelList" : ["Glucose"], "ValueList" : ["Glucose"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_CHECK_A1c_OPTION" : { "ButtonLabelList" : ["A1c"], "ValueList" : ["A1c"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_METABOLIC_CHECK_B12" : { "ButtonLabelList" : ["B12"], "ValueList" : ["B12 level"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_METABOLIC_CHECK_Thiamine" : { "ButtonLabelList" : ["Thiamine"], "ValueList" : ["Thiamine level"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_CHECK_CPK_OPTION" : { "ButtonLabelList" : ["CPK"], "ValueList" : ["CPK"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},


    "AMS_CHECK_TSH_OPTION" : { "ButtonLabelList" : ["TSH"], "ValueList" : ["TSH"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},

    "AMS_CHECK_Gabapentin_OPTION" : { "ButtonLabelList" : ["Gabapentin"], "ValueList" : ["Gabapentin level"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_CHECK_Lithium_OPTION" : { "ButtonLabelList" : ["Lithium"], "ValueList" : ["Lithium level"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_CHECK_Digoxin_OPTION" : { "ButtonLabelList" : ["Digoxin"], "ValueList" : ["Digoxin level"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_CHECK_Amitriptylene_OPTION" : { "ButtonLabelList" : ["Amitriptylene"], "ValueList" : ["Amitriptylene level"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},

    // Hold sedating meds
    "AMS_HOLD_OPIOIDS_OPTION" : { "ButtonLabelList" : ["Opioids"], "ValueList" : ["Opioids"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_HOLD_BENZOS_OPTION" : { "ButtonLabelList" : ["Benzos"], "ValueList" : ["Benzodiazepines"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_HOLD_MUSCLE_RELAXANTS_OPTION" : { "ButtonLabelList" : ["Muscle Relaxers"], "ValueList" : ["Muscle Relaxers"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_HOLD_ANTIHISTAMINES_OPTION" : { "ButtonLabelList" : ["Hydroxyzine"], "ValueList" : ["Hydroxyzine"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_HOLD_PROMETHAZINE_OPTION" : { "ButtonLabelList" : ["Promethazine"], "ValueList" : ["Promethazine"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_HOLD_GABAPENTIN_OPTION" : { "ButtonLabelList" : ["Gabapentin"], "ValueList" : ["Gabapentin"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},

    "AMS_CHECK_SWALLOW_STUDY_OPTION" : { "ButtonLabelList" : ["Swallow"], "ValueList" : ["Consult Speech therapy for Swallow eval"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_Treat_Thiamine_OPTION" : { "ButtonLabelList" : ["Thiamine"], "ValueList" : ["Thiamine 100mg once now stat and daily"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_Treat_Memantine_OPTION" : { "ButtonLabelList" : ["Memantine"], "ValueList" : ["Memantine 5mg daily"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_Treat_Donepezil_OPTION" : { "ButtonLabelList" : ["Donepezil"], "ValueList" : ["Donepezil 5mg QHS"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_Treat_Lorazepam_OPTION" : { "ButtonLabelList" : ["Lorazepam"], "ValueList" : ["Lorazepam 1mg IV PRN agitation"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},
    "AMS_Treat_Haloperidol_OPTION" : { "ButtonLabelList" : ["Haloperidol"], "ValueList" : ["Haloperidol 4mg IV PRN agitation"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},


    "AMS_SLEEP_MED_OPTION" : { "ButtonLabelList" : ["Trazodone"], "ValueList" : ["Trazodone 50mg PO QHS"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "EncephalopathyPlan"},





    // DysphagiaPlan
    "DYSPHAGIA_Speech_Eval_Result_OPTION" : { "ButtonLabelList" : ["Regular", "Honey", "Nectar", "MechSoft", "NPO"], "ValueList" : ["Speech therapy recommends: Regular diet with thin liquids", "Speech therapy recommends: Honey-thick", "Speech therapy recommends: Nectar-thick", "Speech therapy recommends: Mechanical-soft diet", "Speech therapy recommends: NPO"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DysphagiaPlan"},
    "DYSPHAGIA_Mod_Barium_OPTION" : { "ButtonLabelList" : ["Mod Barium"], "ValueList" : ["Mod Barium swallow"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DysphagiaPlan"},
    "DYSPHAGIA_Place_DHT_OPTION" : { "ButtonLabelList" : ["Dobhoff"], "ValueList" : ["Continue Dobhoff tube"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DysphagiaPlan"},
    "DYSPHAGIA_Tube_Feeds_OPTION" : { "ButtonLabelList" : ["Tube Feeds"], "ValueList" : ["Continue tube feeds"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DysphagiaPlan"},


    ///////////////////////////////////////////////////////////
    // GERD
    ///////////////////////////////////////////////////////////
    "OPTION_HOME_PPI_NAME" : { "ButtonLabelList" : ["Home PPI"], "ValueList" : ["Continue home PPI"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GERDPlan"},


    ///////////////////////////////////////////////////////////
    // MBD
    ///////////////////////////////////////////////////////////
    "MBDHyperphosModifier" : { "ButtonLabelList" : ["HyperPhos"], "ValueList" : ["Hyperphosphatemia due to Kidney Disease"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MBDPlan"},
    ////////////// Status
    "MBD_OPTION_SHOW_Ca" : { "ButtonLabelList" : ["Show Ca"], "ValueList" : ["Ca = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MBDPlan"},
    "MBD_OPTION_SHOW_Phos" : { "ButtonLabelList" : ["Show Phos"], "ValueList" : ["Phos = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MBDPlan"},
    "MBD_OPTION_SHOW_PTH" : { "ButtonLabelList" : ["Show PTH"], "ValueList" : ["PTH = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MBDPlan"},
    "MBD_OPTION_SHOW_ICal" : { "ButtonLabelList" : ["Show iCa"], "ValueList" : ["adjusted Ca = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MBDPlan"},
    ////////////// Workup
    "MBD_OPTION_CHECK_PTH" : { "ButtonLabelList" : ["Check PTH"], "ValueList" : ["PTH"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MBDPlan"},
    "MBD_OPTION_CHECK_VITD" : { "ButtonLabelList" : ["Check VitD"], "ValueList" : ["VitD"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MBDPlan"},
    ////////////// Treat
    "MBD_OPTION_TEAT_BINDER" : { "ButtonLabelList" : ["Sevelamer 800", "Sevelamer 1600", "Sevelamer 2400"], "ValueList" : ["Sevelamer 800mg PO TID with meals", "Sevelamer 1600mg PO TID with meals", "Sevelamer 2400mg PO TID with meals"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MBDPlan"},
    "MBD_OPTION_TEAT_CALCITRIOL" : { "ButtonLabelList" : ["Calcitiol 0.25", "Calcitiol 0.5", "Calcitiol 0.75", "Calcitiol 1.0" ], "ValueList" : ["Calcitiol 0.25mg PO daily", "Calcitiol 0.5mg PO daily", "Calcitiol 0.75mg PO daily", "Calcitiol 1.0mg PO daily" ], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MBDPlan"},

   // IVContrastPlan
    "CONTRAST_PPX_HOLD_ACE_OPTION" : { "ButtonLabelList" : ["Hold ACE"], "ValueList" : ["Hold all nephrotoxins, specifically ACE-inhibitors or ARBS"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IVContrastPlan"},
    "CONTRAST_PPX__Hold_Diuretics_OPTION" : { "ButtonLabelList" : ["Hold Diuretics"], "ValueList" : ["Hold Diuretics"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IVContrastPlan"},
    "CONTRAST_PPX__PRE_FLUIDS_OPTION" : { "ButtonLabelList" : ["Pre Fluids"], "ValueList" : ["IV NS up to 1L given continuously over 8hrs prior to procedure"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IVContrastPlan"},
    "CONTRAST_PPX_POST_FLUIDS_OPTION" : { "ButtonLabelList" : ["Post Fluids"], "ValueList" : ["IV NS up to 1L given continuously over 8hrs post procedure"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IVContrastPlan"},
    "CONTRAST_PPX_BICARB_OPTION" : { "ButtonLabelList" : ["Bicarb"], "ValueList" : ["IV Bicarb, 150mEq/L, give 3 mL/kg over 1 hour prior to procedure, then 1 mL/kg per hour for 6 hours after procedure"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IVContrastPlan"},
    "CONTRAST_PPX_NAC_OPTION" : { "ButtonLabelList" : ["NAC"], "ValueList" : ["N-acetylcysteine 600mg PO Q12hrs for 4 doses, first dose before surgery"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "IVContrastPlan"},

    // HEPATITIS
    "HepatitisAcuteChronicOption" : { "ButtonLabelList" : ["AcuteOnChronic", "Acute", "Chronic"], "ValueList" : ["Acute on Chronic", "Acute", "Chronic"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},
    "HepatitisViralOption" : { "ButtonLabelList" : ["Viral"], "ValueList" : ["Viral"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},
    "HepatitisAlcoholOption" : { "ButtonLabelList" : ["Alcohol"], "ValueList" : ["Alcohol"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},
    // Status
    "HEPATITIS_ALTAST_OPTION" : { "ButtonLabelList" : ["Show ALT/AST"], "ValueList" : ["AST/ALT ratio is "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},
    "HEPATITIS_Trend_OPTION" : { "ButtonLabelList" : ["Trend ALT"], "ValueList" : ["ALT = xxxxx"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},
    "HEPATITIS_Maddrey_OPTION" : { "ButtonLabelList" : ["Show Maddrey"], "ValueList" : ["Maddrey Score = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},
    "HEPATITIS_Lille_OPTION" : { "ButtonLabelList" : ["Show Lille"], "ValueList" : ["Lille Score = "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},
    // Diff
    "HEPATITIS_Diff_Viral_OPTION" : { "ButtonLabelList" : ["Viral"], "ValueList" : ["Viral"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},
    "HEPATITIS_Dif_Toxicity_OPTION" : { "ButtonLabelList" : ["Tox"], "ValueList" : ["Drug-induced"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},
    "HEPATITIS_Autoimmune_OPTION" : { "ButtonLabelList" : ["AutoImmune"], "ValueList" : ["Autoimmune"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},
    "HEPATITIS_Alcohol_OPTION" : { "ButtonLabelList" : ["Alcohol"], "ValueList" : ["Alcohol"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},

    // Workup
    "HEPATITIS_CheckHepAIgG_OPTION" : { "ButtonLabelList" : ["HepA IgG"], "ValueList" : ["HepA Ig"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},
    "HEPATITIS_CheckHepAIgM_OPTION" : { "ButtonLabelList" : ["HepA IgM"], "ValueList" : ["HepA IgM"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},
    "HEPATITIS_CheckHepBIgAg_OPTION" : { "ButtonLabelList" : ["HepB Ig and Ag"], "ValueList" : ["HepB Ig and Ag"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},
    "HEPATITIS_CheckHepBPCR_OPTION" : { "ButtonLabelList" : ["HepB PCR"], "ValueList" : ["HepB viral load"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},
    "HEPATITIS_CheckHepDIgG_OPTION" : { "ButtonLabelList" : ["HepD IgG"], "ValueList" : ["HepD IgG"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},
    "HEPATITIS_CheckHepEIgG_OPTION" : { "ButtonLabelList" : ["HepE IgG"], "ValueList" : ["HepE IgG"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},
    "HEPATITIS_CheckCMV_OPTION" : { "ButtonLabelList" : ["CMV"], "ValueList" : ["CMV viral load"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},
    "HEPATITIS_CheckEBV_OPTION" : { "ButtonLabelList" : ["EBV"], "ValueList" : ["EBV viral load"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},
    "HEPATITIS_CheckCeruloplasm_OPTION" : { "ButtonLabelList" : ["Ceruloplasm"], "ValueList" : ["Ceruloplasm"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},
    "HEPATITIS_CheckApap_OPTION" : { "ButtonLabelList" : ["Apap"], "ValueList" : ["Acetaminophen level"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},

    // Treat
    "HEPATITIS_POSteroids_OPTION" : { "ButtonLabelList" : ["Steroids"], "ValueList" : ["Prednisolone 40mg/day x4 weeks"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},
    "HEPATITIS_Pentoxifylline_OPTION" : { "ButtonLabelList" : ["Pentoxifylline"], "ValueList" : ["Pentoxifylline 400mg PO TID x4 weeks"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "HepatitisPlan"},



    ///////////////////////////////////////////////////////////
    // PANCREATITIS
    ///////////////////////////////////////////////////////////
    "PancreatitisAcuteChronicOption" : { "ButtonLabelList" : ["AcuteOnChronic", "Acute", "Chronic"], "ValueList" : ["Acute on Chronic", "Acute", "Chronic"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PancPlan"},
    // Criteria
    "PANCREATITIS_Pain_OPTION" : { "ButtonLabelList" : ["Pain"], "ValueList" : ["abdominal pain"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PancPlan"},
    "PANCREATITIS_Imaging_OPTION" : { "ButtonLabelList" : ["Imaging"], "ValueList" : ["pancreatic inflammation on imaging"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PancPlan"},
    "PANCREATITIS_Lipsase_OPTION" : { "ButtonLabelList" : ["Lipase"], "ValueList" : ["lipase over 3x upper normal"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PancPlan"},
    // Pain
    "PANCREATITIS_MORPHINE_IR_OPTION" : { "ButtonLabelList" : ["PRN Morphine"], "ValueList" : ["Morphine IR 25mg PO Q4h PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PancPlan"},
    "PANCREATITIS_Oxycodone_OPTION" : { "ButtonLabelList" : ["Oxycodone 5", "Oxycodone 10", "Oxycodone 15"], "ValueList" : ["Oxycodone 5mg PO Q4h PRN", "Oxycodone 10mg PO Q4h PRN", "Oxycodone 15mg PO Q4h PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PancPlan"},
    "PANCREATITIS_Dilaudid_PO_OPTION" : { "ButtonLabelList" : ["Dilaudid 2 PO", "Dilaudid 4 PO"], "ValueList" : ["Hydromorphone 2mg PO Q2h PRN", "Hydromorphone 4mg PO Q2h PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PancPlan"},
    "PANCREATITIS_Dilaudid_IV_OPTION" : { "ButtonLabelList" : ["Dilaudid 0.25 IV", "Dilaudid 0.5", "Dilaudid 1.0", "Dilaudid 2.0"], "ValueList" : ["Hydromorphone 0.25mg IV PRN Q2h", "Hydromorphone 0.5mg IV PRN Q2h", "Hydromorphone 1mg IV PRN Q2h", "Hydromorphone 2mg IV PRN Q2h"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PancPlan"},
    "PANCREATITIS_PCA_OPTION" : { "ButtonLabelList" : ["PCA"], "ValueList" : ["Continue Hydromorphone PCA"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PancPlan"},
    // Fluids
    "PANCREATITIS_FluidBolusOption" : { "ButtonLabelList" : ["Bolus LR"], "ValueList" : ["Bolus 1L LR"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PancPlan"},
    "PANCREATITIS_MaintFluidOption" : { "ButtonLabelList" : ["IV Drip LR"], "ValueList" : ["IV LR at 125 mL/hr"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PancPlan"},
    // Nausea
    "PANCREATITIS_ONDANSETRON_PRN_OPTION" : { "ButtonLabelList" : ["PRN Zofran"], "ValueList" : ["Ondansetron 4mg IV Q4h PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PancPlan"},
    "PANCREATITIS_ONDANSETRON_SCHEDULED_OPTION" : { "ButtonLabelList" : ["Sched Zofran"], "ValueList" : ["Ondansetron 8mg PO Q8h scheduled"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PancPlan"},
    "PANCREATITIS_Prochlorperazine_OPTION" : { "ButtonLabelList" : ["PRN Compazine"], "ValueList" : ["Prochlorperazine 5mg IV PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PancPlan"},
    "PANCREATITIS_Phenergan_OPTION" : { "ButtonLabelList" : ["PRN Phenergan"], "ValueList" : ["Promethazine 25 mg PO PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PancPlan"},
    // Diet
    "PANCREATITIS_Diet_OPTION" : { "ButtonLabelList" : ["NPO", "Clears"], "ValueList" : ["NPO", "Clear liquid diet"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PancPlan"},
    "PANCREATITIS_Pancrealipase_OPTION" : { "ButtonLabelList" : ["Pancrealipase"], "ValueList" : ["Pancrealipase with all meals when eating"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PancPlan"},




    ///////////////////////////////////////////////////////////
    // GI SYMPTOMS
    ///////////////////////////////////////////////////////////
    // Problem Labels
    "GISymptomTypeOption" : { "ButtonLabelList" : ["Nausea", "Diarrhea", "Abdominal Pain"], "ValueList" : ["Nausea and Vomiting", "Diarrhea", "Abdominal Pain"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},

    // History and Description
    "GISymptoms_EmesisBilious_OPTION" : { "ButtonLabelList" : ["NonBilious", "Bilious"], "ValueList" : ["non-bilious", "bilious"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_EmesisBloodyOption" : { "ButtonLabelList" : ["NonBloody", "Bloody", "PureBlood"], "ValueList" : ["non-bloody", "bloody", "pure blood"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_DiarrheaBloodyOption" : { "ButtonLabelList" : ["NonBloody", "Bloody", "PureBlood"], "ValueList" : ["non-bloody", "bloody", "pure blood"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_Melena_OPTION" : { "ButtonLabelList" : ["No Melena", "Melena"], "ValueList" : ["non-melanic", "melanic"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},


    "GISymptoms_StartTimeOption" : { "ButtonLabelList" : ["Started"], "ValueList" : ["Symptoms started xxxx"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_SxLocation_OPTION" : { "ButtonLabelList" : ["Location", "RUQ", "LUQ", "Epigastric", "ALL QUads"], "ValueList" : ["in all quadrants", "located in right upper quadrant", "located in left upper quadrant", "Epigastric", "in all quadrants"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_SxQuality_OPTION" : { "ButtonLabelList" : ["Sharp", "Dull"], "ValueList" : ["sharp", "dull"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_SxRadiate_OPTION" : { "ButtonLabelList" : ["RadiateBack", "RadiateGroin", "NonRadiate"], "ValueList" : ["radiating to back", "radiating to groin", "non-radiating"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_SxSevere_OPTION" : { "ButtonLabelList" : ["Severe"], "ValueList" : ["severe"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_SxConstant_OPTION" : { "ButtonLabelList" : ["Constant", "Periodic"], "ValueList" : ["constant", "periodic"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_SxUnique_OPTION" : { "ButtonLabelList" : ["Unique", "NonUnique"], "ValueList" : ["unique", "similar to past episodes"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_SxWithFood_OPTION" : { "ButtonLabelList" : ["WorseWithFood", "OKWithFood"], "ValueList" : ["worse with food", "not affected by eating"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_SxWithStool_OPTION" : { "ButtonLabelList" : ["BetterWithStool", "NoStoolEffect"], "ValueList" : ["better after stooling", "not affected by stooling"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},

    // Workup
    "GISymptoms_CheckLactate_Option" : { "ButtonLabelList" : ["Lactate"], "ValueList" : ["Lactate"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckLipase_Option" : { "ButtonLabelList" : ["Lipase"], "ValueList" : ["Lipase"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckCRP_Option" : { "ButtonLabelList" : ["CRP"], "ValueList" : ["CRP"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckA1c_Option" : { "ButtonLabelList" : ["A1c"], "ValueList" : ["Hemoglobin A1c"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckAcuteHep_Option" : { "ButtonLabelList" : ["Hepatitis"], "ValueList" : ["acute Hepatitis panel"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckApap_Option" : { "ButtonLabelList" : ["Apap"], "ValueList" : ["acetaminophen level"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckAsa_Option" : { "ButtonLabelList" : ["Salicylate"], "ValueList" : ["salicylate level"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckHCG_Option" : { "ButtonLabelList" : ["BetaHCG"], "ValueList" : ["Beta-HCG"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckCMV_Option" : { "ButtonLabelList" : ["CMV"], "ValueList" : ["serum CMV"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckCA125_Option" : { "ButtonLabelList" : ["CA125"], "ValueList" : ["CA-125"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckCEA_Option" : { "ButtonLabelList" : ["CEA"], "ValueList" : ["CEA"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckCA19_Option" : { "ButtonLabelList" : ["CA19-9"], "ValueList" : ["CA19-9"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckTTG_Option" : { "ButtonLabelList" : ["TTG"], "ValueList" : ["Tissue Transglutaminase IgA antibody (tTG-IgA)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckGliadin_Option" : { "ButtonLabelList" : ["Gliadin"], "ValueList" : ["Deamidated Gliadin IgA antibody"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckEndomysial_Option" : { "ButtonLabelList" : ["Endomysial"], "ValueList" : ["Endomysial IgA antibody"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckUDS_Option" : { "ButtonLabelList" : ["UDS"], "ValueList" : ["Check urine drug screen (to rule out THC)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},

    // Stool Workup
    "GISymptoms_CheckCDiff_Option" : { "ButtonLabelList" : ["GI Panel"], "ValueList" : ["C diff"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckGIPanel_Option" : { "ButtonLabelList" : ["GI Panel"], "ValueList" : ["GI Panel"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckLactoferrin_Option" : { "ButtonLabelList" : ["Lactoferrin"], "ValueList" : ["Lactoferrin"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckHPylori_Option" : { "ButtonLabelList" : ["H Pylori"], "ValueList" : ["H Pylori"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckStoolCMV_Option" : { "ButtonLabelList" : ["Stool CMV"], "ValueList" : ["CMV"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckStoolCalprotectin_Option" : { "ButtonLabelList" : ["Calprotectin"], "ValueList" : ["Calprotectin"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},

    // Imaging
    "GISymptoms_CheckCT_Option" : { "ButtonLabelList" : ["CT Abd/Pelvis"], "ValueList" : ["CT Abd/Pelvis with contrast"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckCTAMesenteric_Option" : { "ButtonLabelList" : ["CTA Mesenteric"], "ValueList" : ["CTA Mesenteric arteries"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CheckDopplerMesenteric_Option" : { "ButtonLabelList" : ["Doppler Mesenteric"], "ValueList" : ["Doppler Mesenteric"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},

    // Antibiotics
    "GISymptoms_PipTazoOption" : { "ButtonLabelList" : ["Pip/Tazo"], "ValueList" : ["Pip/Tazo 3.375g IV Q6h"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_CeftriaxoneOption" : { "ButtonLabelList" : ["Ceftriaxone"], "ValueList" : ["Ceftriaxone 2g IV daily"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_FlagylOption" : { "ButtonLabelList" : ["Metronidazole"], "ValueList" : ["Metronidazole 500mg q6h"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},

    // Fluids
    "GISymptoms_FluidBolusOption" : { "ButtonLabelList" : ["Bolus LR"], "ValueList" : ["Bolus 1L LR"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_MaintFluidOption" : { "ButtonLabelList" : ["IV Drip LR"], "ValueList" : ["IV LR at 125 mL/hr"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},

    // Pain
    "GISymptoms_MORPHINE_IR_OPTION" : { "ButtonLabelList" : ["PRN Morphine"], "ValueList" : ["Morphine IR 25mg PO Q4h PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_Oxycodone_OPTION" : { "ButtonLabelList" : ["Oxycodone 5", "Oxycodone 10", "Oxycodone 15"], "ValueList" : ["Oxycodone 5mg PO Q4h PRN", "Oxycodone 10mg PO Q4h PRN", "Oxycodone 15mg PO Q4h PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_Dilaudid_PO_OPTION" : { "ButtonLabelList" : ["Dilaudid 2 PO", "Dilaudid 4 PO"], "ValueList" : ["Hydromorphone 2mg PO Q2h PRN", "Hydromorphone 4mg PO Q2h PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_Dilaudid_IV_OPTION" : { "ButtonLabelList" : ["Dilaudid 0.25", "Dilaudid 0.5", "Dilaudid 1.0", "Dilaudid 2.0"], "ValueList" : ["Hydromorphone 0.25mg IV PRN Q2h", "Hydromorphone 0.5mg IV PRN Q2h", "Hydromorphone 1mg IV PRN Q2h", "Hydromorphone 2mg IV PRN Q2h"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_PCA_OPTION" : { "ButtonLabelList" : ["PCA"], "ValueList" : ["Continue Hydromorphone PCA"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},

    // Nausea
    "GISymptoms_ONDANSETRON_PRN_OPTION" : { "ButtonLabelList" : ["PRN Zofran"], "ValueList" : ["Ondansetron 4mg IV Q4h PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_ONDANSETRON_SCHEDULED_OPTION" : { "ButtonLabelList" : ["Sched Zofran"], "ValueList" : ["Ondansetron 8mg PO Q8h scheduled"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_Prochlorperazine_OPTION" : { "ButtonLabelList" : ["PRN Compazine"], "ValueList" : ["Prochlorperazine 5mg IV PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_Phenergan_OPTION" : { "ButtonLabelList" : ["PRN Phenergan"], "ValueList" : ["Promethazine 25 mg PO PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_Cyproheptadine_OPTION" : { "ButtonLabelList" : ["Cyproheptadine"], "ValueList" : ["Cyproheptadine 2mg Q6h"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},
    "GISymptoms_Amitriptylene_OPTION" : { "ButtonLabelList" : ["Amitriptylene"], "ValueList" : ["Amitriptylene 25mg PO"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GISymptomsPlan"},


    ///////////////////////////////////////////////////////////
    // MOOD DISORDER
    ///////////////////////////////////////////////////////////
    "Mood_Disorder_DepressionOption" : { "ButtonLabelList" : ["Depression"], "ValueList" : ["Depression"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    "Mood_Disorder_AnxietyOption" : { "ButtonLabelList" : ["Anxiety"], "ValueList" : ["Anxiety"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    // DHM
    "MOOD_DISORDER_AxisI_OPTION" : { "ButtonLabelList" : ["None", "Anxiety, Depression"], "ValueList" : ["None", "Anxiety, Depression"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    "MOOD_DISORDER_AxisII_OPTION" : { "ButtonLabelList" : ["None", "Borderline"], "ValueList" : ["None", "Borderline personality disorder"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    "MOOD_DISORDER_AxisIII_OPTION" : { "ButtonLabelList" : ["None", "Medical"], "ValueList" : ["None", "Multiple medical conditions"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    "MOOD_DISORDER_AxisIV_OPTION" : { "ButtonLabelList" : ["None", "Drugs", "Economic"], "ValueList" : ["None", "Substance abuse", "Economic stress"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    // SIGECAPS
    "MOOD_DISORDER_Sleep_OPTION" : { "ButtonLabelList" : ["Sleep"], "ValueList" : ["Sleep"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    "MOOD_DISORDER_Interest_OPTION" : { "ButtonLabelList" : ["Interest"], "ValueList" : ["Interest"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    "MOOD_DISORDER_Guilt_OPTION" : { "ButtonLabelList" : ["Guilt"], "ValueList" : ["Guilt"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    "MOOD_DISORDER_Energy_OPTION" : { "ButtonLabelList" : ["Energy"], "ValueList" : ["Energy"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    "MOOD_DISORDER_Concentraion_OPTION" : { "ButtonLabelList" : ["Concentraion"], "ValueList" : ["Concentraion"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    "MOOD_DISORDER_Appetite_OPTION" : { "ButtonLabelList" : ["Appetite"], "ValueList" : ["Appetite"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    "MOOD_DISORDER_Psychomotor_OPTION" : { "ButtonLabelList" : ["Psychomotor"], "ValueList" : ["Psychomotor"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    "MOOD_DISORDER_Suicidal_OPTION" : { "ButtonLabelList" : ["Suicidal"], "ValueList" : ["Suicidal"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    // Suicidal

    "MOOD_DISORDER_SHOW_QTC_OPTION" : { "ButtonLabelList" : ["Show Qtc"], "ValueList" : ["Latest Qtc is: "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    "MOOD_DISORDER_SUICIDE_RISK_OPTION" : { "ButtonLabelList" : ["Not Suicidal"], "ValueList" : ["The patient denies suicidal ideation"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},

    // Comorbidities
    "MOOD_DISORDER_MANIA_OPTION" : { "ButtonLabelList" : ["Mania"], "ValueList" : ["Mania"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    "MOOD_DISORDER_PTSD_OPTION" : { "ButtonLabelList" : ["PTSD"], "ValueList" : ["PTSD"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    "MOOD_DISORDER_ANXIETY_OPTION" : { "ButtonLabelList" : ["Anxiety"], "ValueList" : ["Anxiety"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    // Workup
    "MOOD_DISORDER_HYPOTHYROID_OPTION" : { "ButtonLabelList" : ["Hypothyroid"], "ValueList" : ["Check TSH to rule out hypothyroid"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    "MOOD_DISORDER_DRUG_USE_OPTION" : { "ButtonLabelList" : ["Illegal Drugs"], "ValueList" : ["Check urine drug screen"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    // Treat
    "MOOD_DISORDER_START_SSRI_OPTION" : { "ButtonLabelList" : ["Start SSRI"], "ValueList" : ["Start Sertraline"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},
    "MOOD_DISORDER_HOME_MEDS_OPTION" : { "ButtonLabelList" : ["Home Meds"], "ValueList" : ["Continue home medications"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "DepressionPlan"},

    ///////////////////////////////////////////////////////////
    // GOUT
    ///////////////////////////////////////////////////////////
    "GoutAcuteChronicOption" : { "ButtonLabelList" : ["AcuteOnChronic", "Acute", "Chronic"], "ValueList" : ["Acute on Chronic", "Acute", "Chronic"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GoutPlan"},
    // Status
    "GOUT_FLARING_OPTION" : { "ButtonLabelList" : ["Flaring"], "ValueList" : ["This is an acute flare"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GoutPlan"},
    "GOUT_LAST_FLARE_OPTION" : { "ButtonLabelList" : ["Last Flare"], "ValueList" : ["Last Gout flare was xxxxx"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GoutPlan"},
    "GOUT_SHOW_URATE_OPTION" : { "ButtonLabelList" : ["Show Urate"], "ValueList" : ["Serum Uric acid is xxxx"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GoutPlan"},
    // Home Meds
    "GOUT_HOME_ALLOPURINOL_OPTION" : { "ButtonLabelList" : ["Alloputinol"], "ValueList" : ["Alloputinol"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GoutPlan"},
    // Treat
    "GOUT_Target_OPTION" : { "ButtonLabelList" : ["Urate Target"], "ValueList" : ["Titrate Allopurinol for serum urate at below 6 if one attack in the past year and CKD-2, or two attacks in the past year and CKD-1 (per ACR 2012 Guidelines)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GoutPlan"},
    "GOUT_Allopurinol_OPTION" : { "ButtonLabelList" : ["Allopurinol"], "ValueList" : ["Allopurinol 100mg PO daily"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GoutPlan"},
    "GOUT_Prednisone_OPTION" : { "ButtonLabelList" : ["Prednisone"], "ValueList" : ["Prednisone 60mg PO daily x5 days, then Colchicine"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GoutPlan"},
    "GOUT_Febuxostat_OPTION" : { "ButtonLabelList" : ["Febuxostat"], "ValueList" : ["Consider Febuxostat if the patient cannot tolerate Allopurinol or Pegloticase if the patient has flares resistant to purine lowering"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GoutPlan"},
    "GOUT_SLOW_DIURETICS_OPTION" : { "ButtonLabelList" : ["Slow Diuretics"], "ValueList" : ["Decrease Diuretics"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "GoutPlan"},


    ///////////////////////////////////////////////////////////
    // SYNCOPE
    ///////////////////////////////////////////////////////////
    // Cardiogenic
    "SYNCOPE_Orthostatic_OPTION" : { "ButtonLabelList" : ["Orthostatic"], "ValueList" : ["Orthostatic BP was xxxxx supine and xxx standing"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "SyncopePlan"},
    "SYNCOPE_SHOW_EKG_OPTION" : { "ButtonLabelList" : ["EKG Normal"], "ValueList" : ["EKG shows no arrhythmias"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "SyncopePlan"},
    // Differential
    "SYNCOPE_DIFFERENTIAL_Medications_OPTION" : { "ButtonLabelList" : ["Meds"], "ValueList" : ["medications"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "SyncopePlan"},
    "SYNCOPE_DIFFERENTIAL_Cardiogenic_OPTION" : { "ButtonLabelList" : ["Cardiac"], "ValueList" : ["cardiogenic"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "SyncopePlan"},
    "SYNCOPE_DIFFERENTIAL_Neuro_OPTION" : { "ButtonLabelList" : ["Neuro"], "ValueList" : ["neurologic"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "SyncopePlan"},
    "SYNCOPE_DIFFERENTIAL_Hematologic_OPTION" : { "ButtonLabelList" : ["Heme"], "ValueList" : ["hematologic"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "SyncopePlan"},
    "SYNCOPE_DIFFERENTIAL_Infectious_OPTION" : { "ButtonLabelList" : ["Infectious"], "ValueList" : ["infectious"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "SyncopePlan"},
    // Workup
    "SYNCOPE_GET_EKG_OPTION" : { "ButtonLabelList" : ["Check EKG"], "ValueList" : ["EKG"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "SyncopePlan"},
    "SYNCOPE_UDS_OPTION" : { "ButtonLabelList" : ["Get UDS"], "ValueList" : ["Urine Drug Screen"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "SyncopePlan"},
    "SYNCOPE_Interrogate_ICD_OPTION" : { "ButtonLabelList" : ["Check ICD"], "ValueList" : ["Interrogate ICD"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "SyncopePlan"},
    "SYNCOPE_Telemetry_OPTION" : { "ButtonLabelList" : ["Tele"], "ValueList" : ["Monitor on telemetry"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "SyncopePlan"},
    "SYNCOPE_EEG_OPTION" : { "ButtonLabelList" : ["EEG"], "ValueList" : ["EEG"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "SyncopePlan"},
    "SYNCOPE_CT_HEAD_OPTION" : { "ButtonLabelList" : ["CT Head"], "ValueList" : ["CT Head"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "SyncopePlan"},
    "SYNCOPE_BLOOD_CULTURES_OPTION" : { "ButtonLabelList" : ["Blood Cx"], "ValueList" : ["blood cultures"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "SyncopePlan"},
    "SYNCOPE_PROCAL_OPTION" : { "ButtonLabelList" : ["Procal"], "ValueList" : ["Procalcitonin"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "SyncopePlan"},
    // Treat
    "SYNCOPE_IV_FLUIDS_OPTION" : { "ButtonLabelList" : ["IV Drip NS"], "ValueList" : ["Continuous IV fluids, NS at 150mL/hr"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "SyncopePlan"},
    "SYNCOPE_HOLTER_OPTION" : { "ButtonLabelList" : ["Holter Monitor"], "ValueList" : ["Holter Monitor on discharge"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "SyncopePlan"},


    ///////////////////////////////////////////////////////////
    // PRESSURE ULCER
    ///////////////////////////////////////////////////////////
    "PressureUlcer_StageOption" : { "ButtonLabelList" : ["Stage I", "Stage II", "Stage III", "Stage IV"], "ValueList" : ["Stage I", "Stage II", "Stage III", "Stage IV"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PressureUlcersPlan"},
    // Treat
    "PRESSURE_ULCER_WOUND_CARE_OPTION" : { "ButtonLabelList" : ["Wound Care"], "ValueList" : ["Wound Care"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PressureUlcersPlan"},

    ///////////////////////////////////////////////////////////
    // LEG FRACTURE
    ///////////////////////////////////////////////////////////
    "LegFracture_SideMODIFIER" : { "ButtonLabelList" : ["Left", "Right"], "ValueList" : ["Left", "Right"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "LegFracturePlan"},
    "LegFracture_JointMODIFIER" : { "ButtonLabelList" : ["Hip", "Femur", "Tibia", "Humerus", "Radius"], "ValueList" : ["Hip", "Femur", "Tibia", "Humerus", "Radius"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "LegFracturePlan"},
    // Pain
    "LEG_FRACTURE_Opioids_OPTION" : { "ButtonLabelList" : ["Oxycodone 5", "Oxycodone 10", "Oxycodone 15"], "ValueList" : ["Oxycodone 5mg PO Q4h PRN", "Oxycodone 10mg PO Q4h PRN", "Oxycodone 15mg PO Q4h PRN"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "LegFracturePlan"},
    // Pre Op
    "LEG_FRACTURE_NON_WEIGHT_BEARING_OPTION" : { "ButtonLabelList" : ["Non-Weight"], "ValueList" : ["Non-Weight-bearing"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "LegFracturePlan"},
    "LEG_FRACTURE_INR_OPTION" : { "ButtonLabelList" : ["INR"], "ValueList" : ["Check INR"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "LegFracturePlan"},
    "LEG_FRACTURE_NPO_OPTION" : { "ButtonLabelList" : ["NPO"], "ValueList" : ["NPO at midnight"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "LegFracturePlan"},
    // Prevent
    "LEG_FRACTURE_CHECK_VIT_D_OPTION" : { "ButtonLabelList" : ["Vit D"], "ValueList" : ["Check Vit D"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "LegFracturePlan"},




    ///////////////////////////////////////////////////////////
    // DIC
    ///////////////////////////////////////////////////////////

    // Criteria
    "DIC_Diagnose_ISTH_PLTS_Option" : { "ButtonLabelList" : ["Plt over 100", "Plt 50-100", "Plt below 50"], "ValueList" : ["Plt over 100", "Plt 50-100", "Plt below 50"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "DICPlan"},
    "DIC_Diagnose_ISTH_PT_Option" : { "ButtonLabelList" : ["INR Below 3", "INR 3 - 6", "INR Above 6"], "ValueList" : ["INR Below 3", "INR 3 - 6", "INR Above 6"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "DICPlan"},
    "DIC_Diagnose_ISTH_Fibrinogen_Option" : { "ButtonLabelList" : ["Fbogen over 1", "Fbogen below 1"], "ValueList" : ["Fibrinogen over 1 g/L", "Fibrinogen below 1 g/L" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "DICPlan"},
    "DIC_Diagnose_ISTH_D_DIMER_Option" : { "ButtonLabelList" : ["DDimer Normal", "DDimer Slight", "DDimer High"], "ValueList" : ["DDimer Normal", "DDimer slightly elevaled", "DDimer strongly elevated" ], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "DICPlan"},

    // Status
    "DICHgbTrendOption" : { "ButtonLabelList" : ["Hgb Trend"], "ValueList" : ["Recent Hgb trend: "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "DICPlan"},
    "DICPlateletTrendOption" : { "ButtonLabelList" : ["Plts Trend"], "ValueList" : ["Recent Platelets trend: "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "DICPlan"},
    "DICINRTrendOption" : { "ButtonLabelList" : ["INR Trend"], "ValueList" : ["Recent INR trend: "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "DICPlan"},
    "DICFibrinogenOption" : { "ButtonLabelList" : ["Fibrinogen Trend"], "ValueList" : ["Recent Fibrinogen trend: "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "DICPlan"},
    "DICDDimerTrendOption" : { "ButtonLabelList" : ["Show DDimer"], "ValueList" : ["Recent D-Dimer trend: "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "DICPlan"},

    // Monitor
    "DIC_Check_CBC_Option" : { "ButtonLabelList" : ["Check CBC"], "ValueList" : ["CBC"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "DICPlan"},
    "DIC_Check_Fibrinogen_Option" : { "ButtonLabelList" : ["Check Fibrinogen"], "ValueList" : ["Clottable Fibrinogen"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "DICPlan"},
    "DIC_Check_INR_Option" : { "ButtonLabelList" : ["Check PT and INR"], "ValueList" : ["PT and INR"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "DICPlan"},
    "DIC_Check_DDimer_Option" : { "ButtonLabelList" : ["Check DDimer"], "ValueList" : ["D-Dimer"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "DICPlan"},

    // Transfuse
    "DIC_Treat_PRN_PRBC_Option" : { "ButtonLabelList" : ["PRN RBC"], "ValueList" : ["Transfuse RBC to maintain Hemoglobin over 7"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "DICPlan"},
    "DIC_Treat_PRN_PLTS_Option" : { "ButtonLabelList" : ["PRN PLTS"], "ValueList" : ["Transfuse 1U platelets for active bleed and Plts below 50, or non-bleeding patients and Plts below 20"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "DICPlan"},
    "DIC_Treat_PRN_FFP_Option" : { "ButtonLabelList" : ["PRN FFP"], "ValueList" : ["Transfuse 2U (or 30mL/kg) Fresh Frozen Plasma for INR over 1.5"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "DICPlan"},
    "DIC_Treat_PRN_Cryo_Option" : { "ButtonLabelList" : ["PRN Cryo"], "ValueList" : ["Transfuse cryoprecipitate (two pools or 10 donor units or 3g) Fresh Frozen Plasma for Fibrinogen < 100 mg/dL"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "DICPlan"},

    // Other
    "DIC_Infection_Option" : { "ButtonLabelList" : ["Infection"], "ValueList" : ["Manage infection as discussed above"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "DICPlan"},



    ///////////////////////////////////////////////////////////
    // Covid
    ///////////////////////////////////////////////////////////
    "CovidPossibleModifier" : { "ButtonLabelList" : ["Possible"], "ValueList" : ["Possible "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},

    // SOFA Current
    "COVIDSOFAOption_Current_PaO2FiO2" : { "ButtonLabelList" : ["Over 400", "300-400", "200-300", "100-200", "Below 100"], "ValueList" : ["Over 400", "300-400", "200-300", "100-200", "Below 100"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "COVIDSOFAOption_Current_Plts" : { "ButtonLabelList" : ["Over 150", "100-150", "50-100", "20-50", "Below 20"], "ValueList" : ["Over 150", "100-150", "50-100", "20-50", "Below 20"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "COVIDSOFAOption_Current_Bili" : { "ButtonLabelList" : ["Below 1.2", "1.2-1.9", "2.0-5.9", "6.0-11.9", "Over 12"], "ValueList" : ["Below 1.2", "1.2-1.9", "2.0-5.9", "6.0-11.9", "Over 12"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "COVIDSOFAOption_Current_MAP" : { "ButtonLabelList" : ["Over 70", "Below 70", "Dop below 5", "Norepi below 0.1", "Norepi above 0.1"], "ValueList" : ["Over 70", "Below 70", "Dop below 5", "Norepi below 0.1", "Norepi above 0.1"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "COVIDSOFAOption_Current_GCS" : { "ButtonLabelList" : ["15 (AOx3)", "13-14 (AOx1)", "10-12", "6-9", "Below 6"], "ValueList" : ["15 (AOx3)", "13-14 (AOx1)", "10-12", "6-9", "Below 6"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "COVIDSOFAOption_Current_Cr" : { "ButtonLabelList" : ["Below 1.2", "1.2-1.9", "2.0-3.4", "3.5-4.9", "Over 5.0"], "ValueList" : ["Below 1.2", "1.2-1.9", "2.0-3.4", "3.5-4.9", "Over 5.0"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},

    // SOFA Baseline
    "COVIDSOFAOption_Baseline_PaO2FiO2" : { "ButtonLabelList" : ["Over 400", "300-400", "200-300", "100-200", "Below 100"], "ValueList" : ["Over 400", "300-400", "200-300", "100-200", "Below 100"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "COVIDSOFAOption_Baseline_Plts" : { "ButtonLabelList" : ["Over 150", "100-150", "50-100", "20-50", "Below 20"], "ValueList" : ["Over 150", "100-150", "50-100", "20-50", "Below 20"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "COVIDSOFAOption_Baseline_Bili" : { "ButtonLabelList" : ["Below 1.2", "1.2-1.9", "2.0-5.9", "6.0-11.9", "Over 12"], "ValueList" : ["Below 1.2", "1.2-1.9", "2.0-5.9", "6.0-11.9", "Over 12"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "COVIDSOFAOption_Baseline_MAP" : { "ButtonLabelList" : ["Over 70", "Below 70", "Dop below 5", "Norepi below 0.1", "Norepi above 0.1"], "ValueList" : ["Over 70", "Below 70", "Dop below 5", "Norepi below 0.1", "Norepi above 0.1"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "COVIDSOFAOption_Baseline_GCS" : { "ButtonLabelList" : ["15 (AOx3)", "13-14 (AOx1)", "10-12", "6-9", "Below 6"], "ValueList" : ["15 (AOx3)", "13-14 (AOx1)", "10-12", "6-9", "Below 6"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "COVIDSOFAOption_Baseline_Cr" : { "ButtonLabelList" : ["Below 1.2", "1.2-1.9", "2.0-3.4", "3.5-4.9", "Over 5.0"], "ValueList" : ["Below 1.2", "1.2-1.9", "2.0-3.4", "3.5-4.9", "Over 5.0"], "IntValueList" : [0, 1, 2, 3, 4], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},

    // History
    "CovidSxStartedOption" : { "ButtonLabelList" : ["Sx Started"], "ValueList" : ["Symptoms began xxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidTestPositiveOption" : { "ButtonLabelList" : ["Test+"], "ValueList" : ["PCR Test positive on xxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidAsymptomaticOption" : { "ButtonLabelList" : ["Asymptomatic"], "ValueList" : ["Patient is asymptomatic and on room air. No indication for steroids or remdesivir."], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},

    // Status
    "CovidSpO2TrendOption" : { "ButtonLabelList" : ["SpO2 Trend"], "ValueList" : ["Recent SpO2 trend: xxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidCRPTrendOption" : { "ButtonLabelList" : ["CRP Trend"], "ValueList" : ["Recent CRP trend: xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidPMNToLymphTrendOption" : { "ButtonLabelList" : ["PMN/Lymph Trend"], "ValueList" : ["Recent Neutrophil/Lymphocyte trend: xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidProcalTrendOption" : { "ButtonLabelList" : ["Procal Trend"], "ValueList" : ["Recent Procalcitonin trend: xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidFibrinogenTrendOption" : { "ButtonLabelList" : ["Fibrinogen Trend"], "ValueList" : ["Recent Fibrinogen trend: xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidPltsTrendOption" : { "ButtonLabelList" : ["Plts Trend"], "ValueList" : ["Recent Platelets trend: xxxxx"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},




    // Risks
    "CovidRiskCRPOver100Option": { "ButtonLabelList" : ["CRP >= 100"], "ValueList" : ["CRP over 100"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidRiskDDimerOver1000Option": { "ButtonLabelList" : ["DDimer>1000"], "ValueList" : ["DDimer over 1000"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidRiskLymphsUnder800Option": { "ButtonLabelList" : ["Lymphs < 800"], "ValueList" : ["Abs Lymphs under 800"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidRiskLDHOver245Option": { "ButtonLabelList" : ["LDH >= 245"], "ValueList" : ["LDH over 245"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidRiskFerritinOver500Option": { "ButtonLabelList" : ["Ferritin >= 500"], "ValueList" : ["Ferritin over 500"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},

    "CovidRiskAgeOver65Option": { "ButtonLabelList" : ["Over 65yo"], "ValueList" : ["Over 65yo"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidRiskDM2Option": { "ButtonLabelList" : ["DM-2"], "ValueList" : ["Diabetes type 2"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidRiskAsthmaOption": { "ButtonLabelList" : ["Asthma"], "ValueList" : ["Asthma"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidRiskCOPDOption": { "ButtonLabelList" : ["COPD"], "ValueList" : ["COPD"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidRiskTobaccoOption": { "ButtonLabelList" : ["Tobacco"], "ValueList" : ["Tobacco use"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},

    "CovidRiskObeseOption": { "ButtonLabelList" : ["BMI 30+"], "ValueList" : ["BMI over 30"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidRiskCADOption": { "ButtonLabelList" : ["CAD"], "ValueList" : ["CAD"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidRiskCHFOption": { "ButtonLabelList" : ["CHF"], "ValueList" : ["Heart Failure"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidRiskCVAOption": { "ButtonLabelList" : ["CVA"], "ValueList" : ["Chronic Stroke"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidRiskLungDiseaseOption": { "ButtonLabelList" : ["Lung Dx"], "ValueList" : ["Chronic Lung Disease"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},

    "CovidRiskCirrhosisOption": { "ButtonLabelList" : ["Cirrhosis"], "ValueList" : ["Cirrhosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidRiskImmuneSuppressionOption": { "ButtonLabelList" : ["LowImmune"], "ValueList" : ["Immune suppressed"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidRiskCFOption": { "ButtonLabelList" : ["CF"], "ValueList" : ["Cystic Fibrosis"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidRiskSickleCellOption": { "ButtonLabelList" : ["Sickle Cell"], "ValueList" : ["Sickle Cell"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidRiskCancerOption": { "ButtonLabelList" : ["Cancer"], "ValueList" : ["Malignancy"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},



    // Care Plan
    "CovidNoTreatOption": { "ButtonLabelList" : ["Monitor"], "ValueList" : ["The patient does not have hypoxia and no clinical or laboratory risk factors, so will monitor but not start steroids or Remdesivir"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidRemdesivirOnlyOption": { "ButtonLabelList" : ["Only Remdesivir"], "ValueList" : ["The patient does not have hypoxia but does have clinical or laboratory risk factors, so will treat with Remdesivir but not start steroids"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidNirmatrelvirOnlyOption": { "ButtonLabelList" : ["Nirmatrelvir"], "ValueList" : ["The patient does not have hypoxia but does have clinical or laboratory risk factors, so will treat with Nirmatrelvir-Ritonivir but not start steroids"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},


    // Workup
    "CovidWUPCROption" : { "ButtonLabelList" : ["Covid PCR"], "ValueList" : ["COVID PCR"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidWUXRayOption" : { "ButtonLabelList" : ["Chest XRay"], "ValueList" : ["Chest XRay"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidWUProcalOption" : { "ButtonLabelList" : ["Procal"], "ValueList" : ["Procalcitonin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidWURVPOption" : { "ButtonLabelList" : ["RVP"], "ValueList" : ["Resp viral panel"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidWUABGOption" : { "ButtonLabelList" : ["ABG"], "ValueList" : ["Arterial blood gas"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidCTPEOption" : { "ButtonLabelList" : ["CT PE"], "ValueList" : ["CT Chest with Pulmonary Embolism protocol"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},

    // Monitor
    "CovidCRPDailyOption" : { "ButtonLabelList" : ["CRP"], "ValueList" : ["CRP"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidCBCDiffPDailyOption" : { "ButtonLabelList" : ["CBC"], "ValueList" : ["CBC with Diff"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidDDimerDailyOption" : { "ButtonLabelList" : ["D-Dimer"], "ValueList" : ["D-Dimer"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidVBGDailyOption" : { "ButtonLabelList" : ["VBG"], "ValueList" : ["Venous blood gas"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidLDHDailyOption" : { "ButtonLabelList" : ["LDH"], "ValueList" : ["LDH"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidFibrinogenDailyOption" : { "ButtonLabelList" : ["Fibrinogen"], "ValueList" : ["Fibrinogen"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidWUFerritinOption" : { "ButtonLabelList" : ["Ferritin"], "ValueList" : ["Ferritin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidWULactateOption" : { "ButtonLabelList" : ["Lactate"], "ValueList" : ["lactate"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},

    // Treat
    "CovidDexamethasoneOption" : { "ButtonLabelList" : ["Dex (low)", "Dex (high)"], "ValueList" : ["Dexamethasone 6mg PO daily x10days (RECOVERY Trial protocol)", "Dexamethasone 20mg IV x5 days (start ) then Dexamethasone 10mg IV x5 days (start ) (CoDEX and Dexa-ARDS Trials protocol)"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidRemdesivirOption" : { "ButtonLabelList" : ["Remdesivir", "Remdesivir"], "ValueList" : ["Remdesivir 200mg on day 1, then 100mg daily for 4 days", "Remdesivir 200mg on day 1, then 100mg daily for 2 days"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidBaricitinibOption" : { "ButtonLabelList" : ["Baricitinib"], "ValueList" : ["Baricitinib 4mg PO daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidNirmatrelvirOption": { "ButtonLabelList" : ["Nirmatrelvir"], "ValueList" : ["Nirmatrelvir-Ritonivir"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidDiureticsOption": { "ButtonLabelList" : ["Lasix 20IV", "Lasix 20IVBID", "Lasix 40IV", "Lasix 40IVBID", "Lasix 80IV", "Lasix 80IVBID", "Lasix 100IV", "Lasix 100IVBID"], "ValueList" : ["Furosemide 20mg IV daily at breakfast", "Furosemide 20mg IV BID", "Furosemide 40mg IV daily at breakfast", "Furosemide 40mg IV BID", "Furosemide 80mg IV daily at breakfast", "Furosemide 80mg IV BID", "Furosemide 100mg IV daily at breakfast", "Furosemide 100mg IV BID"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CovidPlan"},

    // Other
    "CovidApapOption" : { "ButtonLabelList" : ["Apap"], "ValueList" : ["Acetaminophen 650mg PO Q6h PRN for fever"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidGuaifenesinOption" : { "ButtonLabelList" : ["Guaifenesin"], "ValueList" : ["Guaifenesin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidPPIOption" : { "ButtonLabelList" : ["PPI"], "ValueList" : ["Pantoprazole while on steroids"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidInsulinOption" : { "ButtonLabelList" : ["Insulin"], "ValueList" : ["Sliding scale insulin while on steroids"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidAntibioticsOption" : { "ButtonLabelList" : ["Ceftriaxone"], "ValueList" : ["Ceftriaxone 2g IV Q24h and Azithromycin 500mg PO daily"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},

    // Other treat
    "CovidO2Option" : { "ButtonLabelList" : ["O2"], "ValueList" : ["Continue Oxygen per nasal canula. Titrate O2 for 92-96%"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidPrecautionsOption" : { "ButtonLabelList" : ["Precautions"], "ValueList" : ["Airborne precautions, including use of N95 masks, face-shields, gown, gloves"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidNoSteroidsOption" : { "ButtonLabelList" : ["No steroids"], "ValueList" : ["Avoid steroids as this may prolong viral shedding, as per CDC and WHO Guidelines"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidProneOption" : { "ButtonLabelList" : ["Prone"], "ValueList" : ["Ask the patient to lay in prone position for up to 16hrs per day"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : -1, "PlanSectionID" : "CovidPlan"},
    "CovidAlbuterolOption": { "ButtonLabelList" : ["Albuterol"], "ValueList" : ["Albuterol HFA inhaler Q4h PRN"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "CovidPlan"},


    ///////////////////////////////////////////////////////////
    //PE/DVT
    ///////////////////////////////////////////////////////////
    "PEDVTAcuteChronicOption": { "ButtonLabelList" : ["Acute", "Chronic"], "ValueList" : ["Acute ", "Chronic "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PEDVTPlan"},
    "PEDVTMassiveOption": { "ButtonLabelList" : ["Massive", "Submassive"], "ValueList" : ["Massive ", "Submassive "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PEDVTPlan"},
    "PEDVTPEvsDVTOption": { "ButtonLabelList" : ["PE", "DVT"], "ValueList" : ["Pulmonary Embolism", "Deep Venous Thrombosis"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PEDVTPlan"},
    "PEDVTShowEchoOption": { "ButtonLabelList" : ["Echo Strain", "Echo No Strain"], "ValueList" : ["Echo shows right heart strain", "Echo does not show right heart strain"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PEDVTPlan"},
    "PEDVTProvokedOption": { "ButtonLabelList" : ["Immobility", "Cancer", "Travel", "Unprovoked"], "ValueList" : ["This was likely provoked by immobility", "This was likely provoked by malignancy", "This was likely provoked by travel", "This was unprovoked"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PEDVTPlan"},
    "PEDVTGetEchoOption": { "ButtonLabelList" : ["Get Echo"], "ValueList" : ["Get Cardiac Echocardiogram to assess right heart strain "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PEDVTPlan"},
    "PEDVTGetINROption": { "ButtonLabelList" : ["Get INR"], "ValueList" : ["Check INR "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PEDVTPlan"},

    "PEDVTRisksPastDVTOption": { "ButtonLabelList" : ["past DVT/PE"], "ValueList" : ["past DVT/PE"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PEDVTPlan"},
    "PEDVTRisksPastCVAOption": { "ButtonLabelList" : ["past CVA"], "ValueList" : ["past CVA"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PEDVTPlan"},
    "PEDVTRisksCADOption": { "ButtonLabelList" : ["CAD"], "ValueList" : ["coronary artery disease"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PEDVTPlan"},
    "PEDVTRisksOCPOption": { "ButtonLabelList" : ["OCPs"], "ValueList" : ["oral contraceptives"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PEDVTPlan"},
    "PEDVTRisksMiscarriageOption": { "ButtonLabelList" : ["Miscarriage"], "ValueList" : ["past miscarriages"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PEDVTPlan"},
    "PEDVTRisksFamilyOption": { "ButtonLabelList" : ["Family"], "ValueList" : ["family history of clotting disorders"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PEDVTPlan"},

    "PEDVTHomeCoumadinOption": { "ButtonLabelList" : ["Coumadin"], "ValueList" : ["Coumadin"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PEDVTPlan"},
    "PEDVTHomeApixibanOption": { "ButtonLabelList" : ["Apixiban"], "ValueList" : ["Apixiban"], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PEDVTPlan"},

    "PEDVTApixibanOption": { "ButtonLabelList" : ["Apixiban"], "ValueList" : ["Apixiban 5mg PO BID"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PEDVTPlan"},
    "PEDVTLovenoxOption": { "ButtonLabelList" : ["Enoxaparin"], "ValueList" : ["Enoxaparin 1mg/kg subcu BID"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PEDVTPlan"},
    "PEDVTRivaroxabanOption": { "ButtonLabelList" : ["Rivaroxaban"], "ValueList" : ["Rivaroxaban PO"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PEDVTPlan"},
    "PEDVTCoumadinOption": { "ButtonLabelList" : ["Coumadin"], "ValueList" : ["Coumadin 5mg PO daily and titrate to INR "], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PEDVTPlan"},
    "PEDVTHeparinOption": { "ButtonLabelList" : ["Heparin"], "ValueList" : ["Heparin drip"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PEDVTPlan"},




    ///////////////////////////////////////////////////////////
    // Prevention
    ///////////////////////////////////////////////////////////

    // Screening Status
    "Prevention_Colonoscopy_Status_Option": { "ButtonLabelList" : ["Never Colonoscopy", "Last 5 years", "Last 10 years"], "ValueList" : ["No previous Colonoscopy", "Colonoscopy in the past 5 years", "Colonoscopy in the past 10 years"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_Mammogram_Status_Option": { "ButtonLabelList" : ["Never Mammogram", "Last year", "Last 2 year", "Over 2 yrs"], "ValueList" : ["No previous Mammogram", "Mammogram in the past year", "Mammogram in the past 2 years", "Mammogram over 2 years ago"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_ChestCT_Status_Option": { "ButtonLabelList" : ["Never Chest CT", "Last year", "Over 1 year"], "ValueList" : ["No previous Chest CT for lung cancer screening", "Chest CT for lung cancer screening in the past year", "Chest CT for lung cancer screening over 1 year ago"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_LDL_Status_Option": { "ButtonLabelList" : ["No LDL", "Last year", "Over 1yr ago"], "ValueList" : ["No LDL on record", "LDL in the past year", "LDL checked over 1 year ago"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_Pap_Status_Option": { "ButtonLabelList" : ["No Pap", "Last 2 years", "Over 3 years"], "ValueList" : ["No previous Pap Smear", "Pap Smear in the past 2 years", "Pap Smear over years ago"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},

    // Vaccination Status
    "Prevention_Flu_Status_Option": { "ButtonLabelList" : ["No Flu Vax", "Flu Vax"], "ValueList" : ["no Flu vaccine in the past year", "received Flu vaccine in past year"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_Covid_Status_Option": { "ButtonLabelList" : ["No Covid Vax", "Covid Vax"], "ValueList" : ["no Covid vaccine in the past year", "received Covid vaccine in past year"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_Pneumovax_Status_Option": { "ButtonLabelList" : ["No Pneumovax", "1x Pneumovax", "2x Pneumovax"], "ValueList" : ["no Pneumovax", "received one Pneumovax", "received Pneumovax and Booster"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_Zoster_Option": { "ButtonLabelList" : ["No Zoster", "1x Zoster", "2x Zoster"], "ValueList" : ["no Zoster vaccination", "received single Zoster vaccination", "received Zoster vaccine and booster"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_HepA_Vax_Status_Option": { "ButtonLabelList" : ["No Hep A Vax", "Hep A Immune"], "ValueList" : ["no previous Hep A Vaccine", "Hep A immune"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_HepB_Vax_Status_Option": { "ButtonLabelList" : ["No Hep B Vax", "Hep B Immune"], "ValueList" : ["no previous Hep B Vaccination", "Hep B immune"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_HPV_Status_Option": { "ButtonLabelList" : ["No HPV Vax", "HPV Vax"], "ValueList" : ["no HPV vaccination", "received HPV vaccine"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},

    // Vaccination Plans
    "Prevention_Give_Flu_Option": { "ButtonLabelList" : ["Flu Vax"], "ValueList" : ["Influenza vaccination"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_Give_Covid_Option": { "ButtonLabelList" : ["Covid Vax"], "ValueList" : ["Covid vaccination"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_Give_Pneumovax_Option": { "ButtonLabelList" : ["Pneumovax Vax"], "ValueList" : ["Pneumovax"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_Give_Zostervax_Option": { "ButtonLabelList" : ["Zoster Vax"], "ValueList" : ["Zoster vaccination"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_Give_HepA_Vax_Option": { "ButtonLabelList" : ["Hep A Vax"], "ValueList" : ["Hep A vaccination"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_Give_HepB_Vax_Option": { "ButtonLabelList" : ["Hep B Vax"], "ValueList" : ["Hep B vaccination"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_Give_HPV_Option": { "ButtonLabelList" : ["HPV Vax"], "ValueList" : ["HPV vaccination"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},

    // Risks
    "Prevention_ColonRisks_Age_Option": { "ButtonLabelList" : ["50-75yo"], "ValueList" : ["age 50-75"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_ColonRisks_Family_History_Option": { "ButtonLabelList" : ["Family Hx"], "ValueList" : ["positive family history"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_ColonRisks_Past_Adenoma_Option": { "ButtonLabelList" : ["Past Adenoma"], "ValueList" : ["past Adenoma"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_LungRisks_Age_Option": { "ButtonLabelList" : ["55-80yo"], "ValueList" : ["age 55-80"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_LungRisks_Smoking_Option": { "ButtonLabelList" : ["30 PackYrs"], "ValueList" : ["30 or more pack years smoking history"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_LungRisks_Smoked_Past_15yrs_Option": { "ButtonLabelList" : ["Past 15yrs"], "ValueList" : ["smoked in past 15 years"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_BreastRisks_Age_Option": { "ButtonLabelList" : ["50-74yo"], "ValueList" : ["age 50-74"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_BreastRisks_Family_Option": { "ButtonLabelList" : ["Family Hx"], "ValueList" : ["family history of breast cancer"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},

    // Lipids
    "Prevention_Check_Lipids_Option": { "ButtonLabelList" : ["Lipids"], "ValueList" : ["Check Lipids"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},

    // Colon Cancer
    "Prevention_Hemoccult_Option": { "ButtonLabelList" : ["Hemoccult"], "ValueList" : ["Hemoccult for colon cancer screening"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_Colonoscopy_Option": { "ButtonLabelList" : ["Colonoscopy"], "ValueList" : ["Colonoscopy as outpatient"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},

    // Breast Cancer
    "Prevention_CheckBRCA_Option": { "ButtonLabelList" : ["BRCA"], "ValueList" : ["Check BRCA mutations"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},
    "Prevention_CheckMammogram_Option": { "ButtonLabelList" : ["Mammogram"], "ValueList" : ["Mammogram as outpatient"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},

    // Lung Cancer
    "Prevention_ChestCT_Option": { "ButtonLabelList" : ["Chest CT"], "ValueList" : ["Low power Chest CT for lung cancer screening"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},

    // Cervical Cancer
    "Prevention_Pap_Option": { "ButtonLabelList" : ["Pap Smear"], "ValueList" : ["Check Pap Smear as outpatient"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "PreventionPlan"},




    ///////////////////////////////////////////////////////////
    // Migraines
    ///////////////////////////////////////////////////////////
    "MigraineAuraModifier": { "ButtonLabelList" : ["Aura"], "ValueList" : [" with aura"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MigrainesPlan"},
    "MigraineNumMonthOption": { "ButtonLabelList" : ["Less 1/month", "1/month", "2-5/month", "5-10/month", "Over 10/month"], "ValueList" : ["Averages less than one headache per month", "Averages one headache per month", "Averages  2-5 headaches per month", "Averages 5-10 headaches per month", "Averages  over 10 headaches permonth"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MigrainesPlan"},
    "MigraineDurationOption": { "ButtonLabelList" : ["Last 1hr", "Last hours", "Last 1day", "Last days"], "ValueList" : ["Headaches typically last one hour", "Headaches typically last several hours", "Headaches typically last one day", "Headaches typically last days"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MigrainesPlan"},
    "MigraineUnilateralOption": { "ButtonLabelList" : ["Unilateral", "Bilateral"], "ValueList" : ["Unilateral", "Bilateral"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MigrainesPlan"},
    "MigrainePulsatileOption": { "ButtonLabelList" : ["Pulsatile", "Constant"], "ValueList" : ["throbbing", "constant"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MigrainesPlan"},
    "MigraineNauseaOption": { "ButtonLabelList" : ["Nausea"], "ValueList" : ["nausea"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MigrainesPlan"},
    "MigrainePhotophobiaOption": { "ButtonLabelList" : ["Photophobia"], "ValueList" : ["photophobia"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MigrainesPlan"},
    "MigraineHomeRegimenOption": { "ButtonLabelList" : ["Home-NSAIDs", "Home-Aimovig", "Home-Ajovy", "Home-Triptan", "Home-Ubrelvy", "Home-Nurtec"], "ValueList" : ["NSAIDs", "Aimovig (erenumab)", "Ajovy (fremanezumab)", "Sumatriptan", "Ubrelvy (ubrogepant)", "Nurtec (ubrogepant)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MigrainesPlan"},

    "MigraineBenadrylCompazineOption": { "ButtonLabelList" : ["Benadryl/Compazine"], "ValueList" : ["PRN Benadryl 25mg IV and Prochlorperazine 10mg IV Q12h"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MigrainesPlan"},
    "MigraineSumatriptanOption": { "ButtonLabelList" : ["Sumatriptan"], "ValueList" : ["PRN Sumatriptan 25mg PO"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MigrainesPlan"},
    "MigraineFiorocetOption": { "ButtonLabelList" : ["Fiorocet"], "ValueList" : ["PRN Fiorocet"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MigrainesPlan"},

    "MigrainePropranololOption": { "ButtonLabelList" : ["Propranolol"], "ValueList" : ["Propranolol 10mg PO daily for prevention"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MigrainesPlan"},
    "MigraineMagnesiumOption": { "ButtonLabelList" : ["Magnesium"], "ValueList" : ["Magnesium 400mg PO daily for prevention"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MigrainesPlan"},

    "MigraineDiaryOption": { "ButtonLabelList" : ["Diary"], "ValueList" : ["Counseled to keep a headache diary to identify frequency and possible triggers"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MigrainesPlan"},
    "MigraineEtOHOption": { "ButtonLabelList" : ["EtOH"], "ValueList" : ["alcohol"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MigrainesPlan"},
    "MigraineNicotineOption": { "ButtonLabelList" : ["Nicotine"], "ValueList" : ["nicotine"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MigrainesPlan"},
    "MigraineCaffeineOption": { "ButtonLabelList" : ["Caffeine"], "ValueList" : ["caffeine"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "MigrainesPlan"},



    // BILLING
    "BILLING_COMPLEXITY_EXACERBATION": { "ButtonLabelList" : ["Exacerbation"], "ValueList" : ["a severe exacerbation or progression of 1 or more chronic illnesses or with side effects of treatment"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_COMPLEXITY_PROGRESSION": { "ButtonLabelList" : ["Progression"], "ValueList" : ["acute illness or progression of a chronic illness that poses a threat to life or bodily function"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},

    "BILLING_DATA_INFLAMM_LABS": { "ButtonLabelList" : ["Labs-Inflamm"], "ValueList" : ["inflammatory markers (WBC, CRP, Procal)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_DATA_RENAL_LABS": { "ButtonLabelList" : ["Labs-Renal"], "ValueList" : ["renal function markers (Creatinine, BUN, potassium)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_DATA_LYTES_LABS": { "ButtonLabelList" : ["Labs-Lytes"], "ValueList" : ["electrolyte levels (Potassium, Magnesium, Phos, Calcium)"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},

    "BILLING_DATA_FAMILY": { "ButtonLabelList" : ["Ind History"], "ValueList" : ["independent historian"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},

    "BILLING_DATA_PERSONAL_EKG": { "ButtonLabelList" : ["EKG"], "ValueList" : ["EKG"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_DATA_PERSONAL_CXR": { "ButtonLabelList" : ["CXR"], "ValueList" : ["XRays"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_DATA_PERSONAL_CT": { "ButtonLabelList" : ["CT"], "ValueList" : ["CT Scans"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},

    "BILLING_DATA_DISCUSS": { "ButtonLabelList" : ["Consultant"], "ValueList" : ["Discussion of management with other physicians"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},

    "BILLING_RISK_OPIOIDS": { "ButtonLabelList" : ["IV Opioids"], "ValueList" : ["Parenteral controlled substances"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},

    "BILLING_RISK_TOXICITY": { "ButtonLabelList" : ["Toxicity"], "ValueList" : ["Drug therapy requiring intensive monitoring for toxicity"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_RISK_AKI": { "ButtonLabelList" : ["AKI"], "ValueList" : ["Drug therapy requiring monitoring for Acute Kidney Injury"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_RISK_BLEEDING": { "ButtonLabelList" : ["Bleeding"], "ValueList" : ["Anticoagulation requiring monitoring for signs of bleeding"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_RISK_IMMUNOSUPPRESSED": { "ButtonLabelList" : ["Infection"], "ValueList" : ["Titrating antimicrobials requiring monitoring for signs of infection in an immunosuppressed patient"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},

    "BILLING_RISK_ESCALATION": { "ButtonLabelList" : ["Escalation"], "ValueList" : ["Decision regarding escalation of hospital care"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_RISK_DNR": { "ButtonLabelList" : ["DNR"], "ValueList" : ["Decision to not resuscitate because of poor prognosis"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_REFERENCES_AMA": { "ButtonLabelList" : ["AMA Ref"], "ValueList" : ["Ref: CPT Evaluation and Management, https://www.ama-assn.org/system/files/2023-e-m-descriptors-guidelines.pdf"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},

    //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx    
    "BILLING_COMPLEXITY_CRITCARE_GENERAL": { "ButtonLabelList" : ["Critical Care"], "ValueList" : ["This patient has impairment of one or more vital organ systems such that there is a high probability of imminent or life threatening deterioration in the patient’s condition which requires direct personal management by the physician. The patient care involved high complexity decision making to assess, manipulate, and support vital system function(s) to treat single or multiple vital organ system failure and/or to prevent further life threatening deterioration of the patient’s condition."], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},

    //Critical care was time spent personally by me on the following activities: 
    "BILLING_COMPLEXITY_CRITCARE_HISTORY": { "ButtonLabelList" : ["History"], "ValueList" : ["obtaining history from patient or surrogate"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_COMPLEXITY_CRITCARE_EXAM": { "ButtonLabelList" : ["Examine"], "ValueList" : ["examination of patient"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_COMPLEXITY_CRITCARE_PLAN": { "ButtonLabelList" : ["Plan"], "ValueList" : ["development of treatment plan with patient or surrogate"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_COMPLEXITY_CRITCARE_CONSULTANTS": { "ButtonLabelList" : ["Consultants"], "ValueList" : ["discussions with consultants"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_COMPLEXITY_CRITCARE_RESPONSE": { "ButtonLabelList" : ["Response"], "ValueList" : ["evaluation of patient's response to treatment"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_COMPLEXITY_CRITCARE_ORDERS": { "ButtonLabelList" : ["Orders"], "ValueList" : ["ordering and performing treatments and interventions"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_COMPLEXITY_CRITCARE_ORDER_LABS": { "ButtonLabelList" : ["Labs"], "ValueList" : ["ordering and review of laboratory studies"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_COMPLEXITY_CRITCARE_CT": { "ButtonLabelList" : ["CT"], "ValueList" : ["ordering and review of radiographic studies and review of old charts"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_COMPLEXITY_CRITCARE_CXR": { "ButtonLabelList" : ["CXR"], "ValueList" : ["interpretation of Chest x-rays"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_COMPLEXITY_CRITCARE_PULSEOX": { "ButtonLabelList" : ["PulseOx"], "ValueList" : ["interpretation of Pulse oximetry"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_COMPLEXITY_CRITCARE_ABG": { "ButtonLabelList" : ["ABG"], "ValueList" : ["interpretation of Blood gases and collection and interpretation of physiologic data"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},
    "BILLING_COMPLEXITY_CRITCARE_IV": { "ButtonLabelList" : ["IV"], "ValueList" : ["vascular access procedures"], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},

    // "Total time spent by the provider providing critical care services was "
    "BILLING_COMPLEXITY_CRITCARE_TIME_SPENT": { "ButtonLabelList" : ["30 min", "45 min", "60 min"], "ValueList" : ["30 minutes.", "45 minutes.", "60 minutes."], "htmlButton" : null, "toggleBehavior" : "On/Disabled", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "BillingPlan"},


    //<><> INSERT HERE

}; // g_AllOptionsDeclaration




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FORMATTED STRING OUTPUTS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
var g_FormatStringsDeclaration = {
    "CKDCausesShowCrOption" : { FormatType: "Simple", "FormatString" : "Serum Creatinine={VAL}", "CPInputValueName" : "CKD_INPUT_CURRENT_CR", "CPInputRatioDenominatorValueName" : ""},
    "CKDCausesShowGFROption" : { FormatType: "Simple", "FormatString" : "baseline GFR={VAL}", "CPInputValueName" : "CKD_INPUT_CP_GFR", "CPInputRatioDenominatorValueName" : ""},
    "CKDCausesShowProtCrOption" : { FormatType: "Ratio", "FormatString" : "Urine Prot/Cr ratio is {RATIO} which suggests approximately {RATIO} grams daily proteinuria", "CPInputValueName" : "CKD_INPUT_URINE_PROTEIN", "CPInputRatioDenominatorValueName" : "CKD_INPUT_URINE_Cr"},
    "CKDCausesShowAlbCrOption" : { FormatType: "Ratio", "FormatString" : "and {RATIO} grams of the total daily proteinuria is albumin, the rest is all other proteins", "CPInputValueName" : "CKD_INPUT_URINE_ALBUMIN", "CPInputRatioDenominatorValueName" : "CKD_INPUT_URINE_Cr"},
    "DiabetesStatusShowA1cOption" : { FormatType: "Simple", "FormatString" : "Latest HgbA1c={VAL}", "CPInputValueName" : "Diabetes_A1c_CP_Input", "CPInputRatioDenominatorValueName" : ""},
}; // g_FormatStringsDeclaration






