/////////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////////
//
// This file generates the plan for each medical problem.
/////////////////////////////////////////////////////////////////////////////

var g_BASELINE_SOFA_SCORE = 0;
var g_CURRENT_SOFA_SCORE = 0;
var g_SOFA_DIFFERENNCES = "";

var INVALID_NUMBER = -31415927


//////////////////////////////////////////
// Globals, these just allow ComputeRiskOfESRD() to return two separate values.
var g_2YearESRDRisk = -1;
var g_5YearESRDRisk = -1;

var g_GFR_MDRD = 0;
var g_GFR_CockroftGault = 0;
var g_GFR_CKDEPI_CystatinC = 0;
var g_GFR_CKDEPI = 0;
var g_GFR_CKDEPI_Creatinine_CystatinC = 0;


////////////////////////////////////
var g_F160Info = {id:"F-160", name:"Fresenius Optiflux-160NR", UreaCl:["194", "266", "308", ""]}; 
var g_F180Info = {id:"F-180", name:"Fresenius Optiflux-180NR", UreaCl:["196", "274", "323", ""]}; 
var g_F200Info = {id:"F-200", name:"Fresenius Optiflux-200NR", UreaCl:["197", "277", "330", ""]}; 
var g_Exceltra170Info = {id:"Exceltra-170", name:"Baxter Exceltra-170", UreaCl:["196", "260", "310", "341"]}; 
var g_Exceltra190Info = {id:"Exceltra-190", name:"Baxter Exceltra-190", UreaCl:["197", "273", "323", "354"]}; 
var g_Exceltra210Info = {id:"Exceltra-210", name:"Baxter Exceltra-210", UreaCl:["199", "287", "350", "384"]}; 
var g_RevaclearInfo = {id:"Revaclear", name:"Baxter Revaclear", UreaCl:["196", "271", "321", "353"]}; 
var g_RevaclearMaxInfo = {id:"Revaclear-MAX", name:"Baxter Revaclear-MAX", UreaCl:["198", "282", "339", "376"]}; 

var g_BloodFlowList = ["300", "350", "400", "450", "500"]; 

var g_hisHer = "his";
var g_CapHisHer = "His";
var g_himHer = "him";
var g_CapHimHer = "His";
var g_heShe = "he";
var g_CapHeShe = "He";




////////////////////////////////////////////////////////////////////////////////
//
// [WriteCirrhosisPlan]
//
// Updated 2022-9-22 - Fixed calculators
// Updated 2022-1-18 - Added Transplant
// Updated 2020-12-20 - Fixed MELD, combine etiology labs into 1-line, add Hold Diuretics.
// Updated 2021-4-24 - Get all new user input values.
////////////////////////////////////////////////////////////////////////////////
function 
WriteCirrhosisPlan() {
    //LogEvent("Inside WriteCirrhosisPlan");
    var planNameStr = "Cirrhosis";
    var planConfigState = null;
    var activeControlPanel = null;
    var planStr = "";
    var subPlanActionList = [];
    var subsectionName = "";

    // <> May use "Hepatic Steatosis with Hepatic Fibrosis"
    var modifierStr = MedNote_GetCPOptionValue("CirrhosisPossibleOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planNameStr = modifierStr + " " + planNameStr;
    }

    MedNote_StartNewPlanSection(planNameStr, "CirrhosisPlan");
    planConfigState = g_AllPlansDeclaration['CirrhosisPlan'];
    if (!planConfigState) {
        return;
    }
    activeControlPanel = planConfigState.activeControlPanel;
    if (!activeControlPanel) {
        return;
    }

    if (MedNote_GetCPOptionBool("CirrhosisCoagulopathyOption")) {
        MedNote_AddRelatedProblem("Coagulopathy - Due to liver disease");
    }
    if (MedNote_GetCPOptionBool("CirrhosisThrombocytopeniaOption")) {
        MedNote_AddRelatedProblem("Thrombocytopenia - Due to liver disease");
    }

    WriteCommentIfSelected(activeControlPanel, "CirrhosisBiopsyRecordOption");
    WriteCommentIfSelected(activeControlPanel, "CirrhosisCauseOption");

    //////////////////////////////////////////////
    // Read user input values and calculate scores
    var currentCr = GetFloatInputForControlPanel(activeControlPanel, 'InputCreatinine_CP');
    var currentTBili = GetFloatInputForControlPanel(activeControlPanel, 'InputTBili_CP');
    var currentNa = GetFloatInputForControlPanel(activeControlPanel, 'InputSodium_CP');
    var currentAlbumin = GetFloatInputForControlPanel(activeControlPanel, 'InputAlbumin_CP');
    var currentINR = GetFloatInputForControlPanel(activeControlPanel, 'Cirrhosis_CP_Input_INR');
    var ascitesStr = GetStrInputForControlPanel(activeControlPanel, "Cirrhosis_Ascites_Modifier", null);
    var encephalopathyStr = GetStrInputForControlPanel(activeControlPanel, "Cirrhosis_Encephalopathy_Modifier", null);
    if (MedNote_GetCPOptionBool("CirrhosisMELDOption")) {
        //    ascitesScore = "none", "slight", "large"
        //    encephalopathy = "none", "grade 1", "grade 2"
        var MELDScore = MedNote_ComputeMELD(currentINR, currentNa, currentCr, currentTBili);
        if (MELDScore > 0) {
            scoreStr = "MELD-Na = " + MELDScore + " (";
            if (currentINR > 0) {
                scoreStr += "INR=" + currentINR;
            }
            if (currentNa > 0) {
                scoreStr += ", Na=" + currentNa;
            }
            if (currentCr > 0) {
                scoreStr += ", Cr=" + currentCr;
            }
            if (currentTBili > 0) {
                scoreStr += ", Tbili=" + currentTBili;
            }
            scoreStr = scoreStr + ")";

            if (MELDScore <= 9) {
                scoreStr = scoreStr + " (1.9 percent 3-month mortality)";
            } else if (MELDScore <= 19) {
                scoreStr = scoreStr + " (6.0 percent 3-month mortality)";
            } else if (MELDScore <= 29) {
                scoreStr = scoreStr + " (19.6 percent 3-month mortality)";
            } else if (MELDScore <= 39) {
                scoreStr = scoreStr + " (52.6 percent 3-month mortality)";
            } else {
                scoreStr = scoreStr + " (71.3 percent 3-month mortality)";
            }
            WriteComment(scoreStr);
            //SetStrOutputForControlPanel(activeControlPanel, 'MELD_CP', null, scoreStr);
        } // if (MELDScore > 0) {
        else {
            WriteComment("MELD Score = xxx");
        }

        var ChildPughStr = MedNote_ComputeChildPugh(currentAlbumin, currentINR, currentTBili, ascitesStr, encephalopathyStr);
        if (ChildPughStr) {
            scoreStr = "Child-Pugh = " + ChildPughStr + " (";
            if (currentAlbumin > 0) {
                scoreStr += "Alb=" + currentAlbumin;
            }
            if (currentINR > 0) {
                scoreStr += ", INR=" + currentINR;
            }
            if (currentTBili > 0) {
                scoreStr += ", Tbili=" + currentTBili;
            }
            scoreStr = scoreStr + ", ascites=" + ascitesStr + ", enceph=" + encephalopathyStr + ")";
            WriteComment(scoreStr);
            //SetStrOutputForControlPanel(activeControlPanel, 'ChildPugh_CP', null, 'Child-Pugh = ' + ChildPughStr);
        }
        //if (ChildPughStr) { WriteComment("Child-Pugh Class score = " + ChildPughStr);//        }
    } // if (MedNote_GetCPOptionBool("CirrhosisMELDOption")) {

    WriteActionIfSelected(activeControlPanel, "CirrhosisBiopsyOption");
    WriteActionIfSelected(activeControlPanel, "CirrhosisElastographyOption");

    //////////////////////////////
    // Etiology
    var optionNameList = [ "CirrhosisViralHepOption", "CirrhosisANAOption", "CirrhosisSmoothMuscleOption", 
                        "CirrhosisMitoOption", "CirrhosisFerritinOption", "CirrhosisCeruloplasmOption", 
                        "CirrhosisAntiTyypsinOption"];
    WriteListOfSelectedActions(activeControlPanel, "Workup etiology, check ", optionNameList)


    // Varices
    subPlanActionList = ["CirrhosisEGDResultOption", "CirrhosisGIBleedOption", "CirrhosisPropranololOption"];
    MedNode_WriteSubPlan("Varices", subPlanActionList)

    // Ascites
    subPlanActionList = ["CirrhosisParaResultOption", "CirrhosisDopplersOption", "CirrhosisExplainDiureticsOption",
                        "CirrhosisHoldDiureticsOption", "CirrhosisLasixOption", "CirrhosisSpironolactoneOption",
                        "CirrhosisSBPAntibioticsOption", "Cirrhosis2gNaDietOption"];
    MedNode_WriteSubPlan("Ascites", subPlanActionList)

    // Encephalopathy
    subPlanActionList = ["CirrhosisLactuloseOption", "CirrhosisRifaximinOption"];
    subsectionName = "Encephalopathy";
    // The West-Haven Classification Table
    planStr = MedNote_GetCPOptionValue("CirrhosisHEGradeOption");
    if ((planStr != null) && (planStr != "")) {
        subsectionName = subsectionName + " " + planStr;
    }
    MedNode_WriteSubPlan(subsectionName, subPlanActionList)

    // Coagulopathy
    subPlanActionList = ["CirrhosisNoBleedOption", "CirrhosisCheckINROption"];
    MedNode_WriteSubPlan("Coagulopathy", subPlanActionList)

    // Immunity
    subPlanActionList = ["CirrhosisHAVVaccineOption"];
    MedNode_WriteSubPlan("Immune Status", subPlanActionList);

    // HCC Screen
    subPlanActionList = ["CirrhosisShowHCCResultOption", "CirrhosisHCCShowAFPOption",
                        "CirrhosisHCCCheckAFPOption"];
    MedNode_WriteSubPlan("HCC/PVT screening", subPlanActionList);

    // NASH
    subPlanActionList = ["CirrhosisStatinOption", "CirrhosisVitEOption"];
    MedNode_WriteSubPlan("NASH", subPlanActionList)

    // Nutrition
    subPlanActionList = ["CirrhosisZincOption", "CirrhosisThiamineOption", "CirrhosisVitaminOption"];
    MedNode_WriteSubPlan("Nutrition", subPlanActionList)

    // Transplant
    subPlanActionList = ["CirrhosisStatusTransplantOption", "CirrhosisReferToTransplantOption"];
    MedNode_WriteSubPlan("Transplant", subPlanActionList)

    // Add any footer plans.
    if (MedNote_GetCPOptionBool("CirrhosisCoagulopathyOption")) {
        AddSingleLinePlanAtEnd("CirrhosisPlan", "Coagulopathy", "Due to liver disease, Monitor for bleeding");
    }
    if (MedNote_GetCPOptionBool("CirrhosisThrombocytopeniaOption")) {
        AddSingleLinePlanAtEnd("CirrhosisPlan", "Thrombocytopenia", "Due to liver disease, Monitor for bleeding");
    }
} // WriteCirrhosisPlan




////////////////////////////////////////////////////////////////////////////////
//
// [WriteApapPlan]
//
// Not Used
////////////////////////////////////////////////////////////////////////////////
function 
WriteApapPlan() {
    MedNote_StartNewPlanSection("Acetaminophen Toxicity", null);

    WriteComment("The patient consumed xxx tablets of xxx mg on xxx");
    WriteComment("On admission, at xxx, which was xxx hours after ingestion, the acetaminophen level was xxx");
    WriteComment("The time of ingestion is not known, so empirically treat with N-acetylcysteine per the 21-hour IV protocol");
    WriteComment("The time of ingestion is known, so check acetaminophen level 4 hours after admission, and according to Rumack-Matthew nomogram if level is over 150, then treat with N-acetylcysteine per the 21-hour IV protocol");
    WriteAction("N-acetylcysteine IV, give 150mg/kg in D5W once bolused over 1 hour, then 12.5 mg/kg/hr for 4 hours, then 6.25 mg/kg/hr");
    WriteAction("Continue N-acetylcysteine at 6.25 mg/kg/hr for at least a total of 19 hours from the time of the initial bolus");
    WriteAction("Check CMP and Acetaminophen level at 19 hours after starting N-acetylcysteine drip");
    WriteAction("You may stop the N-acetylcysteine drip when Acetaminophen level is undetectable, ALT and AST are both below 1000 and trending down, and the patient is stable");
    WriteAction("Check CMP and INR daily");
} // WriteApapPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteParathyroidectomyPlan]
//
// Not Used
////////////////////////////////////////////////////////////////////////////////
function 
WriteParathyroidectomyPlan() {
    MedNote_StartNewPlanSection("Parathyroidectomy", null);
    
    WriteComment("Surgery on ");
    WriteComment("There is risk of hungry bone syndrome leading to hypocalcemia.");

    WriteAction("Check ionized Calcium Q4h");
    WriteAction("Check PTH Q24h");

    WriteAction("Ca-Carbonate 750mg PO TID");
    WriteAction("Calcitriol 1mcg daily");
    WriteAction("PRN IV Calcium Gluconate");

    WriteComment("Ok to discharge home tomorrow if no IV calcium needed in 24hrs");
} // WriteParathyroidectomyPlan






////////////////////////////////////////////////////////////////////////////////
//
// [WriteAcidBasePlan]
//
// Updated 2020-4-17
// Updated 2022-11-2
// 2023-11-14 - Combined workup labs into a single task
////////////////////////////////////////////////////////////////////////////////
function 
WriteAcidBasePlan() { 
    var planConfigState = null;
    var activeControlPanel = null;
    var str;
    var anionGap = -1;
    var deltaBicarb = INVALID_NUMBER;
    var deltaGap = -1;
    var deltaPaCO2 = -1;
    var deltapH;
    var urineAnionGap = -1;
    var planStr = "";
    var deltaGapToDeltaBicarbRatio = -1;


    // Start the section
    planStr = MedNote_GetCPOptionValue("AcidBaseTypeOption");
    if ((null == planStr) || ("" == planStr)) {
        planStr = "Acid Base";        
    }
    MedNote_StartNewPlanSection(planStr, "AcidBasePlan");


    planConfigState = g_AllPlansDeclaration['AcidBasePlan'];
    if (!planConfigState) {
        return;
    }
    activeControlPanel = planConfigState.activeControlPanel;
    if (!activeControlPanel) {
        return;
    }


    ////////////////////////////////
    // Get all input values
    var currentNa = GetFloatInputForControlPanel(activeControlPanel, 'InputNa_CP');
    var currentCl = GetFloatInputForControlPanel(activeControlPanel, 'InputCl_CP');
    var currentBicarb = GetFloatInputForControlPanel(activeControlPanel, 'InputBicarb_CP');
    var currentAlbumin = GetFloatInputForControlPanel(activeControlPanel, 'InputAlbumin_CP');
    var currentpH = GetFloatInputForControlPanel(activeControlPanel, 'InputpH_CP');
    var currentPaCO2 = GetFloatInputForControlPanel(activeControlPanel, 'InputPaCO2_CP');
    var currentUrineNa = GetIntInputForControlPanel(activeControlPanel, 'InputUrineNa_CP');
    var currentUrineK = GetIntInputForControlPanel(activeControlPanel, 'InputUrineK_CP');
    var currentUrineChloride = GetIntInputForControlPanel(activeControlPanel, 'InputUrineCl_CP');

    ////////////////////////////////
    // Compute derived values
    if (currentBicarb > 0) {
        deltaBicarb = currentBicarb - 24;
    }
    if ((currentNa > 0) && (currentCl > 0) && (currentBicarb > 0)) {
        anionGap = currentNa - (currentCl + currentBicarb);
        SetStrOutputForControlPanel(activeControlPanel, 'ResultAnionGap_CP', null, 'AnionGap=' + anionGap);

        deltaGap = anionGap - 12;
        deltaGapToDeltaBicarbRatio = deltaGap / (-deltaBicarb);
        // Round to 1 decimal place
        deltaGapToDeltaBicarbRatio = Math.round(deltaGapToDeltaBicarbRatio * 10) / 10;
    }
    if (currentPaCO2 > 0) {
        deltaPaCO2 = currentPaCO2 - 40;
    }
    if ((currentUrineNa > 0) && (currentUrineK > 0) && (currentUrineChloride > 0)) {
        urineAnionGap = (currentUrineNa + currentUrineK) - currentUrineChloride;
        SetStrOutputForControlPanel(activeControlPanel, 'ResultUrineAnionGap_CP', null, 
                    'Urine Anion Gap=' + urineAnionGap);
    }


    ////////////////////////////////
    // pH
    if (MedNote_GetCPOptionBool("AcidBaseShowpHOption")) {
        str = AppendNumberToString("The serum pH on an ABG is ", currentpH);
        WriteComment(str);
        if (MedNote_GetCPOptionBool("AcidBaseInterpretpHOption")) {
            if (currentpH < 7.4) {
                WriteComment("This is a primary acidosis, since compensation will only partially restore the pH to 7.35-7.45");
            } else { // if (currentpH >= 7.4) {            
                WriteComment("This is a primary alkalosis, since compensation will only partially restore the pH to 7.35-7.45");
            }
        }
    } // if (MedNote_GetCPOptionBool("AcidBaseShowpHOption"))



    ////////////////////////////////
    // Bicarb and Anion Gap
    str = "";
    if (MedNote_GetCPOptionBool("AcidBaseBicarbOption")) {
        str = AppendNumberToString("The serum Bicarbonate is ", currentBicarb);
        str = str + "   ";
    } // if (MedNote_GetCPOptionBool("AcidBaseBicarbOption"))
    if (MedNote_GetCPOptionBool("AcidBaseAnionGapOption")) {
        if ((currentNa > 0) && (currentCl > 0) && (currentBicarb > 0)) {
            str = str + "The anion gap is " + anionGap;
        } else {
            str = str + "The anion gap is xxxx";
        }
        if (MedNote_GetCPOptionBool("AcidBaseAdjustedAnionGapOption")) {
            str = str + " (or ";
            if ((currentNa > 0) && (currentCl > 0) && (currentBicarb > 0) && (currentAlbumin > 0)) {
                var adjustedAnionGap = anionGap + (2.5 * (4.0 - currentAlbumin));
                str = str + adjustedAnionGap;
            } else {
                str = str + "xxx";
            }
            str = str + " when adjusted for albumin";
            if (currentAlbumin > 0) {
                str = str + " of " + currentAlbumin;
            }
            str = str + ")";        
        } // if (MedNote_GetCPOptionBool("AcidBaseAdjustedAnionGapOption"))
    } // if (MedNote_GetCPOptionBool("AcidBaseAnionGapOption"))
    if (str != "") {
        WriteComment(str);
    }



    ////////////////////////////////
    // Delta-Delta
    if (MedNote_GetCPOptionBool("AcidBaseDeltaDeltaOption")) {
        str = "The delta Bicarb is ";
        if (deltaBicarb != INVALID_NUMBER) {
            str += deltaBicarb;
        }
        str += " and the delta anion gap is " + deltaGap + " (assuming max normal gap is 12)";
        WriteComment(str);

        str = "The ratio of delta-Gap / delta-Bicarb is " + deltaGapToDeltaBicarbRatio;
        WriteComment(str);

        if (deltaGapToDeltaBicarbRatio > 0) {
            if (deltaGapToDeltaBicarbRatio < 1) {
                WriteComment("The ratio is less than 1, so there is likely a non-gap acidosis");
            } else if (deltaGapToDeltaBicarbRatio < 2) {
                WriteComment("The ratio is between 1 and 2, so there is likely no other non-gap acidosis");
            } else {
                WriteComment("The ratio is over 2, so there is likely also a metabolic alkalosis in addition to the acidosis");
            }
        } // if (deltaGapToDeltaBicarbRatio > 0)
    } // if (MedNote_GetCPOptionBool("AcidBaseDeltaDeltaOption"))



    ////////////////////////////////
    // Signs
    WriteCommentIfSelected(activeControlPanel, "AcidBaseLactateOption");
    WriteCommentIfSelected(activeControlPanel, "AcidBasePaCO2Option");
    if (MedNote_GetCPOptionBool("AcidBaseShowUrineLytesOption")) {
        str = "Urine Anion Gap (Na + K - Cl) is ";
        if ((currentUrineNa > 0) && (currentUrineK > 0) && (currentUrineChloride > 0)) {
            str = str + urineAnionGap;
            str = str + ", (" + currentUrineNa + " + " + currentUrineK + " - " + currentUrineChloride + ")";
        } else {
            str = str + "xxx";
        }
        WriteComment(str);

        if ((currentUrineNa > 0) && (currentUrineK > 0) && (currentUrineChloride > 0)) {
            if (urineAnionGap <= 0) {
                WriteComment("The urine anion gap is negative, so this is appropriate renal compensation");
            } else {
                WriteComment("The urine anion gap is positive, which suggests a renal tubular acidosis");
            }
        }
    } // if (MedNote_GetCPOptionBool("AcidBaseShowUrineLytesOption"))

    if (MedNote_GetCPOptionBool("AcidBaseExplainUrineLytesOption")) {
        WriteComment("Urine anion gap estimates urine ammonia excretion.");
        WriteComment("The kidneys will excrete NaCl, KCl, and when there is acidosis, NH4Cl. The anion gap really estimates the amount of urine Chloride that is not part of NaCl and KCl, which is roughly the same as the amount of NH4Cl. So, a negative urine anion gap means there is excess Cl- ions, which means the kidneys are excreting NH4 in the form of NH4Cl.");
        WriteComment("The urine anion gap should be negative during acidosis, and this is appropriate renal compensation by excreting excess acid as ammonia. If the gap is positive in a metabolic acidosis, then this is inappropriate, and the kidney itself may be the cause of the acidodis.");
    }

    if (MedNote_GetCPOptionBool("AcidBaseShowUClOption")) {
        str = AppendNumberToString("Urine Cl is ", currentUrineChloride);
        WriteComment(str);

        if (currentUrineChloride > 0) {
            if (currentUrineChloride <= 15) {
                WriteComment("The kidney is trying to conserve fluid, so suspect fluid loss, such as vomiting, diarrhea, burns, NG suction, and more");
            } else {
                WriteComment("Urine Cl is high, so suspect renal loss, such as Diuretics, excess Aldosterone, intrinsic renal defect (Liddle, Gittleman, Bartter)");
            }
        }
    }

    if (MedNote_GetCPOptionBool("AcidBaseExplainUClOption")) {
        WriteComment("In alkalosis, the kidneys waste HCO3, but this is an ion so they waste Na-HCO3. As a result, we cannot measure urine sodium or FENa to assess volume status. But, if urine Cl is low, then the kidneys are conserving volume (in the form of NaCl and H2O) even if they are wasting bicarb (in the form of NaHCO3)");
        WriteComment("If Urine Cl is under 15, then the kidney is trying to conserve fluid and you should suspect total body fluid loss, such as vomiting, diarrhea, burns, NG suction, and more");
        WriteComment("If Urine Cl is over 15, then suspect renal loss, such as Diuretic, excess Aldosterone, intrinsic renal defect (Liddle, Gittleman, Bartter)");
    }
    WriteCommentIfSelected(activeControlPanel, "AcidBasePotassiumRTAOption");
    WriteCommentIfSelected(activeControlPanel, "AcidBaseShowCKOption");
    WriteCommentIfSelected(activeControlPanel, "AcidBaseUrineKetonesOption");

    if (MedNote_GetCPOptionBool("AcidBaseDeltapHOption")) {
        str = "The pH is ";
        if (currentpH > 0) {
            deltaPH = currentpH - 7.4
            // Round to 2 decimal places
            deltaPH = Math.round(deltaPH * 100) / 100;
            str += currentpH + ", delta pH is " + deltaPH;
        } else {
            str += "xxx";
        }
        str += AppendNumberToString(", PaCO2 is ", currentPaCO2);
        str += " and delta PaCO2 is ";
        if (currentPaCO2 > 0) {
            str += (currentPaCO2 - 40);
        } else {
            str += "xxx";
        }
        WriteComment(str);
    }
    if (MedNote_GetCPOptionBool("AcidBaseRespAcuteChronicOption")) {
        WriteComment("In an acute Respiratory change (either Alkalosis or Acidosis), delta-pH = 0.008 * delta-PaCO2. The pH changes more because there is initially less compensation.");
        WriteComment("In a Chronic Respiratory change (either Alkalosis or Acidosis), delta-pH = 0.003 * delta-PaCO2. The pH changes less because there is eventually more compensation.");
    }
    if (MedNote_GetCPOptionBool("AcidBaseExplainOsmGapOption")) {
        WriteComment("Predicted serum osm is ((2 * Na) + (Glc / 18) + (BUN / 2.8) + (EtOH / 3.7))");
        WriteComment("If Osmolar gap is over 10, then consider MeOH or Ethylene Glycol. Give empiric Fomeprazole");
    }



    ////////////////////////////////
    // Compensation
    if (MedNote_GetCPOptionBool("AcidBaseMetAcidCompOption")) {
        var predictedPaCO2 = -1;

        WriteComment("In Metabolic Acidosis, PaCO2 should be (1.5 * bicarb) + 8 +- 2 (Winters Formula)");
        str = AppendNumberToString("The actual PaCO2 is ", currentPaCO2);
        str = str + " and should be in the range ";
        if (currentBicarb > 0) {
            predictedPaCO2 = (1.5 * currentBicarb) + 8;
            str += (predictedPaCO2 - 2) + "-" + (predictedPaCO2 + 2);
        } else {
            str += "xxx";
        }        
        WriteComment(str);

        if ((predictedPaCO2 > 0) && (currentPaCO2 > 0)) {
            if (currentPaCO2 > (predictedPaCO2 + 2)) {
                WriteComment("This is not a compensated metabolic acidosis, there may also be a respiratory acidosis");
            } else if (currentPaCO2 < (predictedPaCO2 - 2)) {
                WriteComment("This is not a compensated metabolic acidosis, there may also be a respiratory alkalosis");
            } else {
                WriteComment("This is a compensated metabolic acidosis");
            }
        } // if ((predictedPaCO2 > 0) && (currentPaCO2 > 0))
    } // if (MedNote_GetCPOptionBool("AcidBaseMetAcidCompOption"))


    if (MedNote_GetCPOptionBool("AcidBaseMetAlkCompOption")) {
        var predictedPaCO2 = -1;

        WriteComment("In Metabolic Alkalosis, PaCO2 should be 40 + (0.7 * delta-bicarb)");
        // This estimate only works to a max PaCO2 is approx 55mm Hg");

        str = AppendNumberToString("The actual PaCO2 is ", currentPaCO2);
        str = str + " and should be approximately ";
        if (deltaBicarb != INVALID_NUMBER) {
            predictedPaCO2 = 40 + (0.7 * deltaBicarb);
            str += predictedPaCO2;
        } else {
            str += "xxx";
        }        
        WriteComment(str);

        if ((predictedPaCO2 > 0) && (currentPaCO2 > 0)) {
            if (currentPaCO2 > (predictedPaCO2 + 2)) {
                WriteComment("This is not a compensated metabolic alkalosis, there may also be a respiratory acidosis");
            } else if (currentPaCO2 < (predictedPaCO2 - 2)) {
                WriteComment("This is not a compensated metabolic acidosis, there may also be a respiratory alkalosis");
            } else {
                WriteComment("This is a compensated metabolic alkalosis");
            }
        } // if ((predictedPaCO2 > 0) && (currentPaCO2 > 0))
    } // if (MedNote_GetCPOptionBool("AcidBaseMetAlkCompOption"))


    if (MedNote_GetCPOptionBool("AcidBaseRespAcidCompOption")) {
        var predictedBicarb = -1;

        WriteComment("In Respiratory Acidosis, serum bicarb will eventually rise 3mEq for every increase of 10mm in PaCO2 (acutely it rises only 1mEq).");

        str = AppendNumberToString("The actual bicarb is ", currentBicarb);
        str = str + " and is predicted to be approximately ";
        // Check currentPaCO2, not deltaPaCO2. They will both either be valid
        // or invalid, but deltaPaCO2 may legitamately be negative.
        if (currentPaCO2 > 0) {
            predictedBicarb = 24 + (3 * (deltaPaCO2 / 10));
            str = str + predictedBicarb;
        } else {
            str = str + "xxx";
        }        
        WriteComment(str);

        if ((predictedBicarb > 0) && (currentBicarb > 0)) {
            if (currentBicarb > (predictedBicarb + 2)) {
                WriteComment("This is not a compensated respiratory acidosis, there may also be a metabolic alkalosis ");
            } else if (predictedBicarb < (currentBicarb - 2)) {
                WriteComment("This is not a compensated respiratory acidosis, there may also be a metabolic acidosis");
            } else {
                WriteComment("This is a compensated respiratory acidosis");
            }
        } // if ((predictedPaCO2 > 0) && (currentPaCO2 > 0))
    } // if (MedNote_GetCPOptionBool("AcidBaseRespAcidCompOption"))


    if (MedNote_GetCPOptionBool("AcidBaseRespAlkCompOption")) {
        var predictedBicarb = -1;
        //LogEvent("Inside the Resp Alk section");
        //LogEvent("deltaPaCO2 = " + deltaPaCO2);
        //LogEvent("currentPaCO2 = " + currentPaCO2);

        WriteComment("In Respiratory Alkalosis, serum bicarb drops 4mEq for every decrease of 10mm in PaCO2 (acutely it drops only 2mEq)");

        str = AppendNumberToString("The actual bicarb is ", currentBicarb);
        str = str + " and is predicted to be approximately ";
        // Check currentPaCO2, not deltaPaCO2. They will both either be valid
        // or invalid, but deltaPaCO2 may legitamately be negative.
        if (currentPaCO2 > 0) {
            predictedBicarb = 24 - (4 * (deltaPaCO2 / 10));
            str = str + predictedBicarb;
        } else {
            str = str + "xxx";
        }        
        WriteComment(str);

        if ((predictedBicarb > 0) && (currentBicarb > 0)) {
            if (currentBicarb > (predictedBicarb + 2)) {
                WriteComment("This is not a compensated respiratory alkalosis, there may also be a metabolic alkalosis");
            } else if (currentBicarb < (predictedBicarb - 2)) {
                WriteComment("This is not a compensated respiratory alkalosis, there may also be a metabolic acidosis");
            } else {
                WriteComment("This is a compensated respiratory alkalosis");
            }
        } // if ((predictedPaCO2 > 0) && (currentPaCO2 > 0))
    } // if (MedNote_GetCPOptionBool("AcidBaseRespAlkCompOption"))


    ////////////////////////////////
    // Processes
    var optionNameList = [ "AcidBaseMetGapAcidProcessOption", "AcidBaseMetNonGapAcidProcessOption", "AcidBaseMetAlkProcessOption", "AcidBaseRespAcidProcessOption", "AcidBaseRespAlkProcessOption"];
    WriteListOfSelectedValues(activeControlPanel, "There is a ", false, "", optionNameList, "")

    ////////////////////////////////
    // Gap Acidosis Diff
    var optionNameList = [ "AcidBaseDiffIschemiaOption", "AcidBaseDiffUremiaOption", "AcidBaseDiffDKAOption", "AcidBaseDiffEtOHOption", 
                            "AcidBaseDiffStarvationOption", "AcidBaseDiffPropofolOption", 
                            "AcidBaseDiffLinezolidOption", "AcidBaseDiffAtivanDripOption", "AcidBaseDiffMetforminOption", 
                            "AcidBaseDiffTenofovirOption", "AcidBaseDiffSalicylateOption", 
                            "AcidBaseDiffAcetaminophenOption", "AcidBaseDiffRhabdoOption", "AcidBaseDiffEthyleneGlycolOption", "AcidBaseDiffMethylAlcoholOption", "AcidBaseDiffDLactateOption", 
                            "AcidBaseDiffIsoniazidOption", "AcidBaseDiffMyelomaOption", "AcidBaseDiffIronOption"];
    WriteListOfSelectedValues(activeControlPanel, "Possible causes of the Anion Gap metabolic acidosis include: ", false, "", optionNameList, "")

    ////////////////////////////////
    // Non-Gap Acidosis Diff
    optionNameList = [ "AcidBaseDiffDiarrheaOption", "AcidBaseDiffDilutionalOption", "AcidBaseDiffCKDOption", "AcidBaseDiffRTAIVOption",
                        "AcidBaseDiffRTA2Option", "AcidBaseDiffRTA1Option", "AcidBaseDiffRespAlkalosisOption"];
    WriteListOfSelectedValues(activeControlPanel, "Possible causes of the non-gap metabolic acidosis include: ", false, "", optionNameList, "")

    ////////////////////////////////
    // RTA I Diff
    optionNameList = [ "AcidBaseDiffAcetazolamideOption", "AcidBaseDiffTopiramateOption", 
                        "AcidBaseDiffObstructiveUropathyOption", "AcidBaseDiffSjögrenOption", "AcidBaseDiffRheumatoidOption", 
                        "AcidBaseDiffLupusOption", "AcidBaseDiffSickleCellOption", "AcidBaseDiffPrimaryBiliaryCirrhosisOption", 
                        "AcidBaseDiffChronicUTIOption", "AcidBaseDiffAmphotericinOption", "AcidBaseDiffTolueneOption"];
    WriteListOfSelectedValues(activeControlPanel, "Possible causes of the Renal Tubular Acidosis type I include: ", false, "", optionNameList, "")

    ////////////////////////////////
    // RTA II Diff
    optionNameList = [ "AcidBaseRTAIDiffMultipleMyelomaOption", "AcidBaseRTAIDiffAcetazolamideOption", "AcidBaseRTAIDiffIfosfamideOption", 
                        "AcidBaseRTAIDiffTenofovirOption", "AcidBaseDiffWilsonOption" ];
    WriteListOfSelectedValues(activeControlPanel, "Possible causes of the Renal Tubular Acidosis type II (Fanconi) include: ", false, "", optionNameList, "")

    ////////////////////////////////
    // RTA IV Diff
    optionNameList = [ "AcidBaseRTAIVDiffDiabetesOption", "AcidBaseRTAIVDiffSpironolactoneOption", "AcidBaseRTAIVDiffACEInhibitorsOption", 
                        "AcidBaseRTAIVDiffTrimethoprimOption", "AcidBaseRTAIVDiffNSAIDsOption", "AcidBaseRTAIVDiffAddisonOption", 
                        "AcidBaseRTAIVDiffsickleCellOption", 
                        "AcidBaseRTAIVDiffLupusOption", "AcidBaseRTAIVDiffAmyloidosisOption", "AcidBaseRTAIVDiffPentamidineOption" ];
    WriteListOfSelectedValues(activeControlPanel, "Possible causes of the Renal Tubular Acidosis type IV include: ", false, "", optionNameList, "")

    ////////////////////////////////
    // Metabolic Alkalosis Diff
    optionNameList = [ "AcidBaseDiffDiureticsOption", "AcidBaseDiffVolumeLossOption", "AcidBaseDiffPoorPOOption", "AcidBaseDiffHypercalcemiaOption",
                        "AcidBaseDiffHypokalemiaOption", "AcidBaseDiffHypercapnicCompensationOption", "AcidBaseDiffHyperAldoOption", 
                        "AcidBaseDiffCushingsOption",
                        "AcidBaseDiffLiddleOption", "AcidBaseDiffGlucocorticoidRemedialHyperaldoOption"];
    WriteListOfSelectedValues(activeControlPanel, "Possible causes of the metabolic alkalosis include: ", false, "", optionNameList, "")

    ////////////////////////////////
    // Resp Acidosis Diff
    optionNameList = [ "AcidBaseDiffRespAcidCOPDOption", "AcidBaseDiffSedationOption" ];
    WriteListOfSelectedValues(activeControlPanel, "Possible causes of the Respiratory acidosis include: ", false, "", optionNameList, "")

    ////////////////////////////////
    // Resp Alkalosis Diff
    optionNameList = [ "AcidBaseDiffHypoxiaOption", "AcidBaseDiffPainTachypneaOption", "AcidBaseDiffPulmRestrictOption"];
    WriteListOfSelectedValues(activeControlPanel, "Possible causes of the Respiratory Alaklosis include: ", false, "", optionNameList, "")



    ////////////////////////////////
    // General Workup
    var optionNameList = [ 'AcidBaseCheckVBGOption', 'AcidBaseUrinepHOption', 'AcidBaseCheckLactateOption',
                            'AcidBaseCheckCKOption',  'AcidBaseCheckUrineLytesOption', 'AcidBaseCheckAldoReninOption',
                            'AcidBaseCheckUClOption']; 
    WriteListOfSelectedActions(activeControlPanel, "Check ", optionNameList)


    ////////////////////////////////
    // Gap Acidosis Workup
    if (MedNote_GetCPOptionBool("AcidBaseCheckOsmGapOption")) {
        WriteAction("Check volatile alcohol screen (MeOH, Isopropyl, EtOH)");
        WriteAction("Check Osmolar gap: serum Osm to rule out alcohol intoxication");
    }

    ////////////////////////////////
    // Treat
    WriteActionIfSelected(activeControlPanel, 'AcidBasePOBicarbOption');
    WriteActionIfSelected(activeControlPanel, 'AcidBaseIVBicarbOption');
    WriteActionIfSelected(activeControlPanel, 'AcidBaseIVBolussOption');
    WriteActionIfSelected(activeControlPanel, 'AcidBaseIVFluidsOption');
    WriteActionIfSelected(activeControlPanel, 'AcidBaseThiamineOption');
    WriteActionIfSelected(activeControlPanel, 'AcidBaseAcetazolamideOption');
} // WriteAcidBasePlan





////////////////////////////////////////////////////////////////////////////////
//
// [AppendNumberToString]
//
////////////////////////////////////////////////////////////////////////////////
function 
AppendNumberToString(startStr, numValue) { 
    if (numValue >= 0) {
        return(startStr + numValue);
    } else {
        return(startStr + "xxx");
    }
} // AppendNumberToString





////////////////////////////////////////////////////////////////////////////////
//
// [WriteCHFPlan]
//
// *** Check urine Chloride, daily
//
// Updated 2023-10-31 - Implemented core plan as 5 groups: BB, ACE/ARB, SGLT2, MRA, Diuresis
////////////////////////////////////////////////////////////////////////////////
function 
WriteCHFPlan() {
    //LogEvent("WriteCHFPlan");
    var planConfigState;
    var modifierStr;
    var planNameStr = "Heart Failure";
    var stageStr;
    var LVEF = -1;
    var LVEFStr = null;
    var str;
    var activeControlPanel = null;


    ///////////////////////////
    // Start the section
    modifierStr = MedNote_GetCPOptionValue("CHFAcuteChronicOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planNameStr = modifierStr + planNameStr;
    }
    modifierStr = MedNote_GetCPOptionValue("CHFHFrEFOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planNameStr = planNameStr + ", " + modifierStr;
    }
    modifierStr = MedNote_GetCPOptionValue("CHFIschemicOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planNameStr = planNameStr + ", " + modifierStr;
    } 
   modifierStr = MedNote_GetCPOptionValue("CHFSystolicOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planNameStr = planNameStr + ", " + modifierStr;
    }
    modifierStr = MedNote_GetCPOptionValue("CHFLeftSideOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planNameStr = planNameStr + ", " + modifierStr;
    }
    MedNote_StartNewPlanSection(planNameStr, "CHFPlan");

    // Get the control panel. 
    // This was set up by the call to MedNote_StartNewPlanSection.
    planConfigState = g_AllPlansDeclaration['CHFPlan'];
    activeControlPanel = planConfigState.activeControlPanel;
    if (!activeControlPanel) {
        LogEvent("WriteCHFPlan. activeControlPanel is null");
        return;
    }

    ///////////////////////////////
    // Staging
    LVEF = GetIntInputForControlPanel(activeControlPanel, 'InputLVEF_CP');
    LVEFStr = GetStrInputForControlPanel(activeControlPanel, 'InputLVEF_CP');
    stageStr = MedNote_GetCPOptionValue("CHFNYHAOption");
    modifierStr = MedNote_GetCPOptionValue("CHFACCStageOption");
    if ((stageStr != null) && (stageStr != "")) {
        if ((modifierStr != null) && (modifierStr != "")) {
            stageStr = stageStr + ", " + modifierStr;
        }
    } else {
        stageStr = modifierStr;
    }
    if (MedNote_GetCPOptionBool("CHFLVEFOption")) {
        modifierStr = MedNote_GetCPOptionValue("CHFLVEFOption");
        if (LVEFStr) {
            modifierStr = modifierStr + LVEFStr + "%";
        } 
        if ((stageStr != null) && (stageStr != "")) {
            stageStr = stageStr + ", " + modifierStr;
        } else {
            stageStr = modifierStr;
        }

    }
    if ((stageStr != null) && (stageStr != "")) {
        WriteComment(stageStr);
    }
    WriteCommentIfSelected(activeControlPanel, 'CHFNotExacerbationOption');


    ///////////////////////////////
    // Vitals
    // Urine out
    planStr = MedNote_GetCPOptionValue("CHFUrineOutOption");
    if ((planStr != null) && (planStr != "")) {
        WriteComment(planStr);
    }
    // Weight and trend
    planStr = MedNote_GetCPOptionValue("CHFWeightOption");
    modifierStr = MedNote_GetCPOptionValue("CHFBaseWeightOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        if ((planStr != null) && (planStr != "")) {
            planStr += ", " + modifierStr;
        } else {
            planStr = modifierStr;
        }
    }
    if ((planStr != null) && (planStr != "")) {
        WriteComment(planStr);
    }
    // O2 requirements
    planStr = MedNote_GetCPOptionValue("CHFO2NeededOption");
    modifierStr = MedNote_GetCPOptionValue("CHFHomeO2Option");
    if ((modifierStr != null) && (modifierStr != "")) {
        if ((planStr != null) && (planStr != "")) {
            planStr += ", " + modifierStr;
        } else {
            planStr = modifierStr;
        }
    }
    if ((planStr != null) && (planStr != "")) {
        WriteComment(planStr);
    }


    ///////////////////////////////
    // Past Workup
    if (MedNote_GetCPOptionBool("CHFShowEchoOption")) {
        WriteComment("Latest Echocardiogram showed: ");
    }
    if (MedNote_GetCPOptionBool("CHFShowBNPOption")) {
        WriteComment("BNP on admission: ");
    }
    if (MedNote_GetCPOptionBool("CHFShowXRayOption")) {
        WriteComment("Latest Chest XRay: ");
    }
    WriteCommentIfSelected(activeControlPanel, 'CHFHomeMedsOption');


    ////////////////////////////////
    // Exacerbation Triggers
    var optionNameList = [ "CHFTriggerDietOption", "CHFTriggerComplianceOption", "CHFTriggerMedChangesOption", "CHFTriggerAKIOption", "CHFTriggerFluidsOption" ];
    WriteListOfSelectedValues(activeControlPanel, "Possible triggers for this exacerbation include: ", false, "", optionNameList, "")

    ///////////////////////////////
    // New Workup
    WriteActionIfSelected(activeControlPanel, 'CHFXrayOption');
    WriteActionIfSelected(activeControlPanel, 'CHFGetBNPOption');
    WriteActionIfSelected(activeControlPanel, 'CHFGetEchoOption');


    // Beta Blockers
    var optionNameList = [ 'CHFMetoprololTarOption', 'CHFMetoprololSuccOption', 'CHFCarvedilolOption',
            'CHFNSBBOption', 'CHFNoBetaBlockerOption']; 
    WriteListOfSubActions("Beta Blockade", optionNameList)

    // ACE/ARB
    var optionNameList = [ 'CHFLisinoprilOption', 'CHFLosartanOption', 'CHFARNIOption',
            'CHFNoACEARBOption']; 
    WriteListOfSubActions("Angiotensin Blockade", optionNameList)

    // SGLT2
    var optionNameList = [ 'CHFSGLT2DapagliflozinOption', 'CHFSGLT2EmpagliflozinOption', 
            'CHFSGLT2ReduceInsulinOption', 'CHFSGLT2ExplainGFRDropOption', 'CHFNoSGLT2Option']; 
    WriteListOfSubActions("SGLT2 Inhibitor", optionNameList)

    // MRA
    var optionNameList = [ 'CHFSpironiolactoneOption', 'CHFNoMRAOption']; 
    WriteListOfSubActions("Aldo Blockade", optionNameList)

    // Diuresis
    var optionNameList = [ 'CHFLasixIVOption', 'CHFLasixPOOption', 'CHFTorsemideOption',
            'CHFBumexOption', 'CHFThiazideOption', 'CHFNoDiureticOption']; 
    WriteListOfSubActions("Diuresis", optionNameList)

    ///////////////////////////////
    // ICD
    planStr = MedNote_GetCPOptionValue("CHFICDOption");
    modifierStr = MedNote_GetCPOptionValue("CHFICDIndicationsOption");
    if ((planStr != null) && (planStr != "") && (modifierStr != null) && (modifierStr != "")) {
        planStr += modifierStr;
    }
    if ((planStr != null) && (planStr != "")) {
        WriteAction(planStr);
    }

    ///////////////////////////////
    // Diet and Fluids
    WriteActionIfSelected(activeControlPanel, 'CHF2gNaDietOption');
    WriteActionIfSelected(activeControlPanel, 'CHFFluidRestrictOption');
    WriteActionIfSelected(activeControlPanel, 'CHFCompressionStockingsOption');
    WriteActionIfSelected(activeControlPanel, 'CHFDietEdOption');

    ///////////////////////////////
    // Monitoring
    WriteActionIfSelected(activeControlPanel, 'CHFIOOption');
    WriteActionIfSelected(activeControlPanel, 'CHFDailyWeightOption');
} // WriteCHFPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteHTNPlan]
//
// ACC 2017 Guidelines
// Patients with HFrEF and hypertension should be prescribed GDMT
// titrated to attain systolic blood pressure less than 130 mm Hg.
////////////////////////////////////////////////////////////////////////////////
function 
WriteHTNPlan() {
    var planStr = "";
    var planConfigState = null;
    var activeControlPanel = null;

    ///////////////////
    // HtnUrgency
    planStr = MedNote_GetCPOptionValue("HtnUrgency");
    if ((planStr == null) || (planStr == "")) {
        planStr = "Hypertension";
    }
    if (PrintSingleLinePlanAtEnd('HTNPlan', planStr, "Continue home medications: ")) {
        return
    }
    MedNote_StartNewPlanSection(planStr, "HTNPlan");

    // Get the control panel. 
    // This was set up by the call to MedNote_StartNewPlanSection.
    planConfigState = g_AllPlansDeclaration['HTNPlan'];
    activeControlPanel = planConfigState.activeControlPanel;
    if (!activeControlPanel) {
        LogEvent("WriteHTNPlan. activeControlPanel is null");
        return;
    }

    ///////////////////
    // Type
    WriteCommentIfSelected(activeControlPanel, 'HTNStageOption');
    WriteCommentIfSelected(activeControlPanel, 'HTNPrimaryOption');

    ///////////////////
    // Targets
    WriteCommentIfSelected(activeControlPanel, 'HTNACCTargetOption');
    WriteCommentIfSelected(activeControlPanel, 'HTNDiabetesTargetOption');
    WriteCommentIfSelected(activeControlPanel, 'HTNRenalTargetOption');
    WriteCommentIfSelected(activeControlPanel, 'HTNSprintTargetOption');
    WriteCommentIfSelected(activeControlPanel, 'HTNEmergencyTargetOption');
    WriteCommentIfSelected(activeControlPanel, 'HTNSepsisTargetOption');

    ///////////////////
    // Status
    WriteCommentIfSelected(activeControlPanel, 'HTNCurrentBPOption');
    WriteCommentIfSelected(activeControlPanel, 'HTNHomeMedsOption');

    ///////////////////
    // Calcium Channel Blockers
    WriteActionIfSelected(activeControlPanel, 'HTNAmlodipineOption');
    WriteActionIfSelected(activeControlPanel, 'HTNNifedipineOption');
    WriteActionIfSelected(activeControlPanel, 'HTNDiltiazemOption');

    ///////////////////
    // Diuresis
    WriteActionIfSelected(activeControlPanel, 'HTNThiazideOption');
    WriteActionIfSelected(activeControlPanel, 'HTNLasixPOOption');
    WriteActionIfSelected(activeControlPanel, 'HTNTorsemideOption');
    WriteActionIfSelected(activeControlPanel, 'HTNSeeCHFOption');

    ///////////////////
    // ACE/ARB
    WriteActionIfSelected(activeControlPanel, 'HTNLisinoprilOption');
    WriteActionIfSelected(activeControlPanel, 'HTNLosartanOption');
    WriteActionIfSelected(activeControlPanel, 'HTNSpironiolactoneOption');

    ///////////////////
    // Beta Blockers
    WriteActionIfSelected(activeControlPanel, 'HTNMetoprololTarOption');
    WriteActionIfSelected(activeControlPanel, 'HTNMetoprololSuccOption');
    WriteActionIfSelected(activeControlPanel, 'HTNCarvedilolOption');
    WriteActionIfSelected(activeControlPanel, 'HTNNSBBOption');

    ///////////////////
    // Last resort
    WriteActionIfSelected(activeControlPanel, 'HTNClonidineOption');
    WriteActionIfSelected(activeControlPanel, 'HTNHydralazineOption');

    ///////////////////
    WriteActionIfSelected(activeControlPanel, 'HTNPRNLabetalolOption');
    WriteActionIfSelected(activeControlPanel, 'HTNPRNClonidineOption');
    WriteActionIfSelected(activeControlPanel, 'HTNUFWithDialysisOption');

    ///////////////////
    WriteActionIfSelected(activeControlPanel, 'HTNMicroAlbuminOption');
    WriteActionIfSelected(activeControlPanel, 'HTNCheckAldoRenin');
    WriteActionIfSelected(activeControlPanel, 'HTNRASDopplers');
    WriteActionIfSelected(activeControlPanel, 'HTNRuleOutOSA');
    WriteActionIfSelected(activeControlPanel, 'HTNCheckTSHOption');

    ///////////////////
    WriteActionIfSelected(activeControlPanel, 'HTNNicardipine');
    WriteActionIfSelected(activeControlPanel, 'HTNNTG');
    WriteActionIfSelected(activeControlPanel, 'HTNCheckDrugsOption');
} // WriteHTNPlan







////////////////////////////////////////////////////////////////////////////////
//
// [WriteSepsisPlan]
//
// Updated 2020-5-1
////////////////////////////////////////////////////////////////////////////////
function 
WriteSepsisPlan() {
    var planStr = "";
    var modifierStr = "";
    var planConfigState = null;
    var activeControlPanel = null;
    var count = 0;
    var criteriaStr;
    var criteriaList;


    ///////////////////////////
    // Write the plan and related plans.
    planStr = "SIRS";
    modifierStr = MedNote_GetCPOptionValue("SepsisSepsisModifier");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr;
    }
    MedNote_StartNewPlanSection(planStr, "SepsisPlan");
    // Write related problems.
    modifierStr = MedNote_GetCPOptionValue("SepsisEndocarditisModifier");
    if ((modifierStr != null) && (modifierStr != "")) {
        MedNote_AddRelatedProblem(modifierStr);
    }
    modifierStr = MedNote_GetCPOptionValue("SepsisPulmEmboliModifier");
    if ((modifierStr != null) && (modifierStr != "")) {
        MedNote_AddRelatedProblem(modifierStr);
    }
    modifierStr = MedNote_GetCPOptionValue("SepsisUTIModifier");
    if ((modifierStr != null) && (modifierStr != "")) {
        MedNote_AddRelatedProblem(modifierStr);
    }
    modifierStr = MedNote_GetCPOptionValue("SepsisPneumoniaModifier");
    if ((modifierStr != null) && (modifierStr != "")) {
        MedNote_AddRelatedProblem(modifierStr);
    }

    //////////////////////////
    // Get the control panel. 
    // This was set up by the call to MedNote_StartNewPlanSection.
    planConfigState = g_AllPlansDeclaration['SepsisPlan'];
    activeControlPanel = planConfigState.activeControlPanel;
    if (!activeControlPanel) {
        LogEvent("WriteSepsisPlan. activeControlPanel is null");
        return;
    }


    //////////////////////////
    // Get the current and baseline SOFA scores and show whether they are different.
    var currentSOFAOptionList = [ "SepsisSOFAOption_Current_PaO2FiO2", "SepsisSOFAOption_Current_Plts", "SepsisSOFAOption_Current_Bili", "SepsisSOFAOption_Current_MAP", "SepsisSOFAOption_Current_GCS", "SepsisSOFAOption_Current_Cr" ];
    var baselineSOFAOptionList = [ "SepsisSOFAOption_Baseline_PaO2FiO2", "SepsisSOFAOption_Baseline_Plts", "SepsisSOFAOption_Baseline_Bili", "SepsisSOFAOption_Baseline_MAP", "SepsisSOFAOption_Baseline_GCS", "SepsisSOFAOption_Baseline_Cr" ];
    var SOFAValueNameList = [ "PaO2/FiO2", "Plts", "TBili", "MAP", "GCS", "Creatinine" ];
    MedNote_ComputeSOFAScore(activeControlPanel, currentSOFAOptionList, baselineSOFAOptionList, SOFAValueNameList, "The patient meets SIRS criteris (", false, "", optionNameList, ")")
    if (MedNote_GetCPOptionBool("SepsisShowSOFAChange")) {
        totalDiffInScores = g_CURRENT_SOFA_SCORE - g_BASELINE_SOFA_SCORE;
        if (totalDiffInScores >= 2) {
            planStr = "The patient meeds sepsis criteria with an increase of SOFA score by " + totalDiffInScores;
            planStr += " (from " + g_BASELINE_SOFA_SCORE + " to " + g_CURRENT_SOFA_SCORE + ")";
            WriteComment(planStr);
            planStr = "There were changes in " + g_SOFA_DIFFERENNCES;
            WriteComment(planStr);
        } else {
            planStr = "The SOFA score dud not change significantly";
            planStr += " (from " + g_BASELINE_SOFA_SCORE + " to " + g_CURRENT_SOFA_SCORE + ")";
            WriteComment(planStr);
        }
    } // if (MedNote_GetCPOptionBool("SepsisShowSOFAChange"))


    //////////////////////////
    // Describe the criteria for this diagnosis.
    var optionNameList = [ "SepsisSIRSHROption", "SepsisSIRSTempOption", "SepsisSIRSRROption", "SepsisSIRSWBCOption" ];
    WriteListOfSelectedValues(activeControlPanel, "The patient meets SIRS criteris (", false, "", optionNameList, ")")

    //////////////////////////
    // Describe the possible sources.
    var optionNameList = [ "SepsisUTISourceOption", "SepsisPneumoniaSourceOption", "SepsisCellulitisSourceOption" ];
    WriteListOfSelectedValues(activeControlPanel, "The possible sources of infection include: ", false, "", optionNameList, "")

    // Workup
    var optionNameList = [ "SepsisWUBloodCultureOption", "SepsisWUUAOption", "SepsisWUNaresOption", "SepsisWUSputumCultureOption",
            "SepsisWURVPOption", "SepsisWUStoolCultureOption", "SepsisWUStrepUrineAntigenOption", "SepsisWULegionellaUrineAntigenOption",
            "SepsisWUCDiffOption", "SepsisWUBetaGlucanOption", "SepsisWUGalactomannanOption"];
    WriteListOfSelectedActions(activeControlPanel, "Check ", optionNameList)

    // Markers
    var optionNameList = [ "SepsisWUProcalOption", "SepsisWUCRPOption", "SepsisWULactateOption"];
    WriteListOfSelectedActions(activeControlPanel, "Check ", optionNameList)

    // Imaging
    var optionNameList = [ "SepsisWUXRayOption", "SepsisEchoOption", "SepsisCTAAbdomenOption", "SepsisCTAHeadOption", "SepsisPanorexOption"];
    WriteListOfSelectedValues(activeControlPanel, "Check: ", false, "", optionNameList, "")

    // Fluids/Steroids
    //    WriteAction("IV fluid challenge, starting with 30 mL/Kg initial bolus of crystalloid.");
    planStr = MedNote_GetCPOptionValue("SepsisFluidBolusOption");
    modifierStr = MedNote_GetCPOptionValue("SepsisHighMaintFluidOption");
    if (modifierStr != "") {
        if (planStr != "") {
            planStr += ", then ";
        }
        planStr += modifierStr;
    }
    modifierStr = MedNote_GetCPOptionValue("SepsisLowMaintFluidOption");
    if (modifierStr != "") {
        if (planStr != "") {
            planStr += ", then ";
        }
        planStr += modifierStr;
    }
    if (planStr != "") {
        WriteAction(planStr);
    }
    WriteActionIfSelected(activeControlPanel, "SepsisStressSteroidsOption");

    // Antibiotics
    var actionNameList = [ "SepsisVancOption", "SepsisPipTazoOption", "SepsisCefepimeOption", "SepsisMetronidazoleOption", "SepsisCeftriaxoneOption"];
    WriteListOfSubActions("Antibiotics", actionNameList);
//    if (MedNote_GetCPOptionBool("SepsisVancOption")) {
//        WriteVancomycinPlan(true, true);
//    }
//    if (MedNote_GetCPOptionBool("SepsisPipTazoOption")) {
//        WritePipTazoPlan(true);
//    }

    // Hold Meds
    WriteActionIfSelected(activeControlPanel, "SepsisHoldDiureticsOption");
    WriteActionIfSelected(activeControlPanel, "SepsisHoldBPMedsOption");
} // WriteSepsisPlan






////////////////////////////////////////////////////////////////////////////////
//
// [WriteOSAPlan]
//
// Last Updated 8/6/2023
////////////////////////////////////////////////////////////////////////////////
function 
WriteOSAPlan() {
    var planStr = "";
    var modifierStr = "";
    var planConfigState = null;
    var activeControlPanel = null;
    var count = 0;
    var criteriaStr;
    var criteriaList;

    ///////////////////
    // Start the plan section
    planStr = "Obstructive Sleep Apnea";
    modifierStr = MedNote_GetCPOptionValue("OSAPossibleModifier");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr + planStr;
    }
    if (PrintSingleLinePlanAtEnd('OSAPlan', planStr, "Continue home CPAP")) {
        return
    }
    MedNote_StartNewPlanSection(planStr, "OSAPlan");

    modifierStr = MedNote_GetCPOptionValue("OSAObesityHypoventillationPlan");
    if ((modifierStr != null) && (modifierStr != "")) {
        MedNote_AddRelatedProblem(modifierStr);
    }
    modifierStr = MedNote_GetCPOptionValue("OSAHypercapneaPlan");
    if ((modifierStr != null) && (modifierStr != "")) {
        MedNote_AddRelatedProblem(modifierStr);
    }

    // Get the control panel. 
    // This was set up by the call to MedNote_StartNewPlanSection.
    planConfigState = g_AllPlansDeclaration['OSAPlan'];
    activeControlPanel = planConfigState.activeControlPanel;
    if (!activeControlPanel) {
        LogEvent("WriteOSAPlan. activeControlPanel is null");
        return;
    }

    //////////////////////////
    // Describe the criteria for this diagnosis.
    var optionNameList = [ "OSANeckOver16inOption", "OSASnoringOption", "OSATiredOption", "OSAObservedApneaOption", "OSAHypertensionOption", "OSABMIOver35Option", "OSAAgeOver50yoOption", "OSAMaleOption" ];
    WriteListOfSelectedValues(activeControlPanel, "STOP-BANG score=", true, " (", optionNameList, ")")
    WriteCommentIfSelected(activeControlPanel, "OSAExplainSTOPBANGOption");
    //WriteComment("The patient also complains of morning headaches, and has sequelae possibly attributable to untreated OSA: A-Fib, HFpEF, HTN");
    WriteCommentIfSelected(activeControlPanel, "OSAPastDiagnosisOption");
    WriteCommentIfSelected(activeControlPanel, "OSAABGResultsOption");
    WriteCommentIfSelected(activeControlPanel, "OSAInsuranceOption");

    // Diagnose
    WriteActionIfSelected(activeControlPanel, "OSACheckABGOption");
    WriteActionIfSelected(activeControlPanel, "OSASleepStudyOption");
    WriteActionIfSelected(activeControlPanel, "OSACheckPFTOption");
    WriteActionIfSelected(activeControlPanel, "OSAOvernightOximetryOption");

    // Treat
    WriteActionIfSelected(activeControlPanel, "OSAContinueCPAPOption");
    WriteActionIfSelected(activeControlPanel, "OSAFlonaseOption");

    // Additional Workup
    WriteActionIfSelected(activeControlPanel, "OSAGetEchoOption");
    WriteActionIfSelected(activeControlPanel, "OSAGetEKGOption");
} // WriteOSAPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteIllicitDrugsPlan]
//
// Updated 2023-9-25 - Combine items
////////////////////////////////////////////////////////////////////////////////
function 
WriteIllicitDrugsPlan() { 
    var planStr = "";
    var planConfigState = null;
    var activeControlPanel = null;
    var problemID = "";
    var problemValue = "";
    var subPlanActionList = [];

    ///////////////////
    // Start the plan section
    planStr = "";
    if (planStr == "") {
        problemID = "OpioidUseDisorderModifier";
        problemValue = MedNote_GetCPOptionValue(problemID);
        if ((problemValue != null) && (problemValue != "")) {
            planStr = problemValue;
        }
    }
    if (planStr == "") {
        problemID = "MethUseDisorderModifier";
        problemValue = MedNote_GetCPOptionValue(problemID);
        if ((problemValue != null) && (problemValue != "")) {
            planStr = problemValue;
        }
    }
    if (planStr == "") {
        problemID = "CannabisUseDisorderModifier";
        problemValue = MedNote_GetCPOptionValue(problemID);
        if ((problemValue != null) && (problemValue != "")) {
            planStr = problemValue;
        }
    }
    if (planStr == "") {
        problemID = "CocaineUseDisorderModifier";
        problemValue = MedNote_GetCPOptionValue(problemID);
        if ((problemValue != null) && (problemValue != "")) {
            planStr = problemValue;
        }
    }
    if (planStr == "") {
        planStr = "Substance Abuse";
        problemID = "";
    }
        
    if (PrintSingleLinePlanAtEnd('IllicitDrugsPlan', planStr, "Monitor for withdrawal")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "IllicitDrugsPlan");
    if (!activeControlPanel) {
        LogEvent("WriteIllicitDrugsPlan. activeControlPanel is null");
        return;
    }
    if (problemID != "OpioidUseDisorderModifier") {
        MedNote_AddRelatedProblemIfSelected(activeControlPanel, "OpioidUseDisorderModifier");
    }
    if (problemID != "CannabisUseDisorderModifier") {
        MedNote_AddRelatedProblemIfSelected(activeControlPanel, "CannabisUseDisorderModifier");
    }
    if (problemID != "MethUseDisorderModifier") {
        MedNote_AddRelatedProblemIfSelected(activeControlPanel, "MethUseDisorderModifier");
    }
    if (problemID != "CocaineUseDisorderModifier") {
        MedNote_AddRelatedProblemIfSelected(activeControlPanel, "CocaineUseDisorderModifier");
    }
    if (problemID != "SedativeUseDisorderModifier") {
        MedNote_AddRelatedProblemIfSelected(activeControlPanel, "SedativeUseDisorderModifier");
    }
    WriteCommentIfSelected(activeControlPanel, "IllicitsSeverityModifier");


    //////////////////////////
    // DSM Criteria
    var optionNameList = [ "IllicitsHazardousUseOption", "IllicitsSocialProblemsOption", "IllicitsNeglectedRolesOption", 
                            "IllicitsWithdrawalOption", "IllicitsToleranceOption", "IllicitsLargerAmountsOption", 
                            "IllicitsAttemptsToQuitOption", "IllicitsTimeSpentOption", "IllicitsPsychPhysicalProblemsOption", 
                            "IllicitsGaveUpActivitiesOption", "IllicitsCravingOption" ];
    WriteListOfSelectedValues(activeControlPanel, "The patient meets the following criteria for substance abuse: ", false, "", optionNameList, "")

    // History
    //WriteCommentIfSelected(activeControlPanel, "IllicitsShowUDSOption");
    var optionNameList = [ "Illicits_UDS_Heroin_Option", "Illicits_UDS_Opioids_Option", "Illicits_UDS_Meth_Option", 
                            "Illicits_UDS_THC_Option", "Illicits_UDS_Cocaine_Option", "Illicits_UDS_Benzos_Option" ];
    WriteListOfSelectedValues(activeControlPanel, "On admission, urine drug screen was positive for: ", false, "", optionNameList, "")
    WriteCommentIfSelected(activeControlPanel, "IllicitsPastUDSOption");
    WriteCommentIfSelected(activeControlPanel, "IllicitsShowPharmRecordsOption");
    WriteCommentIfSelected(activeControlPanel, "IllicitsPatientReportsOption");

    // Eval
    var optionNameList = [ "IllicitsCheckUDSOption", "IllicitsCheckHepatitisOption", "IllicitsCheckHIVOption", 
                        "IllicitsCheckHepImmpnityOption"];
    WriteListOfSelectedActions(activeControlPanel, "Check: ", optionNameList)


    // Screening
    var optionNameList = [ "IllicitsAddictionMedOption", "IllicitsMusicTherapyOption", "IllicitsNarrativeMedOption", 
                           "IllicitsChaplainOption"];
    WriteListOfSelectedActions(activeControlPanel, "Supportive care: ", optionNameList)


    // Symptoms
    subPlanActionList = [ "IllicitsHydroxyzineOption", "IllicitsTrazodoneOption", "IllicitsLoperamideOption", 
                            "IllicitsOndansetronOption", "IllicitsMethocarbamolOption",
                            "IllicitsAcetaminophenOption"];
    MedNode_WriteSubPlan("Supportive Care", subPlanActionList)
} // WriteIllicitDrugsPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteGIBleedPlan]
//
// 2023-11-14 - Combined workup labs into a single task
////////////////////////////////////////////////////////////////////////////////
function 
WriteGIBleedPlan() {
    var planStr = "";
    var modifierStr = "";
    var activeControlPanel = null;

    ///////////////////
    // Start the plan section
    planStr = "GI Bleed";
    modifierStr = MedNote_GetCPOptionValue("GIBleedUpperModifier");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr + " " + planStr;
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "GIBleedPlan");
    if (!activeControlPanel) {
        LogEvent("WriteGIBleedPlan. activeControlPanel is null");
        return;
    }

    // Class
    WriteCommentIfSelected(activeControlPanel, "GIBleedSourceOfBleed");
    WriteCommentIfSelected(activeControlPanel, "GIBleedHemorrhageClassOption");
    WriteCommentIfSelected(activeControlPanel, "GIBleedExplainHROption");

    // IV Fluids
    WriteActionIfSelected(activeControlPanel, "GIBleedFluidBolusOption");
    WriteActionIfSelected(activeControlPanel, "GIBleedMaintFluidOption");
    WriteActionIfSelected(activeControlPanel, "GIBleedExplainFluidTargetsOption");
    WriteActionIfSelected(activeControlPanel, "GIBleedHoldDiureticsOption");

    // Basics
    WriteActionIfSelected(activeControlPanel, "GIBleedTypeScreenOption");
    WriteActionIfSelected(activeControlPanel, "GIBleedHgbFreqOption");
    WriteActionIfSelected(activeControlPanel, "GIBleedTransfuseLevelOption");

    // Workup
    var optionNameList = [ 'GIBleedINROption', 'GIBleedBUNOption', 'GIBleedHemoccultOption', 'GIBleedHPyloriOption' ]; 
    WriteListOfSelectedActions(activeControlPanel, "Check ", optionNameList)

    // Imaging
    WriteActionIfSelected(activeControlPanel, "GIBleedCTAngiographyOption");
    WriteActionIfSelected(activeControlPanel, "GIBleedCTEnterographyOption");

    // Treat
    WriteActionIfSelected(activeControlPanel, "GIBleedPantoprazoleOption");
    WriteActionIfSelected(activeControlPanel, "GIBleedOctreotideOption");
    WriteActionIfSelected(activeControlPanel, "GIBleedCeftriaxoneOption");
} // WriteGIBleedPlan





////////////////////////////////////////////////////////////////////////////////
//
// [PrintDiabetesPlan]
//
// Updated 2021-2-15
////////////////////////////////////////////////////////////////////////////////
function 
PrintDiabetesPlan() { 
    var planStr = "";
    var modifierStr = "";
    var activeControlPanel = null;
    var A1cStr = "";

    ///////////////////
    // Start the plan section
    planStr = "Diabetes";
    modifierStr = MedNote_GetCPOptionValue("Diabetes_Type_Modifier");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr += modifierStr;
    }
    modifierStr = MedNote_GetCPOptionValue("Diabetes_Uncontrolled_Modifier");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr += modifierStr;
    }
    modifierStr = MedNote_GetCPOptionValue("DiabetesHyperglycemiaModifier");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr += modifierStr;
    }

    activeControlPanel = MedNote_StartNewPlanSection(planStr, "DiabetesPlan");
    if (!activeControlPanel) {
        LogEvent("PrintDiabetesPlan. activeControlPanel is null");
        return;
    }

    // Status
    var optionNameList = [ "DiabetesStatusShowA1cOption"];
    WriteListOfSelectedFormatStrings(activeControlPanel, optionNameList);
    WriteCommentIfSelected(activeControlPanel, "DiabetesStatusShowWhenDiagnosedOption");
    WriteCommentIfSelected(activeControlPanel, "DiabetesStatusShowHomeRegimenOption");
    WriteCommentIfSelected(activeControlPanel, "DiabetesStatusShowDailyStatusOption");

    // SGLT2
    var optionNameList = [ "DMSGLT2IndicationsDM2Option", "DMSGLT2IndicationsCKDOption", 
                            "DMSGLT2IndicationsHFrEFOption", "DMSGLT2IndicationsUACROver200Option" ]
    WriteListOfSelectedValues(activeControlPanel, "Indications for starting an SGLT2 inhibitor include: ", false, "", optionNameList, "")
    var optionNameList = [ "DMSGLT2ContraindicationsGFRBelow30Option", "DMSGLT2ContraindicationsDM1Option",
                            "DMSGLT2ContraindicationsTransplantOption", "DMSGLT2ContraindicationsDKAOption",
                            "DMSGLT2ContraindicationsImunosuppressedOption", "DMSGLT2ContraindicationsPKDOption",
                            "DMSGLT2ContraindicationsSLEOption", "DMSGLT2ContraindicationsANCAOption" ]
    WriteListOfSelectedValues(activeControlPanel, "Do not start an SGLT2 inhibitor due to contraindications: ", false, "", optionNameList, "")


    // Workup
    WriteActionIfSelected(activeControlPanel, "DiabetesWorkupGetA1cOption");
    WriteActionIfSelected(activeControlPanel, "DiabetesWorkupGetUrineAlbProtCrOption");

    // Insulin
    WriteActionIfSelected(activeControlPanel, "DiabetesInsulinHoldPOOption");

    // Insulin
    WriteCommentIfSelected(activeControlPanel, "DiabetesInsulinReducedHomeRegimenOption");
    var actionNameList = [ "DiabetesInsulinGlargineOption", "DiabetesInsulinLisproOption", "DiabetesInsulinSlidingScaleOption"];
    WriteListOfSubActions("Insulin", actionNameList);

    // SGLT2
    WriteActionIfSelected(activeControlPanel, "DMSGLT2EmpagliflozinOption");
    WriteActionIfSelected(activeControlPanel, "DMSGLT2ReduceInsulinOption");
    WriteActionIfSelected(activeControlPanel, "DMSGLT2ExplainGFRDropOption");

    // Followup
    WriteActionIfSelected(activeControlPanel, "DiabetesDMEducationOption");
    WriteActionIfSelected(activeControlPanel, "DiabetesNutritionEducationOption");
    WriteActionIfSelected(activeControlPanel, "DiabetesFollowupOphthoOption");
    WriteActionIfSelected(activeControlPanel, "DiabetesFollowupPodiatryOption");
    WriteActionIfSelected(activeControlPanel, "DiabetesFollowupEndocrineOption");
} // PrintDiabetesPlan






////////////////////////////////////////////////////////////////////////////////
//
// [PrintCKDPlan]
//
// 2021-4-24 - Get all new user input values.
// 2022-1-18 - Added Transplant
// 2022-11-3 - Updated
// 2023-11-14 - Combined workup labs into a single task
////////////////////////////////////////////////////////////////////////////////
function 
PrintCKDPlan() { 
    var planStr = "";
    var modifierStr = "";
    var activeControlPanel = null;

    ///////////////////
    // Start the plan section
    planStr = "Chronic Kidney Disease";
    modifierStr = MedNote_GetCPOptionValue("CKD_Stage_Modifier");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr += ", " + modifierStr;
    }
    if (PrintSingleLinePlanAtEnd('CKDPlan', planStr, "Renally dose medications")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "CKDPlan");
    if (!activeControlPanel) {
        LogEvent("PrintCKDPlan. activeControlPanel is null");
        return;
    }

    // Write related problems.
    modifierStr = MedNote_GetCPOptionValue("CKD_Diabetic_Modifier");
    if ((modifierStr != null) && (modifierStr != "")) {
        MedNote_AddRelatedProblem(modifierStr);
    }


    ///////////////////
    // Read Inputs and do Calculations
    var currentCr = GetFloatInputForControlPanel(activeControlPanel, 'CKD_INPUT_CURRENT_CR');
    var currentCystatinC = GetFloatInputForControlPanel(activeControlPanel, 'CKD_INPUT_CP_CysC');
    var currentAge = GetFloatInputForControlPanel(activeControlPanel, 'CKD_INPUT_CP_AGE');
    var weightInKg = GetFloatInputForControlPanel(activeControlPanel, 'CKD_INPUT_CP_WEIGHT_KG');
    var currentAlbumin = GetFloatInputForControlPanel(activeControlPanel, 'CKD_INPUT_SERUM_ALBUMIN');
    var currentCa = GetFloatInputForControlPanel(activeControlPanel, 'CKD_INPUT_SERUM_Calcium');
    var currentCO2 = GetFloatInputForControlPanel(activeControlPanel, 'CKD_INPUT_SERUM_Bicarb');
    var currentPhos = GetFloatInputForControlPanel(activeControlPanel, 'CKD_INPUT_SERUM_Phos');
    var currentUrProt = GetFloatInputForControlPanel(activeControlPanel, 'CKD_INPUT_URINE_PROTEIN');
    var currentUrAlb = GetFloatInputForControlPanel(activeControlPanel, 'CKD_INPUT_URINE_ALBUMIN');
    var currentUrCr = GetFloatInputForControlPanel(activeControlPanel, 'CKD_INPUT_URINE_Cr');
    var fIsMale = GetBoolInputForControlPanel(activeControlPanel, "CKD_Male_Modifier");


    // Calculate the eGFR. We need this for both displaying GFR and ansl for ESRD risk.
    ComputeEstGFR(currentCr, currentAge, currentCystatinC, weightInKg, fIsMale);

    /////////////////////////////////
    // Status
    if ((MedNote_GetCPOptionBool("CKDCausesShowCrOption")) && (currentCr > 0)) {
        WriteComment("Current Cr: " + currentCr); 
    }
    if (MedNote_GetCPOptionBool("CKDCausesShowGFROption")) {
        if ((g_GFR_CKDEPI > 0) // || (g_GFR_MDRD > 0) || (g_GFR_CockroftGault > 0)
                || (g_GFR_CKDEPI_CystatinC > 0) || (g_GFR_CKDEPI_Creatinine_CystatinC > 0)) {
            headerLine = "Current eGFR (";
            if (currentCr > 0) {
                headerLine = headerLine + "Cr=" + currentCr;
            }
            if (currentCystatinC > 0) {
                headerLine = headerLine + ", Cystatin-C=" + currentCystatinC;
            }
            if (currentAge > 0) {
                headerLine = headerLine + ", age=" + currentAge;
            }
            if (weightInKg > 0) {
                headerLine = headerLine + ", wt=" + weightInKg + "kg";
            }
            if (!fIsMale) {
                headerLine = headerLine + ", female";
            }
            headerLine = headerLine + ")";
            WriteComment(headerLine);
            //if (g_GFR_MDRD > 0) {
            //    WriteIndentedTextLine(g_GFR_MDRD + " (MDRD)");
            //}
            //if (g_GFR_CockroftGault > 0) {
            //    WriteIndentedTextLine(g_GFR_CockroftGault + " (Cockcroft-Gault)");
            //}
            if (g_GFR_CKDEPI > 0) {
                WriteIndentedTextLine(g_GFR_CKDEPI + " (CKD EPI 2021)");
            }
            if (g_GFR_CKDEPI_Creatinine_CystatinC > 0) {
                WriteIndentedTextLine(g_GFR_CKDEPI_Creatinine_CystatinC + " (CKD EPI Cr-CystatinC 2021)");
            }
            if (g_GFR_CKDEPI_CystatinC > 0) {
                WriteIndentedTextLine(g_GFR_CKDEPI_CystatinC + " (CKD EPI CystatinC 2012)");
            }
        }
    }
    if (MedNote_GetCPOptionBool("CKDCausesShow2YrRiskOption")) {
        var est2yrStr = "xxx";
        var est5yrStr = "xxx";

        var gfrForESRDRisk = g_GFR_MDRD;
        if (g_GFR_CKDEPI_CystatinC > 0) {
            gfrForESRDRisk = g_GFR_CKDEPI_CystatinC;
        } else if (g_GFR_CKDEPI_Creatinine_CystatinC > 0) {
            gfrForESRDRisk = g_GFR_CKDEPI_Creatinine_CystatinC;
        } else if (g_GFR_CKDEPI > 0) {
            gfrForESRDRisk = g_GFR_CKDEPI;
        } //else if (g_GFR_CockroftGault > 0) {
            //gfrForESRDRisk = g_GFR_CockroftGault;
        //}
        LogEvent("gfrForESRDRisk = " + gfrForESRDRisk)

        // This writes the results in global variables g_2YearESRDRisk and g_5YearESRDRisk
        // This forces it to only use the 4-variable equation
        currentAlbumin = -1
        currentCa = -1
        currentCO2 = -1
        currentPhos = -1
        ComputeRiskOfESRD(currentAge, fIsMale, gfrForESRDRisk, currentUrAlb, currentUrCr, currentAlbumin, currentCa, currentCO2, currentPhos);

        if (g_2YearESRDRisk > 0) {
            est2yrStr = g_2YearESRDRisk;
        }
        if (g_5YearESRDRisk > 0) {
            est5yrStr = g_5YearESRDRisk;
        }
        if ((g_2YearESRDRisk > 0) && (g_2YearESRDRisk > 0)) {
            WriteComment("The risk of ESRD within two years is " + est2yrStr 
                            + " percent, and within five years is " + est5yrStr + " percent");
        } else if (g_2YearESRDRisk > 0) {
            WriteComment("The risk of ESRD within two years is " + est2yrStr + " percent");
        }
    } // if (MedNote_GetCPOptionBool("CKDCausesShow2YrRiskOption")) {
    WriteCommentIfSelected(activeControlPanel, "CKDCausesRiskPaperCitationOption");

    WriteCommentIfSelected(activeControlPanel, "CKDStatusTransplantOption");
    //optionNameList = [ "CKDCausesDiabetesOption", "CKDStatusTreatHTNOption", "CKDStatusTreatDMOption"];
    //WriteListOfSelectedValues(activeControlPanel, "We will continue to manage the CKD by treating the ", false, "", optionNameList, "")

    ///////////////////////////////
    // Cause
    var optionNameList = [ "CKDCausesDiabetesOption", "CKDCausesHypertensionOption", 
                            "CKDCausesPastAKIOption", "CKDCausesMedicationsOption", 
                            "CKDCausesObstructionOption"];
    WriteListOfSelectedValues(activeControlPanel, "Possible original causes include: ", false, "", optionNameList, "")


    optionNameList = [ "CKDCausesShowProtCrOption", "CKDCausesShowAlbCrOption"];
    WriteListOfSelectedFormatStrings(activeControlPanel, optionNameList);

    ///////////////////////////////
    // SGLT2 Comments
    var optionNameList = [ "CKDSGLT2IndicationsDM2Option", "CKDSGLT2IndicationsCKDOption", 
                            "CKDSGLT2IndicationsHFrEFOption", "CKDSGLT2IndicationsUACROver200Option" ]
    WriteListOfSelectedValues(activeControlPanel, "Indications for starting an SGLT2 inhibitor include: ", false, "", optionNameList, "")

    var optionNameList = [ "CKDSGLT2ContraindicationsGFRBelow30Option", "CKDSGLT2ContraindicationsDM1Option",
                            "CKDSGLT2ContraindicationsTransplantOption", "CKDSGLT2ContraindicationsDKAOption",
                            "CKDSGLT2ContraindicationsImunosuppressedOption", "CKDSGLT2ContraindicationsPKDOption",
                            "CKDSGLT2ContraindicationsSLEOption", "CKDSGLT2ContraindicationsANCAOption" ]
    WriteListOfSelectedValues(activeControlPanel, "Do not start an SGLT2 inhibitor due to contraindications: ", false, "", optionNameList, "")


    ///////////////////////////////
    // Workup
    var optionNameList = [ 'CKDWorkupGetUrineAlbProtCrOption', 'CKDWorkupGetPTHOption', 'CKDWorkupGetVitDOption' ]; 
    WriteListOfSelectedActions(activeControlPanel, "Check ", optionNameList)

    ///////////////////////////////
    // General
    WriteActionIfSelected(activeControlPanel, "CKDStatusNoNSAIDsOption");
    WriteActionIfSelected(activeControlPanel, "CKDLisinoprilOption");
    WriteActionIfSelected(activeControlPanel, "CKDLosartanOption");
    WriteActionIfSelected(activeControlPanel, "CKDLowKDietOption");

    ///////////////////////////////
    // SGLT2
    WriteActionIfSelected(activeControlPanel, "CKDSGLT2EmpagliflozinOption");
    WriteActionIfSelected(activeControlPanel, "CKDSGLT2ReduceInsulinOption");
    WriteActionIfSelected(activeControlPanel, "CKDSGLT2ExplainGFRDropOption");

    // CKD 3b
    WriteActionIfSelected(activeControlPanel, "CKD3bReduceMetforminOption");
    WriteActionIfSelected(activeControlPanel, "CKD3bStopEmpagliflozinOption");

    // CKD 4
    WriteActionIfSelected(activeControlPanel, "CKD4StopMetforminOption");
    WriteActionIfSelected(activeControlPanel, "CKD4StopThiazidesOption");
    WriteActionIfSelected(activeControlPanel, "CKD4ReduceGabapentinOption");
    WriteActionIfSelected(activeControlPanel, "CKD4ReduceRanitidineOption");
    WriteActionIfSelected(activeControlPanel, "CKD4PhosBinderOption");
    WriteActionIfSelected(activeControlPanel, "CKD4BicarbOption");

    // Clinics
    var optionNameList = [ 'CKDFollowupRenalOption', 'CKDFollowupTransplantOption' ]; 
    WriteListOfSelectedActions(activeControlPanel, "On discharge refer to ", optionNameList)

    ////////////////////
    //WriteAction("ACE inhibitor if microalbumin/Cr over 30 mcg/mg");
    //WriteAction("If HCO3 below 20 and GFR below 30, then start Sodium Bicarb 650mg PO TID (see de Brito-Ashurst et al, Bicarbonate Supplementation Slows Progression of CKD and Improves Nutritional Status)");
    //WriteAction("If Hgb below 10 and CKD 3 or more, then rule out other anemia causes in anticipation of starting erythrocyte stimulating agent");
    //WriteAction("If over 50 years old, start a statin (KDIGO 2013), no benefit seen in non-statin meds");

    // Time on transplant list starts accruing when GFR is below 20. See US Dept of Health & Human Services - Educational Guidance on Patient Referral to Kidney Transplantation - https://optn.transplant.hrsa.gov/resources/guidance/educational-guidance-on-patient-referral-to-kidney-transplantation/");
} // PrintCKDPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteCADPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteCADPlan() {
    var activeControlPanel = null;

    var planStr = "Coronary Artery Disease";
    if (PrintSingleLinePlanAtEnd('CADPlan', planStr, "Continue home medications: ")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection("Coronary Artery Disease", "CADPlan");
    if (!activeControlPanel) {
        LogEvent("WriteCADPlan. activeControlPanel is null");
        return;
    }

    // Past Workup
    WriteCommentIfSelected(activeControlPanel, "CADShowProcedureHistoryOption");
    WriteCommentIfSelected(activeControlPanel, "CADShowEchoOption");
    WriteCommentIfSelected(activeControlPanel, "CADHomeMedsOption");

    // Beta Blockers
    WriteActionIfSelected(activeControlPanel, "CADMetoprololTarOption");
    WriteActionIfSelected(activeControlPanel, "CADMetoprololSuccOption");
    WriteActionIfSelected(activeControlPanel, "CADCarvedilolOption");
    WriteActionIfSelected(activeControlPanel, "CADNSBBOption");

    // ACE/ARB
    WriteActionIfSelected(activeControlPanel, "CADLisinoprilOption");
    WriteActionIfSelected(activeControlPanel, "CADLosartanOption");
    WriteActionIfSelected(activeControlPanel, "CADSpironiolactoneOption");
    WriteActionIfSelected(activeControlPanel, "CADARNIOption");

    // Statin/Aspirin
    WriteActionIfSelected(activeControlPanel, "CADClopidogrelOption");
    WriteActionIfSelected(activeControlPanel, "CADAtorvaOption");
    WriteActionIfSelected(activeControlPanel, "CADAsaOption");
    WriteActionIfSelected(activeControlPanel, "CADRivaroxabanOption");
} // WriteCADPlan






////////////////////////////////////////////////////////////////////////////////
//
// [WriteCOPDPlan]
//
// Updated 2021-2-15
// Updated 2022-10-30
// Updated 2022-11-3
// 2023-11-14 - Combined workup labs into a single task
////////////////////////////////////////////////////////////////////////////////
function 
WriteCOPDPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Chronic Obstructive Pulmonary Disease";
    modifierStr = MedNote_GetCPOptionValue("COPDPossibleOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr;
    }

    activeControlPanel = MedNote_StartNewPlanSection(planStr, "COPDPlan");
    if (!activeControlPanel) {
        LogEvent("WriteCOPDPlan. activeControlPanel is null");
        return;
    }
    MedNote_AddRelatedProblemIfSelected(activeControlPanel, "COPDExacerbationOption");
    MedNote_AddRelatedProblemIfSelected(activeControlPanel, "COPDRespFailureModifier");

    // Exacerbation
    var optionNameList = [ "COPDTriggerDyspneaOption", "COPDTriggerMoreSputumOption", "COPDTriggerPurulentOption"];
    WriteListOfSelectedValues(activeControlPanel, "This is an acute exacerbation with: ", false, "", optionNameList, "")
    //<> WriteComment("The exacerbation is mild(1 criteria) moderate(2 criteria) severe(3 criteria)");

    // Triggers
    var optionNameList = [ "COPDTriggerInfectionOption", "COPDTriggerSmokingOption", "COPDTriggerComplianceOption", "COPDTriggerMedChangesOption"];
    WriteListOfSelectedValues(activeControlPanel, "The possible triggers of this exacerbation include: ", false, "", optionNameList, "")

    // Staging
    var optionNameList = [ "COPDHomeO2Option", "COPDHomeBiPAPOption", "COPDGOLDGroup", "COPDGOLDClass"];
    WriteListOfSelectedValues(activeControlPanel, "At baseline: ", false, "", optionNameList, "")
    WriteCommentIfSelected(activeControlPanel, "COPDShowEOS");
    var inputFEV1 = GetFloatInputForControlPanel(activeControlPanel, 'InputFEV1_CP');
    var inputFVC = GetFloatInputForControlPanel(activeControlPanel, 'InputFVC_CP');
    optionStr = MedNote_GetCPOptionValue("COPDShowFEV1FVC");
    if ((optionStr != null) && (optionStr != "")) {
        fev1FVCRatio = inputFEV1 / inputFVC
        fev1FVCRatio = Math.round((fev1FVCRatio + 0.00001) * 100) / 100;
        WriteComment("FEV1/FVC = " + fev1FVCRatio);
    }
    optionStr = MedNote_GetCPOptionValue("COPDShowFEV1");
    if ((optionStr != null) && (optionStr != "")) {
        WriteComment("FEV1 = " + inputFEV1);
    }
    //<>WriteComment("BODE Index = (BMI, Obstruction, Dyspnea, Exercise)");

    // Vitals
    var optionNameList = [ "COPDCurrentO2SatsOption", "COPDCurrentO2Option", "COPDCurrentCPAPOption", "COPDO2VBGOption"];
    WriteListOfSelectedValues(activeControlPanel, "Currently: ", false, "", optionNameList, "")

    // Workup
    WriteActionIfSelected(activeControlPanel, "COPDXrayOption");
    var optionNameList = [ 'COPDGetVBGOption', 'COPDGetRVPOption', 'COPDCultureSputOption', 'COPDCultureBloodOption',
                            'COPDUrineAntigensOption', 'COPDProcalOption']; 
    WriteListOfSelectedActions(activeControlPanel, "Check ", optionNameList)
    WriteActionIfSelected(activeControlPanel, "COPDPFTOption");

    // Bronchodilators
    WriteActionIfSelected(activeControlPanel, "COPDAlbuterolOption");
    WriteActionIfSelected(activeControlPanel, "COPDAlbuterolIpratropiumOption");
    WriteActionIfSelected(activeControlPanel, "COPDLAMAOOption");
    WriteActionIfSelected(activeControlPanel, "COPDLABAOption");

    // AntiInflammatory
    WriteActionIfSelected(activeControlPanel, "COPDPrednisoneOption");
    WriteActionIfSelected(activeControlPanel, "COPDPPIOption");
    WriteActionIfSelected(activeControlPanel, "COPDAzithroOption");

    // Oxygen
    WriteActionIfSelected(activeControlPanel, "COPDGiveO2Option");
    WriteActionIfSelected(activeControlPanel, "COPDGuaifenesinOption");

//"COPDHomeMedsOption" value="HomeMeds" class="CPOptionDisabledStyle" toggleState="-1" onclick="MedNote_OnCPOptionButton(this)" /></td>
//    WriteActionIfSelected(activeControlPanel, "COPDHomeMedsOption": { "ButtonLabelList" : ["HomeMeds"], "ValueList" : ["Home medications: "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
} // WriteCOPDPlan







////////////////////////////////////////////////////////////////////////////////
//
// [WriteHemodialysisPlan]
//
// 2020-4-3 - combined PD and HD
////////////////////////////////////////////////////////////////////////////////
function 
WriteHemodialysisPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Renal Failure on Hemodialysis";
    modifierStr = MedNote_GetCPOptionValue("ESRDAKIOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr;
    }

    activeControlPanel = MedNote_StartNewPlanSection(planStr, "HemoDialysisPlan");
    if (!activeControlPanel) {
        LogEvent("WriteHemodialysisPlan. activeControlPanel is null");
        return;
    }

    // Outpatient Unit
    var optionNameList = [ "ESRDScheduleOption", "ESRDHomeUnitOption", "ESRDNephrologistOption"];
    WriteListOfSelectedValues(activeControlPanel, "Outpatient dialysis ", false, "", optionNameList, "")

    var optionNameList = [ "ESRDAccessOption", "ESRDDryWeightOption"];
    WriteListOfSelectedValues(activeControlPanel, "", false, "", optionNameList, "")

    var optionNameList = [ "ESRDOnHDSinceOption", "ESRDCauseofESRDOption"];
    WriteListOfSelectedValues(activeControlPanel, "", false, "", optionNameList, "")

    WriteCommentIfSelected(activeControlPanel, "ESRDMakesUrineOption");

    WriteCommentIfSelected(activeControlPanel, "ESRDCAPDTypeOption");
    var optionNameList = [ "ESRDCAPD15PercentOption", "ESRDCAPD25PercentOption", "ESRDCAPD425PercentOption", "ESRDCAPDIcodextrinOption"];
    WriteListOfSelectedValues(activeControlPanel, "Peritoneal Dialysate: ", false, "", optionNameList, "")
    WriteCommentIfSelected(activeControlPanel, "ESRDPeritonitisOption");
    WriteCommentIfSelected(activeControlPanel, "ESRDLastStoolOption");


    // Dialysis
    WriteActionIfSelected(activeControlPanel, "ESRDDialysisPerRenalOutOption");
    WriteActionIfSelected(activeControlPanel, "ESRDRenalVitaminsOption");
    WriteActionIfSelected(activeControlPanel, "ESRDLasixPOOption");
    WriteActionIfSelected(activeControlPanel, "ESRDTorsemideOption");

    WriteActionIfSelected(activeControlPanel, "ESRDHoldBPMedsOption");
    WriteActionIfSelected(activeControlPanel, "ESRDMidodrineOption");
    WriteActionIfSelected(activeControlPanel, "ESRDMiralaxOption");
    WriteActionIfSelected(activeControlPanel, "ESRDGentamycinOption");
    WriteActionIfSelected(activeControlPanel, "ESRDHeparinInPDOption");

    // Diet
    WriteActionIfSelected(activeControlPanel, "ESRDLowKDietOption");
    WriteActionIfSelected(activeControlPanel, "ESRDFluidRestrictOption");
    WriteActionIfSelected(activeControlPanel, "ESRDDietEdOption");

//    WriteComment("Over 24hrs, this is x liters of peritoneal dialysate");




// CVVH
//    WriteComment("Access is right IJ Temp dialysis catheter");
//    WriteComment("Prescription Fluid: K=4, HCO3=35");
//    WriteComment("Prescription Fluid Rate = xxxx mL/hr (30mL/kg/hr, weight xxx kg)");
//    WriteComment("Blood flow rate 300 mL/min");
//    WriteComment("Ultrafiltration 0 mL/hr");
//    WriteComment("Filtration Fraction = xxxxx. Target below 20% to reduce the risk of clotting and losing efficiency (you aren't getting better dialysis)");
//    WriteComment("Use Normal Saline as needed to replace losses from drain outputs");
//    WriteComment("Do not count any IV fluids given for hypotension in the Intake and Output. You may bolus and not count that fluid volume in the intake/output balance.");
//    WriteComment("Anticoag: Heparin x, Protamine x");
//    WriteComment("Dialysis Pressures: Venous: x  Arterial: x");




// HemoDialysis
//    WriteComment("Most recent dialysis was x, and ran for x hours");
//    WriteComment("Dialysis Pressures: Venous: x  Arterial: x");
//    WriteAction("Hemodialysis today, Duration=4hrs");
//    WriteComment("F-160, Blood Flow Rate 400, Dialysate flow rate 600");
//    WriteComment("Dialysis Bath:");
//    WriteComment("Temp=37 (patient temp is 36)");
//    WriteComment("Ca=2.5");
//    WriteComment("K=3 (patient K on BMP was x)");
//    WriteComment("HCO3=30 (patient HCO3 on BMP was x)");
//    WriteComment("Na=138 (patient Na on BMP was x, target total Na change less than 6mEq)");
//    WriteComment("Ultrafiltration: x L (patient weight x kg, EDW = x, max 10-13 mL/kg/hr)");
} // WriteHemodialysisPlan








////////////////////////////////////////////////////////////////////////////////
//
// [WriteDKAPlan]
//
// http://care.diabetesjournals.org/content/27/suppl_1/s94
// http://care.diabetesjournals.org/content/32/7/1335
// https://www.ncbi.nlm.nih.gov/books/NBK279052/
// https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5375966/
// http://www.thelancet.com/journals/landia/article/PIIS2213-8587(17)30093-1/fulltext
// https://www.uptodate.com/contents/diabetic-ketoacidosis-and-hyperosmolar-hyperglycemic-state-in-adults-treatment
////////////////////////////////////////////////////////////////////////////////
function 
WriteDKAPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var altPlanStr = "";
    var modifierStr = "";

    planStr = "Diabetic Ketoacidosis";
    altPlanStr = MedNote_GetCPOptionValue("DKATypeModifierOption");
    if ((altPlanStr != null) && (altPlanStr != "")) {
        planStr = altPlanStr;
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "DKAPlan");
    if (!activeControlPanel) {
        LogEvent("WriteHemodialysisPlan. activeControlPanel is null");
        return;
    }

    //////////////////////
    // Admission Stats
    WriteCommentIfSelected(activeControlPanel, "DKASeverityModifierOption");
    var optionNameList = [ "DKAShowBicarbOption", "DKAShowAnionGapOption", "DKAShowBloodGasOption", "DKAShowKetonesOption", "DKAShowBetaHydroxyOption", "DKAShowGlucoseOption"];
    WriteListOfSelectedValues(activeControlPanel, "On admission ", false, "", optionNameList, "");

    ///////////////////////////
    // Baseline
    WriteCommentIfSelected(activeControlPanel, "DKAStatusShowA1cOption");
    WriteCommentIfSelected(activeControlPanel, "DKAStatusShowWhenDiagnosedOption");
    WriteCommentIfSelected(activeControlPanel, "DKAStatusShowHomeRegimenOption");
    optionNameList = [ "DKAShowCausesOption"];
    WriteListOfSelectedValues(activeControlPanel, "The likely causes of this episode include ", false, "", optionNameList, "");

    WriteActionIfSelected(activeControlPanel, "DKAWorkupGetA1cOption");
    WriteActionIfSelected(activeControlPanel, "DKAWorkupGetLactateOption");

    //////////////////////
    // Fluids
    WriteActionIfSelected(activeControlPanel, "DKAFluidBolusOption");
    WriteActionIfSelected(activeControlPanel, "DKAFluidRateOption");
    WriteActionIfSelected(activeControlPanel, "DKAHalfNSFluidRateOption");
    WriteActionIfSelected(activeControlPanel, "DKAD5HalfNSFluidRateOption");

    //////////////////////
    // Insulin Drip
    WriteActionIfSelected(activeControlPanel, "DKAInsulinDripBolusOption");
    WriteActionIfSelected(activeControlPanel, "DKAInsulinDripOption");
    WriteActionIfSelected(activeControlPanel, "DKAInsulinDripHoldParamsOption");
    WriteActionIfSelected(activeControlPanel, "DKAInsulinDripExpectGlcOption");

    //////////////////////
    // Transition to Subcu Insulin
    WriteActionIfSelected(activeControlPanel, "DKAInsulinDripCriteriaOption");
    WriteActionIfSelected(activeControlPanel, "DKAInsulinDripStopDripTimeOption");

    /////////////////////
    // Subcu Insulin
    WriteActionIfSelected(activeControlPanel, "DKASubcuInsulinStartHomeOption");
    WriteActionIfSelected(activeControlPanel, "DKASubcuInsulinNewRegimenOption");
    WriteActionIfSelected(activeControlPanel, "DKASlidingScaleInsulinOption");

    //////////////////////
    // Electrolytes
    WriteActionIfSelected(activeControlPanel, "DKAGetLabsOption");
    WriteActionIfSelected(activeControlPanel, "DKAPRNBicarbOption");
    WriteActionIfSelected(activeControlPanel, "DKAPRNKOption");
    WriteActionIfSelected(activeControlPanel, "DKAPRNPhosOption");

    ///////////////////////////
    // Followup
    WriteActionIfSelected(activeControlPanel, "DKADMEducationOption");
    WriteActionIfSelected(activeControlPanel, "DKANutritionEducationOption");
    WriteActionIfSelected(activeControlPanel, "DKAFollowupOphthoOption");
    WriteActionIfSelected(activeControlPanel, "DKAFollowupPodiatryOption");
    WriteActionIfSelected(activeControlPanel, "DKAFollowupEndocrineOption");

    //WriteAction("While Potassium is below 5.3, give 20 mEQ KCl with each liter of IV fluid");
} // WriteDKAPlan







////////////////////////////////////////////////////////////////////////////////
//
// [WritePneumoniaPlan]
// 
// Updated 2020-6-24
// Updated 2021-2-15
// 2023-11-14 - Combined workup labs into a single task
////////////////////////////////////////////////////////////////////////////////
function 
WritePneumoniaPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Pneumonia";
    modifierStr = MedNote_GetCPOptionValue("PneumoniaHAPModifier");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr;
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "PneumoniaPlan");
    if (!activeControlPanel) {
        LogEvent("WritePneumoniaPlan. activeControlPanel is null");
        return;
    }
    MedNote_AddRelatedProblemIfSelected(activeControlPanel, "PneumoniaRespFailureModifier");

    var optionNameList = [ "PneumoniaCoughOption", "PneumoniaDyspneaOption", "PneumoniaSputumChangesOption", 
                            "PneumoniaFeversOption", "PneumoniaXRayOption"];
    WriteListOfSelectedValues(activeControlPanel, "The patient meets the following criteria = ", false, "", optionNameList, "");

    var optionNameList = [ "PneumoniaCURB65ConfusionOption", "PneumoniaCURB65BUNOver20Option", 
                            "PneumoniaCURB65RROver30Option", 
                            "PneumoniaCURB65BPBelow90Option", "PneumoniaCURB65AgeOver65yoOption"];
    WriteListOfSelectedValues(activeControlPanel, "CURB65 = ", true, " (", optionNameList, ")");

    var optionNameList = [ "PneumoniaSIRSHROption", "PneumoniaSIRSTempOption", "PneumoniaSIRSRROption",
                            "PneumoniaSIRSWBCOption"];
    WriteListOfSelectedValues(activeControlPanel, "SIRS = ", false, "", optionNameList, "");

    WriteActionIfSelected(activeControlPanel, "PneumoniaWUXRayOption");
    var optionNameList = [ 'PneumoniaWUBloodCultureOption', 'PneumoniaWUSputumCultureOption', 'PneumoniaWURVPOption']; 
    WriteListOfSelectedActions(activeControlPanel, "Culture ", optionNameList)

    var optionNameList = [ 'PneumoniaWUMRSANaresOption', 'PneumoniaWUStrepUrineAntigenOption', 'PneumoniaWULegionellaUrineAntigenOption', 
                            'PneumoniaWUProcalOption', 'PneumoniaWUCRPOption', 'PneumoniaWULactateOption']; 
    WriteListOfSelectedActions(activeControlPanel, "Check ", optionNameList)

    WriteActionIfSelected(activeControlPanel, "PneumoniaSwallowStudyOption");
    WriteActionIfSelected(activeControlPanel, "PneumoniaPanorexOption");

    // Antibiotics
    var actionNameList = [ "PneumoniaVancOption", "PneumoniaPipTazoOption", "PneumoniaCefepimeOption", 
                            "PneumoniaMetronidazoleOption", "PneumoniaCeftriaxoneOption", "PneumoniaAzithromycinOption"];
    WriteListOfSubActions("Antibiotics", actionNameList);

    // Misc
    WriteActionIfSelected(activeControlPanel, "PneumoniaNebsOption");
    WriteActionIfSelected(activeControlPanel, "PneumoniaGuaifenesinOption");
    WriteActionIfSelected(activeControlPanel, "PneumoniaInspirometerOption");


//    WriteComment("This is HAP, since it started after the patient had been in a hospital for 48 hours");
//    WriteComment("This is HCAP, since the patient had been hospitalized within 90 days, or lives in a long-term care facility, or has received chemotherapy or IV antibiotics, ");
//    WriteComment("This is VAP, since it started after the patient had been intubated for 48 hours");
//    WriteComment("For HCAP:");
//    WriteVancomycinPlan(true, true);
//    WritePipTazoPlan(true);
//    WriteAction("Tobramycin (double coverage for Pseudomonas unless CKD)");
//    WriteComment("For CAP:");
//    WriteAction("Ceftriaxone or Levofloxacin (Strep pneumo and gram negative coverage)");
//    WriteAction("Azithromycin (cover atypicals, also possible anti-inflammatory) 500mg IV x3days");
} // WritePneumoniaPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteStrokePlan]
//
// 2023-11-14 - Combined workup labs into a single task
////////////////////////////////////////////////////////////////////////////////
function 
WriteStrokePlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Stroke";
    modifierStr = MedNote_GetCPOptionValue("StrokeAcuteOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr + " " + planStr;
    }
    if (PrintSingleLinePlanAtEnd('StrokePlan', planStr, "Continue home medications: ")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "StrokePlan");
    if (!activeControlPanel) {
        LogEvent("WriteStrokePlan. activeControlPanel is null");
        return;
    }

    WriteCommentIfSelected(activeControlPanel, "StrokeOnsetOption");

    WriteActionIfSelected(activeControlPanel, "StrokeImagingHeadCTOption");
    WriteActionIfSelected(activeControlPanel, "StrokeImagingCTAOption");
    WriteActionIfSelected(activeControlPanel, "StrokeImagingMRIOption");
    WriteActionIfSelected(activeControlPanel, "StrokeImagingCarotidOption");
    WriteActionIfSelected(activeControlPanel, "StrokeImagingEchoOption");

    var optionNameList = [ 'StrokeGetA1cOption', 'StrokeGetLDLOption', 'StrokeGetINROption', 'StrokeGetSMEAROption',
                            'StrokeGetHaptoglobinsOption',  'StrokeGetLDHOption']; 
    WriteListOfSelectedActions(activeControlPanel, "Check ", optionNameList)

    // Anticoag
    WriteActionIfSelected(activeControlPanel, "StrokeHoldDay1Option");
    WriteActionIfSelected(activeControlPanel, "StrokeAsaOnDay2Option");
    WriteActionIfSelected(activeControlPanel, "StrokeSCDsOption");

    // Hypertension
    WriteActionIfSelected(activeControlPanel, "StrokeHTNDay1HoldOption");
    WriteActionIfSelected(activeControlPanel, "StrokeHTNDay2ResumeOption");

    // Dysphagia
    WriteActionIfSelected(activeControlPanel, "StrokeDysphagiaNPOOption");
    WriteActionIfSelected(activeControlPanel, "StrokeDysphagiaStudyOption");

    // Management
    WriteActionIfSelected(activeControlPanel, "StrokeAsaOption");
    WriteActionIfSelected(activeControlPanel, "StrokeStatinOption");

    // No keppra ppx unless symptoms of seizure

//    tPA within 3-4.5 hours of onset unless:
//        Age over 80yo
//        Oral anticoagulants (regardless of INR), or any dose within the past 2 days
//        NIHSS score over 25
//        Past history of stroke and diabetes
//        Imaging shows infarct covering more than 1/3 of the MCA territory
} // WriteStrokePlan







////////////////////////////////////////////////////////////////////////////////
//
// [WriteAFibPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteAFibPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Atrial Fibrillation";
    modifierStr = MedNote_GetCPOptionValue("AFibParoxtsmalOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr + planStr;
    }
    modifierStr = MedNote_GetCPOptionValue("AFibRVROption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr += modifierStr;
    }

    activeControlPanel = MedNote_StartNewPlanSection(planStr, "AFibPlan");
    if (!activeControlPanel) {
        LogEvent("xxxxx. activeControlPanel is null");
        return;
    }

    var optionNameList = [ "AFibCHADSVaSCCHFOption", "AFibCHADSVaSCHypertensionOption", 
                            "AFibCHADSVaSCOver75yoOption", "AFibCHADSVaSCDiabetesOption", 
                            "AFibCHADSVaSCPVDOption", "AFibCHADSVaSCOver65yoOption", 
                            "AFibCHADSVaSCStrokeOption", "AFibCHADSVaSCFemaleOption"];
    WriteListOfSelectedValues(activeControlPanel, "CHADS2VASc = ", true, " (", optionNameList, ")");

    WriteCommentIfSelected(activeControlPanel, "AFibCHADSVaSCValvularOption");

    var optionNameList = [ "AFibHasBLEDSBPOver160Option", "AFibHasBLEDESRDorCrOver2Option", 
                            "AFibHasBLEDCirrhosisOption", "AFibHasBLEDStrokeOption", 
                            "AFibHasBLEDPastBleedOption", "AFibHasBLEDLabileINROption",
                            "AFibHasBLEDOnAntiPltOption",
                            "AFibHasBLEDOver65yoOption", "AFibHasBLEDEtOHOption"];
    WriteListOfSelectedValues(activeControlPanel, "Has-BLED = ", true, " (", optionNameList, ")");

    var optionNameList = [ "AFibRisksPastDVTOption", "AFibRisksPastCVAOption", 
                            "AFibRisksCADOption", "AFibHasBLEDStrokeOption", 
                            "AFibHasBLEDPastBleedOption", "AFibRisksOCPOption",
                            "AFibRisksMiscarriageOption", "AFibRisksFamilyOption"];
    WriteListOfSelectedValues(activeControlPanel, "Additional risk factors include ", false, "", optionNameList, "");

    var optionNameList = [ "AFibHomeCoumadinOption", "AFibHomeApixibanOption" ];
    WriteListOfSelectedValues(activeControlPanel, "Home medications are ", false, "", optionNameList, "");

    // Eval
    WriteActionIfSelected(activeControlPanel, "AFibCheckEKGOption");
    WriteActionIfSelected(activeControlPanel, "AFibGetEchoOption");
    WriteActionIfSelected(activeControlPanel, "AFibUDSOption");
    WriteActionIfSelected(activeControlPanel, "AFibTSHOption");
    WriteActionIfSelected(activeControlPanel, "AFibKMgOption");

    // Rate control
    WriteActionIfSelected(activeControlPanel, "AFibMetoprololTarOption");
    WriteActionIfSelected(activeControlPanel, "AFibMetoprololSuccOption");
    WriteActionIfSelected(activeControlPanel, "AFibCarvedilolOption");
    WriteActionIfSelected(activeControlPanel, "AFibDiltiazemPOOption");

    // IV and Drips
    WriteActionIfSelected(activeControlPanel, "AFibIVMetoprololOption");
    WriteActionIfSelected(activeControlPanel, "AFibDiltiazemDripOption");
    WriteActionIfSelected(activeControlPanel, "AFibAmiodaroneDripOption");
    WriteActionIfSelected(activeControlPanel, "AFibHRTargetOption");

    // Anti-Plt
    WriteActionIfSelected(activeControlPanel, "AFibAsaOption");
    WriteActionIfSelected(activeControlPanel, "AFibApixabanOption");
    WriteActionIfSelected(activeControlPanel, "AFibRivaroxabanOption");
    WriteActionIfSelected(activeControlPanel, "AFibCoumadinOption");
    WriteActionIfSelected(activeControlPanel, "AFibOnlyCoumadinOption");

    // Manage Other
    WriteActionIfSelected(activeControlPanel, "AFibManageOption");
    WriteActionIfSelected(activeControlPanel, "AFibManageInfectionOption");
    WriteActionIfSelected(activeControlPanel, "AFibManageCHFOption");
    WriteActionIfSelected(activeControlPanel, "AFibManageOSAOption");
} // WriteAFibPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteAsthmaPlan]
//
// 2023-11-14 - Combined workup labs into a single task
////////////////////////////////////////////////////////////////////////////////
function 
WriteAsthmaPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Asthma";
    if (PrintSingleLinePlanAtEnd('AsthmaPlan', planStr, "Continue as needed short-acting beta agonist")) {
        return
    }
    modifierStr = MedNote_GetCPOptionValue("AsthmaExacerbationOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr;
    }

    activeControlPanel = MedNote_StartNewPlanSection(planStr, "AsthmaPlan");
    if (!activeControlPanel) {
        LogEvent("xxxxx. activeControlPanel is null");
        return;
    }

    // Exacerbation
    WriteCommentIfSelected(activeControlPanel, "AsthmaExacerbationTypeOption"); 

    // Staging
    WriteCommentIfSelected(activeControlPanel, "AsthmaTypeOption"); 
 
    // Triggers
    var optionNameList = [ "AsthmaTriggerInfectionOption", "AsthmaTriggerSmokingOption", "AsthmaTriggerComplianceOption", "AsthmaTriggerMedChangesOption"];
    WriteListOfSelectedValues(activeControlPanel, "Possible triggers for this exacerbation include: ", false, "", optionNameList, "");

    // Vitals
    var optionNameList = [ "AsthmaCurrentO2SatsOption", "AsthmaCurrentO2Option", "AsthmaCurrentCPAPOption"];
    WriteListOfSelectedValues(activeControlPanel, "", false, "", optionNameList, "");
    WriteCommentIfSelected(activeControlPanel, "AsthmaO2VBGOption"); 
 
    // Workup
    WriteActionIfSelected(activeControlPanel, "AsthmaXrayOption"); 
    WriteActionIfSelected(activeControlPanel, "AsthmaGetABGOption"); 
    var optionNameList = [ 'AsthmaGetCBCOption', 'AsthmaGetRVPOption', 'AsthmaProcalOption',
                            'AsthmaCultureSputOption',  'AsthmaCultureBloodOption', 'AsthmaUrineAntigensOption']; 
    WriteListOfSelectedActions(activeControlPanel, "Check ", optionNameList)
 
    // Bronchodilators
    WriteActionIfSelected(activeControlPanel, "AsthmaNebsOption"); 
    WriteActionIfSelected(activeControlPanel, "AsthmaHFAOption"); 
    WriteActionIfSelected(activeControlPanel, "AsthmaLABAOption"); 
    // WriteAction("Mg 2g IV once");
 
    // AntiInflammatory
    WriteActionIfSelected(activeControlPanel, "AsthmaPrednisoneOption"); 
    WriteActionIfSelected(activeControlPanel, "AsthmaPPIOption"); 
    WriteActionIfSelected(activeControlPanel, "AsthmaH1BlockerOption"); 
    WriteActionIfSelected(activeControlPanel, "AsthmaH2BlockerOption"); 
 
    // Oxygen
    WriteActionIfSelected(activeControlPanel, "AsthmaGiveO2Option"); 
    WriteActionIfSelected(activeControlPanel, "AsthmaGuaifenesinOption"); 
    WriteActionIfSelected(activeControlPanel, "AsthmaPneumovaxOption"); 
} // WriteAsthmaPlan








////////////////////////////////////////////////////////////////////////////////
//
// [WriteRenalTransplantPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteRenalTransplantPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Renal Transplant";
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "RenalTransplantPlan");
    if (!activeControlPanel) {
        LogEvent("xxxxx. activeControlPanel is null");
        return;
    }

    // History
    WriteCommentIfSelected(activeControlPanel, "RenalTransplantTypeOption"); 
    WriteCommentIfSelected(activeControlPanel, "RenalTransplantDateOption"); 
    WriteCommentIfSelected(activeControlPanel, "RenalTransplantNephrologistOption"); 
    WriteCommentIfSelected(activeControlPanel, "RenalTransplantBaselineCrOption"); 
    WriteCommentIfSelected(activeControlPanel, "RenalTransplantRecentTacLevelOption"); 
    //WriteComment("Tacrolimus Level=xxx");
 
    // Home IS
    var optionNameList = [ "RenalTransplantTacroOption", "RenalTransplantMMFOption", "RenalTransplantAzathioprineOption", "RenalTransplantPrednisoneOption"];
    WriteListOfSelectedValues(activeControlPanel, "Home immunosuppression is: ", false, "", optionNameList, "");

    // Inpatient IS
    WriteActionIfSelected(activeControlPanel, "RenalTransplantIPTacroOption"); 
    WriteActionIfSelected(activeControlPanel, "RenalTransplantIPMMFOption"); 
    WriteActionIfSelected(activeControlPanel, "RenalTransplantIPAzathioprineOption"); 
    WriteActionIfSelected(activeControlPanel, "RenalTransplantIPPrednisoneOption"); 
 
    // Monitor
    WriteActionIfSelected(activeControlPanel, "RenalTransplantCheckTacLevelOption"); 
 
    // AKI
    WriteActionIfSelected(activeControlPanel, "RenalTransplantCheckDSAOption"); 
    WriteActionIfSelected(activeControlPanel, "RenalTransplantTransplantUSOption"); 
    WriteActionIfSelected(activeControlPanel, "RenalTransplantCheckCMVOption"); 
    WriteActionIfSelected(activeControlPanel, "RenalTransplantCheckEBVOption"); 
    WriteActionIfSelected(activeControlPanel, "RenalTransplantCheckBKOption"); 
} // WriteRenalTransplantPlan







////////////////////////////////////////////////////////////////////////////////
//
// [WriteNephrolithiasisPlan]
//
// Updated 2022-11-3
////////////////////////////////////////////////////////////////////////////////
function 
WriteNephrolithiasisPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Nephrolithiasis";
    if (PrintSingleLinePlanAtEnd('NephrolithiasisPlan', planStr, "Monitor")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "NephrolithiasisPlan");
    if (!activeControlPanel) {
        LogEvent("xxxxx. activeControlPanel is null");
        return;
    }

    // History
    WriteCommentIfSelected(activeControlPanel, "NephrolithiasisShowLatestStoneOption");
    WriteCommentIfSelected(activeControlPanel, "NephrolithiasisRateOption");
    var optionNameList = [ "NephrolithiasisStoneTypeOption"];
    WriteListOfSelectedValues(activeControlPanel, "Previous stones were ", false, "", optionNameList, "");

    // Urine
    WriteCommentIfSelected(activeControlPanel, "NephrolithiasisShowUrinepHOption");
    WriteCommentIfSelected(activeControlPanel, "NephrolithiasisShowUrineSedimentOption");
 
    // 24hr Urine
    // WriteComment("24hr urine labs:");
    WriteCommentIfSelected(activeControlPanel, "Nephrolithiasis24hrUrineVolumeOption");
    WriteCommentIfSelected(activeControlPanel, "Nephrolithiasis24hrUrineCalciumOption");
    WriteCommentIfSelected(activeControlPanel, "Nephrolithiasis24hrUrineCitrateOption");
    WriteCommentIfSelected(activeControlPanel, "Nephrolithiasis24hrUrinePhosOption");
    WriteCommentIfSelected(activeControlPanel, "Nephrolithiasis24hrUrineSodiumOption");
    WriteCommentIfSelected(activeControlPanel, "Nephrolithiasis24hrUrineChlorideOption");
    WriteCommentIfSelected(activeControlPanel, "Nephrolithiasis24hrUrineUrateOption");
    WriteCommentIfSelected(activeControlPanel, "Nephrolithiasis24hrUrineOxalateOption");
    WriteCommentIfSelected(activeControlPanel, "Nephrolithiasis24hrUrineSulfateOption");
 
    // Workup
    WriteActionIfSelected(activeControlPanel, "NephrolithiasisGetUAOption");
    WriteActionIfSelected(activeControlPanel, "NephrolithiasisGet24hrOption");
    WriteActionIfSelected(activeControlPanel, "NephrolithiasisGetUSOption");
    WriteActionIfSelected(activeControlPanel, "NephrolithiasisGetCTOption");

    // Treat
    WriteActionIfSelected(activeControlPanel, "Nephrolithiasis2LPOFluidOption");
    WriteActionIfSelected(activeControlPanel, "NephrolithiasisLowNaDietOption");
    WriteActionIfSelected(activeControlPanel, "NephrolithiasisKCitrateOption");
    WriteActionIfSelected(activeControlPanel, "NephrolithiasisThiazideOption");
    WriteActionIfSelected(activeControlPanel, "NephrolithiasisFollowupRenalOption");
} // WriteNephrolithiasisPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteNephroticPlan]
//
// Updated 2022-10-30
// 2023-11-14 - Combined workup labs into a single task
////////////////////////////////////////////////////////////////////////////////
function 
WriteNephroticPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Nephrotic Proteinuria";
    modifierStr = MedNote_GetCPOptionValue("NephroticSyndromeOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr;
    }

    activeControlPanel = MedNote_StartNewPlanSection(planStr, "NephroticPlan");
    if (!activeControlPanel) {
        LogEvent("xxxxx. activeControlPanel is null");
        return;
    }

    var urineProtein = GetIntInputForControlPanel(activeControlPanel, "InputUrineProtein_CP");
    var urineAlbumin = GetIntInputForControlPanel(activeControlPanel, "InputUrineAlbuminCP");
    var urineCreatinine = GetIntInputForControlPanel(activeControlPanel, "InputUrineCreatinineCP");
    var serumAlbumin = GetIntInputForControlPanel(activeControlPanel, "SerumAlbuminCP");
    var urineProtCrRatio = -1
    var urineAlbCrRatio = -1

    if ((urineProtein > 0) && (urineCreatinine > 0)) {
        urineProtCrRatio = urineProtein / urineCreatinine;
        SetStrOutputForControlPanel(activeControlPanel, 'ResultUPCRCP', null, 'urineProtCrRatio = ' + urineProtCrRatio);
    }
    if ((urineAlbumin > 0) && (urineCreatinine > 0)) {
        urineAlbCrRatio = urineAlbumin / urineCreatinine;
        SetStrOutputForControlPanel(activeControlPanel, 'ResultNonAlbuminUPCR', null, 'urineAlbCrRatio = ' + urineAlbCrRatio);
    }


    // Labs
    planStr = MedNote_GetCPOptionValue("NephroticShowUrineProtCreatRatioOption");
    if ((planStr != null) && (planStr != "")) {
        if (urineProtCrRatio > 0) {
            planStr += urineProtCrRatio;
        }
        WriteComment(planStr);
    }
    planStr = MedNote_GetCPOptionValue("NephroticShowUrineAlbCreatRatioOption");
    if ((planStr != null) && (planStr != "")) {
        if (urineAlbCrRatio > 0) {
            planStr += urineAlbCrRatio;
        }
        WriteComment(planStr);
    }
    WriteCommentIfSelected(activeControlPanel, "NephroticShowSerumAlbuminOption"); 
    WriteCommentIfSelected(activeControlPanel, "NephroticExplainRatioOption"); 

    // Etiology
    var optionNameList = [ "NephroticDiffDiabetesOption", "NephroticDiffSLEOption", "NephroticDiffHepBOption", "NephroticDiffHepCOption", "NephroticDiffHIVOption", "NephroticDiffAmyloidosis", "NephroticDiffPreeclampsiaOption", "NephroticDiffFSGSOption", "NephroticDiffMembranousOption", "NephroticDiffMinimalChangeOption", "NephroticDiffNSAIDsOption", "NephroticDiffTamoxifenOption", "NephroticDiffLithiumOption"];
    WriteListOfSelectedValues(activeControlPanel, "The differential includes: ", false, "", optionNameList, "");


    // Workup
    var optionNameList = [ 'NephroticWorkupA1cOption', 'NephroticWorkupLightChainsOption', 'NephroticWorkupSPEPOption', 
                            'NephroticWorkupRheumatoidFactorOption', 'NephroticWorkupCryoglobulinsOption',
                            'NephroticWorkupANAOption', 'NephroticWorkupC3C4Option', 'NephroticWorkupAntiGBMOption',
                            'NephroticWorkupPLA2ROption', 'NephroticWorkupHIVOption', 'NephroticWorkupHepBOption',
                            'NephroticWorkupHepCOption', 'NephroticWorkupSyphilisOption']; 
    WriteListOfSelectedActions(activeControlPanel, "Check for causes: ", optionNameList)

    var optionNameList = [ 'NephroticTreatCancerScreenOption', 'NephroticTreatCheckTSHOption', 'NephroticTreatCheckLDLOption']; 
    WriteListOfSelectedActions(activeControlPanel, "Check for effects of nephrotic: ", optionNameList)

    // Treat
    WriteActionIfSelected(activeControlPanel, "NephroticTreatLasixPOOption");
    WriteActionIfSelected(activeControlPanel, "NephroticTreatACEOption");
    WriteCommentIfSelected(activeControlPanel, "NephroticTreatExplainACEOption");
    WriteActionIfSelected(activeControlPanel, "NephroticTreatAnticoagulationOption");
    WriteCommentIfSelected(activeControlPanel, "NephroticTreatCriteriaAnticoagulationOption");
} // WriteNephroticPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteEtOHPlan]
//
// Excessive drinking includes binge drinking, heavy drinking, and any drinking by pregnant women or people younger than age 21.
// 
//     Binge drinking, the most common form of excessive drinking, is defined as consuming
//         For women, 4 or more drinks during a single occasion.
//         For men, 5 or more drinks during a single occasion.
//     Heavy drinking is defined as consuming
//         For women, 8 or more drinks per week.
//         For men, 15 or more drinks per week.

// Most people who drink excessively are not alcoholics or alcohol dependent.5
// What is moderate drinking?

// The Dietary Guidelines for Americans defines moderate drinking as up to 1 drink per day for women and up to 2 drinks per day for men.4 In addition, the Dietary Guidelines do not recommend that individuals who do not drink alcohol start drinking for any reason.
// https://www.cdc.gov/alcohol/fact-sheets/alcohol-use.htm

////////////////////////////////////////////////////////////////////////////////
function 
WriteEtOHPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    var withdrawalsPlanStr = MedNote_GetCPOptionValue("EtOHWithdrawalsModifier");

    // Pick a primary plan.
    planStr = "Alcohol Use Disorder";
    if ((withdrawalsPlanStr != null) && (withdrawalsPlanStr != "")) {
        planStr = withdrawalsPlanStr;
    }

    if (PrintSingleLinePlanAtEnd('EtOHPlan', planStr, "Monitor for withdrawal")) {
        return
    }

    // Start the problem.
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "EtOHPlan");
    if (!activeControlPanel) {
        LogEvent("WriteEtOHPlan. activeControlPanel is null");
        return;
    }

    // Write secondary plans    
    if ((withdrawalsPlanStr != null) && (withdrawalsPlanStr != "")) {
        MedNote_AddRelatedProblem("Toxic Encephalopathy due to Alcohol Withdrawals");
    }

    var optionNameList = [ "EtOHDailyUseOption", "EtOHLastUseOption"];
    WriteListOfSelectedValues(activeControlPanel, "", false, "", optionNameList, "")

    planStr = MedNote_GetCPOptionValue("EtOHPastWithdrawalsOption");
    if ((planStr != null) && (planStr != "")) {
        modifierStr = MedNote_GetCPOptionValue("EtOHPastSeizuresOption");
        if ((modifierStr != null) && (modifierStr != "")) {
            planStr += " " + modifierStr;
        }
        WriteComment(planStr);
    }
    WriteCommentIfSelected(activeControlPanel, "EtOHAABookOption");

    WriteActionIfSelected(activeControlPanel, "EtOHCIWAOption");
    WriteActionIfSelected(activeControlPanel, "EtOHThiamineOption");
    WriteActionIfSelected(activeControlPanel, "EtOHVitaminsOption");
    //Chlorthiazepoxide
} // WriteEtOHPlan






////////////////////////////////////////////////////////////////////////////////
//
// [WriteHypokalemiaPlan]
//
// Updated 2022-10-31
// 2023-11-14 - Combined workup labs into a single task
////////////////////////////////////////////////////////////////////////////////
function 
WriteHypokalemiaPlan() {    
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Hypokalemia";
    if (PrintSingleLinePlanAtEnd('HypokalemiaPlan', planStr, "Monitor and replace as needed")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "HypokalemiaPlan");
    if (!activeControlPanel) {
        LogEvent("WriteHypokalemiaPlan. activeControlPanel is null");
        return;
    }

    // Get the inputs
    var currentK = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_K_CP');
    var currentCr = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_Cr_CP');
    var currentMg = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_Mg_CP');
    var serumOsm = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_OSM_CP');
    var currentUrineK = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_URINE_K_CP');
    var currentUrineCr = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_URINE_CR_CP');
    var currentUrineCl = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_URINE_CL_CP');
    var urineOsm = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_URINE_OSM_CP');


    var optionNameList = [ "LowPotassiumShowKOption", "LowPotassiumShowMgOption", "LowPotassiumShowUrClOption"];
    var valueList = [ "", "", ""];
    var valueNameList = [ "INPUT_SERUM_K_CP", "INPUT_SERUM_Mg_CP", "INPUT_URINE_CL_CP"];
    WriteListOfSelectedValuesWithDescriptions(activeControlPanel, optionNameList, valueList, valueNameList)

    ///////////////////////////////////////////
    // Trans-Tubular Potassium Gradient
    planStr = MedNote_GetCPOptionValue("LowPotassiumShowTTKGOption");
    if ((planStr != null) && (planStr != "")) {
        if ((currentUrineK > 0) && (serumOsm > 0) && (currentK > 0) && (urineOsm > 0)) {
            var transTubularKGradient = (currentUrineK / currentK) / (urineOsm / serumOsm);
            transTubularKGradient = Math.round((transTubularKGradient + 0.00001) * 10) / 10;
            planStr += transTubularKGradient;
        } 
        WriteComment(planStr);
    }
    WriteCommentIfSelected(activeControlPanel, 'LowPotassiumExplainLowTTKGOption');

    ///////////////////////////////////////////
    // Fractional Excretion Potassium
    planStr = MedNote_GetCPOptionValue("LowPotassiumShowFEKOption");
    if ((planStr != null) && (planStr != "")) {
        if ((currentUrineK > 0) && (currentK > 0) && (currentUrineCr > 0) && (currentCr > 0)) {
            var FEPot = (currentUrineK / currentK) / (currentUrineCr / currentCr);
            // Convert to a percentage
            FEPot = FEPot * 100;
            // Round it to 2 decimal places. We add 0.00001 to work around a Javascript bug.
            FEPot = Math.round((FEPot + 0.00001) * 100) / 100;
            planStr += FEPot + " percent";
        } 
        WriteComment(planStr);
    }
    WriteCommentIfSelected(activeControlPanel, 'LowPotassiumExplainFEKGOption');

    WriteCommentIfSelected(activeControlPanel, 'LowPotassiumInterpretUrClOption');
    WriteCommentIfSelected(activeControlPanel, 'LowPotassiumExplainUrClOption');

    var optionNameList = [ "LowPotassiumCausesDiarrheaOption", "LowPotassiumCausesRenalOption", "LowPotassiumCausesDiureticsOption", "LowPotassiumCausesLowMgOption", "LowPotassiumCausesHighAldoOption", "LowPotassiumCausesHyperAaldoOption", "LowPotassiumCausesRASOption", "LowPotassiumCausesMalnutritionOption", "LowPotassiumCausesTubeFeedsOption" ];
    WriteListOfSelectedValues(activeControlPanel, "Possible causes include: ", false, "", optionNameList, "");

    var optionNameList = [ 'LowPotassiumCheckMgOption', 'LowPotassiumCheckUrChlorideOption', 'LowPotassiumCheckULytesOption']; 
    WriteListOfSelectedActions(activeControlPanel, "Check ", optionNameList)

    WriteActionIfSelected(activeControlPanel, "LowPotassiumRepleteKOption");
    WriteActionIfSelected(activeControlPanel, "LowPotassiumRepleteMgOption");
} // WriteHypokalemiaPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteHypERkalemiaPlan]
//
// Updated 2022-11-2
////////////////////////////////////////////////////////////////////////////////
function 
WriteHypERkalemiaPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Hyperkalemia";
    if (PrintSingleLinePlanAtEnd('HyperkalemiaPlan', planStr, "Monitor")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "HyperkalemiaPlan");
    if (!activeControlPanel) {
        LogEvent("WriteHypERkalemiaPlan. activeControlPanel is null");
        return;
    }

    // Get the inputs
    var currentK = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_K_CP');
    var currentCr = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_Cr_CP');
    var serumOsm = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_OSM_CP');
    var currentUrineK = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_URINE_K_CP');
    var currentUrineCr = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_URINE_CR_CP');
    var urineOsm = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_URINE_OSM_CP');

    var optionNameList = [ "HighPotassiumShowKOption"];
    var valueList = [ "", "", ""];
    var valueNameList = [ "INPUT_SERUM_K_CP"];
    WriteListOfSelectedValuesWithDescriptions(activeControlPanel, optionNameList, valueList, valueNameList)
    WriteCommentIfSelected(activeControlPanel, "HighPotassiumShowEKGOption");

    ///////////////////////////////////////////
    // Trans-Tubular Potassium Gradient
    planStr = MedNote_GetCPOptionValue("HighPotassiumShowTTKGOption");
    if ((planStr != null) && (planStr != "")) {
        if ((currentUrineK > 0) && (serumOsm > 0) && (currentK > 0) && (urineOsm > 0)) {
            var transTubularKGradient = (currentUrineK / currentK) / (urineOsm / serumOsm);
            transTubularKGradient = Math.round((transTubularKGradient + 0.00001) * 10) / 10;
            planStr += transTubularKGradient;
        } 
        WriteComment(planStr);
    }
    WriteCommentIfSelected(activeControlPanel, "HighPotassiumExplainLowTTKGOption");
    ///////////////////////////////////////////
    // Fractional Excretion Potassium
    planStr = MedNote_GetCPOptionValue("HighPotassiumShowFEKOption");
    if ((planStr != null) && (planStr != "")) {
        if ((currentUrineK > 0) && (currentK > 0) && (currentUrineCr > 0) && (currentCr > 0)) {
            var FEPot = (currentUrineK / currentK) / (currentUrineCr / currentCr);
            // Convert to a percentage
            FEPot = FEPot * 100;
            // Round it to 2 decimal places. We add 0.00001 to work around a Javascript bug.
            FEPot = Math.round((FEPot + 0.00001) * 100) / 100;
            planStr += FEPot + " percent";
        } 
        WriteComment(planStr);
    }
    WriteCommentIfSelected(activeControlPanel, 'HighPotassiumExplainFEKGOption');

    var optionNameList = [ "HighPotassiumEtiologyRTA4Option", "HighPotassiumEtiologySeizuresOption", "HighPotassiumEtiologyTumorLysisOption", 
                            "HighPotassiumEtiologySaltSubstituteOption", "HighPotassiumEtiologyDigoxinOption" ];
    WriteListOfSelectedValues(activeControlPanel, "Possible causes include: ", false, "", optionNameList, "");

    WriteActionIfSelected(activeControlPanel, "HighPotassiumCheckEKGOption");
    WriteActionIfSelected(activeControlPanel, "HighPotassiumCheckULytesOption");
    WriteActionIfSelected(activeControlPanel, "HighPotassiumCaIVOption");
    WriteActionIfSelected(activeControlPanel, "HighPotassiumBinderResinOption");
    WriteActionIfSelected(activeControlPanel, "HighPotassiumInsulinD50WOption");
    WriteActionIfSelected(activeControlPanel, "HighPotassiumFurosemideOption");
    WriteActionIfSelected(activeControlPanel, "HighPotassiumBicarbonateOption");
    WriteActionIfSelected(activeControlPanel, "HighPotassiumAlbuterolOption");
} // WriteHypERkalemiaPlan






////////////////////////////////////////////////////////////////////////////////
//
// [PrintHyperNatremiaPlan]
//
// Updated 2022-10-30
////////////////////////////////////////////////////////////////////////////////
function 
PrintHyperNatremiaPlan() {    
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Hypernatremia";
    if (PrintSingleLinePlanAtEnd('HypERnatremiaPlan', planStr, "Continue free water")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "HypERnatremiaPlan");
    if (!activeControlPanel) {
        LogEvent("PrintHyperNatremiaPlan. activeControlPanel is null");
        return;
    }

    ///////////////////
    // Read Inputs and do Calculations
    var currentNa = GetIntInputForControlPanel(activeControlPanel, 'HIGH_NA_INPUT_SERUM_NA_CP');
    var currentWt = GetIntInputForControlPanel(activeControlPanel, 'HIGH_NA_INPUT_WT_CP');
    var currentUOsm = GetIntInputForControlPanel(activeControlPanel, 'InputUrineOsm_CP');
    var currentUNa = GetIntInputForControlPanel(activeControlPanel, 'InputUrineNa_CP');

    // Total Body Water is used by several values, so let's compute it once now.
    // There are some many ways to estimate this.
    //
    // Watson:
    // Male TBW =  2.447 - (0.09156 x age) + (0.1074 x height) + (0.3362 x weight) 
    // Female TBW =  -2.097 + (0.1069 x height) + (0.2466 x weight) 
    // Watson PE, Watson ID, Batt RD. Total body water volumes for adult males and females estimated from simple anthropometric measurements. Am J Clin Nutr 33:27-39, 1980.
    //
    // Hume-Weyers:
    // Male TBW =  (0.194786 x height) + (0.296785 x weight) - 14.012934 
    // Female TBW =  (0.34454 x height) + (0.183809 x weight) - 35.270121 
    // Hume R, Weyers E. Relationship between total body water and surface area in normal and obese subjects. J Clin Pathol 24:234-238, 1971.
    //
    // Chertow's Bioelectrical Impedance:
    // TBW =  ht x (0.0186104 x wt + 0.12703384) + wt x (0.11262857 x male + 0.00104135 x age - 0.00067247 x wt - 0.04012056) - age x (0.03486146 x male + 0.07493713) - male x 1.01767992 + diabetes x 0.57894981 
    // Chertow GM, Lowrie EG, Lew NL, Lazarus JM. Development of a population-specific regression equation to estimate total body water in hemodialysis patients. 
    //      Kid Int 51:1578-1582, 1997.
    //
    // I use a much simpler method, which scales mass. But, the scale can vary depending on sex and age
    // Children: 0.6 
    // Adult men: 0.6 
    // Adult women: 0.5 
    // Geriatric (?age) men: 0.5 
    // Geriatric (age?) women: 0.45
    var EstimatedTotalBodyWater = -1;
    if (currentWt > 0) {
        EstimatedTotalBodyWater = 0.6 * currentWt;
    }

    WriteCommentIfSelected(activeControlPanel, 'HighNaExplainOption');

    var optionNameList = [ "HighNaShowNaOption", "HighNaShowUrineOsmOption", "HighNaShowUrineNaOption"];
    var valueList = [ "", "", ""];
    var valueNameList = [ "HIGH_NA_INPUT_SERUM_NA_CP", "InputUrineOsm_CP", "InputUrineNa_CP"];
    WriteListOfSelectedValuesWithDescriptions(activeControlPanel, optionNameList, valueList, valueNameList)

    planStr = MedNote_GetCPOptionValue("HighNaFreeWaterDeficitOption");
    if ((planStr != null) && (planStr != "")) {
        // Free Water Deficit
        if ((currentNa > 0) && (EstimatedTotalBodyWater > 0)) {
            var freeWaterDeficit = EstimatedTotalBodyWater * ((currentNa / 140) - 1);
            // This is in liters, so round to the nearest 10th
            freeWaterDeficit = Math.round((freeWaterDeficit + 0.00001) * 10) / 10;
            planStr += freeWaterDeficit + " liters";
        }
        WriteComment(planStr);
    }

    var optionNameList = [ "HighNaCausesLowIntakeOption", "HighNaCausesDiarreaOption", "HighNaCausesBurnsOption", "HighNaCausesPostATNOption", "HighNaCausesTPNOption", "HighNaCausesLithiumOption", "HighNaCausesCisplatinOption" ];
    WriteListOfSelectedValues(activeControlPanel, "Possible causes include: ", false, "", optionNameList, "");

    WriteActionIfSelected(activeControlPanel, "HighNaGiveD5WOption");
    WriteActionIfSelected(activeControlPanel, "HighNaTubeFeedFreeWaterOption");
    WriteActionIfSelected(activeControlPanel, "HighNaDDAVPOption");
} // PrintHyperNatremiaPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteHypomagnesemiaPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteHypomagnesemiaPlan() { 
    var activeControlPanel = null;
    var planStr = "";

    planStr = "Hypomagnesemia";
    if (PrintSingleLinePlanAtEnd('HypomagnesemiaPlan', planStr, "Monitor and replace as needed")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "HypomagnesemiaPlan");
    if (!activeControlPanel) {
        LogEvent("WriteHypomagnesemiaPlan. activeControlPanel is null");
        return;
    }

    var optionNameList = [ "LowMgShowMgOption"];
    var valueList = [ ""];
    var valueNameList = [ "ControlPanel_Mg_Input"];
    WriteListOfSelectedValuesWithDescriptions(activeControlPanel, optionNameList, valueList, valueNameList)

    WriteActionIfSelected(activeControlPanel, "LowMgCheckUrineOption");
    WriteActionIfSelected(activeControlPanel, "LowMgRepleteOption");
} // WriteHypomagnesemiaPlan




////////////////////////////////////////////////////////////////////////////////
//
// [WriteHypoPhosPlan]
//
// Updated 2022-11-2
////////////////////////////////////////////////////////////////////////////////
function 
WriteHypoPhosPlan() { 
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "HypoPhosphatemia";
    if (PrintSingleLinePlanAtEnd('HypoPhosPlan', planStr, "Monitor and replace as needed")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "HypoPhosPlan");
    if (!activeControlPanel) {
        LogEvent("WriteHypoPhosPlan. activeControlPanel is null");
        return;
    }

    // Get the inputs
    var currentPhos = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_Phos_CP');
    var currentCr = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_Cr_CP');
    var currentPTH = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_PTH_CP');
    var currentCa = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_Ca_CP');
    var currentUrinePhos = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_URINE_Phos_CP');
    var currentUrineCr = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_URINE_CR_CP');

    var optionNameList = [ "LowPhosShowPhosOption", "LowPhosShowPTHOption", "LowPhosShowCalciumOption"];
    var valueList = [ "", "", "", ""];
    var valueNameList = [ "INPUT_SERUM_Phos_CP", "INPUT_SERUM_PTH_CP", "INPUT_SERUM_Ca_CP"];
    WriteListOfSelectedValuesWithDescriptions(activeControlPanel, optionNameList, valueList, valueNameList)

    ///////////////////////////////////////////
    // Fractional Excretion Phos
    planStr = MedNote_GetCPOptionValue("LowPhosShowFEPhosOption");
    if ((planStr != null) && (planStr != "")) {
        if ((currentUrinePhos > 0) && (currentPhos > 0) && (currentUrineCr > 0) && (currentCr > 0)) {
            var FEPhos = (currentUrinePhos / currentPhos) / (currentUrineCr / currentCr);
            // Convert to a percentage
            FEPhos = FEPhos * 100;
            // Round it to 2 decimal places. We add 0.00001 to work around a Javascript bug.
            FEPhos = Math.round((FEPhos + 0.00001) * 100) / 100;
            planStr += FEPhos + " percent";
        } 
        WriteComment(planStr);
    }
    WriteCommentIfSelected(activeControlPanel, 'LowPhosExplainFEPhosOption');

    WriteActionIfSelected(activeControlPanel, "LowPhosCheckUrineOption");
    WriteActionIfSelected(activeControlPanel, "LowPhosCheckPTHOption");

    WriteActionIfSelected(activeControlPanel, "LowPhosTreatIVOption");
    WriteActionIfSelected(activeControlPanel, "LowPhosTreatPOOption");
    WriteActionIfSelected(activeControlPanel, "LowPhosRepleteOption");
    WriteActionIfSelected(activeControlPanel, "LowPhosFixCalOption");
} // WriteHypoPhosPlan




////////////////////////////////////////////////////////////////////////////////
//
// [WriteHypoCalcemiaPlan]
//
// 2022-11-2 - Updated
// 2023-21-14 - Combined workup labs into a single task
////////////////////////////////////////////////////////////////////////////////
function 
WriteHypoCalcemiaPlan() { 
    var activeControlPanel = null;
    var planStr = "";

    planStr = "HypoCalcemia";
    if (PrintSingleLinePlanAtEnd('HypoCalcemiaPlan', planStr, "Monitor and replace as needed")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "HypoCalcemiaPlan");
    if (!activeControlPanel) {
        LogEvent("WriteHypoCalcemiaPlan. activeControlPanel is null");
        return;
    }

    // Get the inputs
    var currentCa = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_Ca_CP');
    var currentiCal = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_iCal_CP');
    var currentCr = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_Cr_CP');
    var currentVitD = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_VitD_CP');
    var currentUrineCa = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_URINE_Ca_CP');
    var currentUrineCr = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_URINE_CR_CP');

    // Adjust Calcium for Albumin    
    // I do not use this for UK, because our lab seems to not be affected by free/bound state
    albumin = -1;
    if ((currentCa > 0) && (albumin > 0) && (albumin < 4)) {
        var adjustedCa = currentCa + (0.8 * (4.0 - albumin));
        // Round it to 2 decimal places. We add 0.00001 to work around a Javascript bug.
        adjustedCa = Math.round((adjustedCa + 0.00001) * 100) / 100;
    }

    var optionNameList = [ "LowCalciumShowCaOption", "LowCalciumShowiCalOption", "LowCalciumShowVitDOption"];
    var valueList = [ "", "", ""];
    var valueNameList = [ "INPUT_SERUM_Ca_CP", "INPUT_SERUM_iCal_CP", "INPUT_SERUM_VitD_CP"];
    WriteListOfSelectedValuesWithDescriptions(activeControlPanel, optionNameList, valueList, valueNameList)



    ///////////////////////////////////////////
    // Fractional Excretion Ca
    planStr = MedNote_GetCPOptionValue("LowCalciumShowFECaOption");
    if ((planStr != null) && (planStr != "")) {
        if ((currentUrineCa > 0) && (currentCa > 0) && (currentUrineCr > 0) && (currentCr > 0)) {
            var FECa = (currentUrineCa / currentCa) / (currentUrineCr / currentCr);
            // Convert to a percentage
            FECa = FECa * 100;
            // Round it to 2 decimal places. We add 0.00001 to work around a Javascript bug.
            FECa = Math.round((FECa + 0.00001) * 100) / 100;
            planStr += FECa + " percent";
        } 
        WriteComment(planStr);
    }
    WriteCommentIfSelected(activeControlPanel, 'LowCalciumExplainFECaOption');

    // Workup
    var optionNameList = [ 'LowCalciumCheckiCalOption', 'LowCalciumCheckVitaminOption', 'LowCalciumCheckPTHOption',
                            'LowCalciumCheckUrineOption']; 
    WriteListOfSelectedActions(activeControlPanel, "Check ", optionNameList)

    WriteActionIfSelected(activeControlPanel, "LowCalciumReplaceCaOption");
    WriteActionIfSelected(activeControlPanel, "LowCalciumGiveVitDOption");
} // WriteHypoCalcemiaPlan






////////////////////////////////////////////////////////////////////////////////
//
// [WriteHypERCalcemiaPlan]
//
// Updated 2022-11-2
// 2023-11-15 - Combined workup labs into a single task
////////////////////////////////////////////////////////////////////////////////
function 
WriteHypERCalcemiaPlan() { 
    var activeControlPanel = null;
    var planStr = "";

    planStr = "HyperCalcemia";
    if (PrintSingleLinePlanAtEnd('HypERCalcemiaPlan', planStr, "IV fluids")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "HypERCalcemiaPlan");
    if (!activeControlPanel) {
        LogEvent("WriteHypERCalcemiaPlan. activeControlPanel is null");
        return;
    }

    // Get the inputs
    var currentCa = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_Ca_CP');
    var currentiCal = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_iCal_CP');
    var currentAlbumin = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_Albumin_CP');
    var currentCr = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_Cr_CP');
    var currentPhos = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_Phos_CP');
    var currentPTH = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_PTH_CP');
    var currentUrineCa = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_URINE_Ca_CP');
    var currentUrineCr = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_URINE_CR_CP');

    var optionNameList = [ "HighCalciumShowCaOption", "HighCalciumShowiCalOption", "HighCalciumShowVitDOption", "HighCalciumShow125VitDOption"];
    var valueList = [ "", "", "", ""];
    var valueNameList = [ "INPUT_SERUM_Ca_CP", "INPUT_SERUM_iCal_CP", "INPUT_SERUM_VitD_CP", "INPUT_SERUM_125VitD_CP"];
    WriteListOfSelectedValuesWithDescriptions(activeControlPanel, optionNameList, valueList, valueNameList)

    ///////////////////////////////////////////
    // Fractional Excretion Ca
    planStr = MedNote_GetCPOptionValue("HighCalciumShowFECaOption");
    if ((planStr != null) && (planStr != "")) {
        if ((currentUrineCa > 0) && (currentCa > 0) && (currentUrineCr > 0) && (currentCr > 0)) {
            var FECa = (currentUrineCa / currentCa) / (currentUrineCr / currentCr);
            // Convert to a percentage
            FECa = FECa * 100;
            // Round it to 2 decimal places. We add 0.00001 to work around a Javascript bug.
            FECa = Math.round((FECa + 0.00001) * 100) / 100;
            planStr += FECa + " percent";
        } 
        WriteComment(planStr);
    }
    WriteCommentIfSelected(activeControlPanel, 'HighCalciumExplainFECaOption');

    var optionNameList = [ 'HighCalciumCheckiCalOption', 'HighCalciumCheckPTHOption', 'HighCalciumCheckVitaminOption',
                            'HighCalciumCheck125VitaminOption',
                            'HighCalciumCheckPTHrPOption']; 
    WriteListOfSelectedActions(activeControlPanel, "Check ", optionNameList)

    WriteActionIfSelected(activeControlPanel, "HighCalciumIVFluidsOption");
    WriteActionIfSelected(activeControlPanel, "HighCalciumPamidronateOption");
    WriteActionIfSelected(activeControlPanel, "HighCalciumDiureticsOption");
} // WriteHypERCalcemiaPlan




////////////////////////////////////////////////////////////////////////////////
//
// [WriteBPHPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteBPHPlan() {
    var activeControlPanel = null;
    var planStr = "";

    planStr = "Benign Prostatic Hyperplasia";
    if (PrintSingleLinePlanAtEnd('BPHPlan', planStr, "Continue home medications:")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "BPHPlan");
    if (!activeControlPanel) {
        LogEvent("WriteBPHPlan. activeControlPanel is null");
        return;
    }

    var optionNameList = [ 'BPH_HOME_TAMSULOSIN_OPTION', 'BPH_HOME_FINASTERIDE_OPTION', 'BPH_HOME_IO_CATH_OPTION' ]; 
    WriteListOfSelectedValues(activeControlPanel, "Home regimen includes: ", false, "", optionNameList, "")

    var optionNameList = [ 'BPH_SYMPTOMS_STRAINING_OPTION', 'BPH_SYMPTOMS_WEAK_STREAM_OPTION', 'BPH_SYMPTOMS_SLOW_STREAM_OPTION', 'BPH_SYMPTOMS_FREQUENCY_OPTION' ]; 
    WriteListOfSelectedValues(activeControlPanel, "The patient reports urinary symptoms, including: ", false, "", optionNameList, "")

    WriteCommentIfSelected(activeControlPanel, "BPH_SHOW_PSA_OPTION");

    WriteActionIfSelected(activeControlPanel, "BPH_TREAT_TAMSULOSIN_OPTION");
    WriteActionIfSelected(activeControlPanel, "BPH_TREAT_FINASTERIDE_OPTION");
    WriteActionIfSelected(activeControlPanel, "BPH_TREAT_IOCATH_OPTION");
    WriteActionIfSelected(activeControlPanel, "BPH_TREAT_FOLEY_OPTION");
    WriteActionIfSelected(activeControlPanel, "BPH_CHECK_PSA_OPTION");
} // WriteBPHPlan






////////////////////////////////////////////////////////////////////////////////
//
// [WriteVitaminDPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteVitaminDPlan() {
    var activeControlPanel = null;
    var planStr = "";

    planStr = "Vitamin D Deficiency";
    if (PrintSingleLinePlanAtEnd('VitDPlan', planStr, "Continue home medications:")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "VitDPlan");
    if (!activeControlPanel) {
        LogEvent("WriteVitaminDPlan. activeControlPanel is null");
        return;
    }

    var optionNameList = [ 'LOWVITD_HOME_MEDS_OPTION' ]; 
    WriteListOfSelectedValues(activeControlPanel, "Home regimen includes: ", false, "", optionNameList, "")

    WriteCommentIfSelected(activeControlPanel, "LOWVITD_VITDLEVEL_OPTION");
    WriteCommentIfSelected(activeControlPanel, "LOWVITD_SHOW_TSCORE_OPTION");

    WriteActionIfSelected(activeControlPanel, "LOWVITD_TREAT_OPTION");

    //if ((!fIsMale) && (patientAge >= 65) && (patientAge <= 75)) {
      //  WriteAction("Bone density screening (DEXA Q2yr): Last DEXA ");
} // WriteVitaminDPlan







////////////////////////////////////////////////////////////////////////////////
//
// [WriteOncologyPlan]
//
// Updated 2020-6-24
////////////////////////////////////////////////////////////////////////////////
function 
WriteOncologyPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Malignancy";
    modifierStr = MedNote_GetCPOptionValue("ONCOLOGY_CANCER_TYPE_MODIFIER");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr;
    }
    modifierStr = MedNote_GetCPOptionValue("ONCOLOGY_METASTATIC_MODIFIER");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr + planStr;
    }
    modifierStr = MedNote_GetCPOptionValue("ONCOLOGY_STAGE_MODIFIER");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr += modifierStr;
    }
    modifierStr = MedNote_GetCPOptionValue("ONCOLOGY_NEWLY_DIAGNOSED_MODIFIER");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr += modifierStr;
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "OncologyPlan");
    if (!activeControlPanel) {
        LogEvent("WriteOncologyPlan. activeControlPanel is null");
        return;
    }

    WriteCommentIfSelected(activeControlPanel, "ONCOLOGY_STATUS_WHEN_DIAG_OPTION");
    var optionNameList = [ 'ONCOLOGY_STATUS_SP_SURGERY_OPTION', 'ONCOLOGY_STATUS_SP_CHEMO_OPTION', 'ONCOLOGY_STATUS_SP_XRT_OPTION' ]; 
    WriteListOfSelectedValues(activeControlPanel, "The patient is ", false, "", optionNameList, "")

    WriteCommentIfSelected(activeControlPanel, "ONCOLOGY_STATUS_ECOG_OPTION");
    WriteCommentIfSelected(activeControlPanel, "ONCOLOGY_STATUS_BASELINE_URATE_OPTION");
    WriteCommentIfSelected(activeControlPanel, "ONCOLOGY_STATUS_BASELINE_LDH_OPTION");

    WriteActionIfSelected(activeControlPanel, "ONCOLOGY_STAGING_MRI_BRAIN_OPTION");
    WriteActionIfSelected(activeControlPanel, "ONCOLOGY_STAGING_CT_OPTION");

    WriteActionIfSelected(activeControlPanel, "ONCOLOGY_TLS_GET_LDH_OPTION");
    WriteActionIfSelected(activeControlPanel, "ONCOLOGY_TLS_GET_URATE_OPTION");
    WriteActionIfSelected(activeControlPanel, "ONCOLOGY_TLS_Allopurinol_OPTION");
    WriteActionIfSelected(activeControlPanel, "ONCOLOGY_TLS_Rasburicase_OPTION");
    WriteActionIfSelected(activeControlPanel, "ONCOLOGY_TLS_IV_Fluids_OPTION");
    WriteActionIfSelected(activeControlPanel, "ONCOLOGY_TLS_DONT_ALKALINIZE_OPTION");

    WriteActionIfSelected(activeControlPanel, "ONCOLOGY_HYPERCALCEMIA_IVF_OPTION");
    WriteActionIfSelected(activeControlPanel, "ONCOLOGY_HYPERCALCEMIA_Bisphosphonate_OPTION");

    var actionNameList = [ "ONCOLOGY_ONDANSETRON_PRN_OPTION", "ONCOLOGY_ONDANSETRON_SCHEDULED_OPTION", "ONCOLOGY_Prochlorperazine_OPTION", "ONCOLOGY_Phenergan_OPTION"];
    WriteListOfSubActions("Antiemetics", actionNameList);

    var actionNameList = [ "ONCOLOGY_MORPHINE_ER_OPTION", "ONCOLOGY_OXYCODONE_LR_OPTION", "ONCOLOGY_FENTANYL_OPTION", "ONCOLOGY_Prednisone_OPTION", "ONCOLOGY_MORPHINE_IR_OPTION",
                        "ONCOLOGY_Oxycodone_OPTION", "ONCOLOGY_Dilaudid_PO_OPTION", "ONCOLOGY_Dilaudid_IV_OPTION", "ONCOLOGY_PCA_OPTION"];
    WriteListOfSubActions("Pain Control", actionNameList);

    var actionNameList = [ "ONCOLOGY_DOCSENNA_OPTION", "ONCOLOGY_MIRALAX_OPTION", "ONCOLOGY_MgCitrate_OPTION", "ONCOLOGY_Lactulose_OPTION"];
    WriteListOfSubActions("Bowel Regimen", actionNameList);

    WriteActionIfSelected(activeControlPanel, "ONCOLOGY_Acyclovir_OPTION");
    WriteActionIfSelected(activeControlPanel, "ONCOLOGY_Bactrim_OPTION");
} // WriteOncologyPlan






////////////////////////////////////////////////////////////////////////////////
//
// [WritePalliativePlan]
//
// Updated 2020-6-24
////////////////////////////////////////////////////////////////////////////////
function 
WritePalliativePlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Palliative";
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "PalliativePlan");
    if (!activeControlPanel) {
        LogEvent("WritePalliativePlan. activeControlPanel is null");
        return;
    }
    WriteCommentIfSelected(activeControlPanel, "PALLIATIVE_STATUS_COMFORT_OPTION");

    WriteCommentIfSelected(activeControlPanel, "PALLIATIVE_STATUS_HEALTH_CARE_REP_OPTION");
    WriteCommentIfSelected(activeControlPanel, "PALLIATIVE_STATUS_LIVING_WILL_OPTION");
    WriteCommentIfSelected(activeControlPanel, "PALLIATIVE_STATUS_CODE_DOCUMENTED_OPTION");
    WriteCommentIfSelected(activeControlPanel, "PALLIATIVE_STATUS_DNR_OPTION");
    WriteCommentIfSelected(activeControlPanel, "PALLIATIVE_STATUS_DNI_OPTION");
    WriteCommentIfSelected(activeControlPanel, "PALLIATIVE_STATUS_FEEDING_OPTION");

    WriteActionIfSelected(activeControlPanel, "PALLIATIVE_Glycopyrrolate_OPTION");
    WriteActionIfSelected(activeControlPanel, "PALLIATIVE_Lorazepam_OPTION");

    var actionNameList = [ "PALLIATIVE_ONDANSETRON_PRN_OPTION", "PALLIATIVE_ONDANSETRON_SCHEDULED_OPTION", "PALLIATIVE_Prochlorperazine_OPTION", "PALLIATIVE_Phenergan_OPTION"];
    WriteListOfSubActions("Antiemetics", actionNameList);

    var actionNameList = [ "PALLIATIVE_MORPHINE_ER_OPTION", "PALLIATIVE_OXYCODONE_LR_OPTION", "PALLIATIVE_FENTANYL_OPTION", "PALLIATIVE_Prednisone_OPTION", 
                        "PALLIATIVE_MORPHINE_IR_OPTION", "PALLIATIVE_Oxycodone_OPTION", "PALLIATIVE_Dilaudid_PO_OPTION", "PALLIATIVE_Dilaudid_IV_OPTION", "PALLIATIVE_PCA_OPTION"];
    WriteListOfSubActions("Pain Control", actionNameList);

    var actionNameList = [ "PALLIATIVE_DOCSENNA_OPTION", "PALLIATIVE_MIRALAX_OPTION", "PALLIATIVE_MgCitrate_OPTION", "PALLIATIVE_Lactulose_OPTION"];
    WriteListOfSubActions("Bowel Regimen", actionNameList);
} // WritePalliativePlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteScoreFromSelectedValues]
//
// BUG!!!! This is different than MedNote_WriteScoreFromSelectedValues.
// Need to merge the two.
//
// var optionNameList = [ 'p0', 'p1', 'p2' ]; 
// WriteScoreFromSelectedValues(activeControlPanel, "Preface", false, "", optionNameList, "Suffix")
////////////////////////////////////////////////////////////////////////////////
function 
WriteScoreFromSelectedValues(activeControlPanel, optionNameList, pointList, percentRiskList, minCountToPrint, prefaceStr, unitStr, riskStr) {
    //LogEvent("WriteScoreFromSelectedValues");
    var planStr;
    var currentOptionName;
    var currentOptionValue;
    var count = 0;
    var score = 0;
    var percentRisk;
    var wordListStr = "";

    for (index = 0; index < optionNameList.length; index++) {
        //LogEvent("WriteScoreFromSelectedValues. index: " + index);
        currentOptionName = optionNameList[index];
        currentOptionValue = MedNote_GetCPOptionValue(currentOptionName);

        //LogEvent("WriteScoreFromSelectedValues. Check option: " + currentOptionName);
        if (currentOptionValue) {
            //LogEvent("WriteScoreFromSelectedValues. Found selected option: " + currentOptionName);
            wordListStr = wordListStr + currentOptionValue + ", ";
            count += 1;
            if (pointList) {
                score += pointList[index];
            } else {
                score += 1;
            }
        }
    } // for (index = 0; index < optionNameList.length; index++)

    if (count < minCountToPrint) {
        return;
    }

    //LogEvent("WriteScoreFromSelectedValues. count = " + count);
    //LogEvent("WriteScoreFromSelectedValues. score = " + score);

    if (count > 0) {
        // Remove the last ", "
        wordListStr = wordListStr.substring(0, wordListStr.length - 2);
    }

    if (score >= (percentRiskList.length - 1)) {
        score = percentRiskList.length - 1;
    }
    percentRisk = percentRiskList[score];


    planStr = prefaceStr + " " + count + " " + unitStr;
    if (count > 0) {
        planStr += " (" + wordListStr + ") ";
    }
    if (riskStr) {
        planStr += " which suggests a " + percentRisk + " percent risk of "  + riskStr;
    }
    WriteComment(planStr);
} // WriteScoreFromSelectedValues






////////////////////////////////////////////////////////////////////////////////
//
// [ComputeScoreFromSelectedValues]
//
// var optionNameList = [ 'p0', 'p1', 'p2' ]; 
// WriteScoreFromSelectedValues(activeControlPanel, "Preface", false, "", optionNameList, "Suffix")
////////////////////////////////////////////////////////////////////////////////
function 
ComputeScoreFromSelectedValues(activeControlPanel, optionNameList) {
    //LogEvent("ComputeScoreFromSelectedValues");
    var currentOptionName;
    var currentOptionValue;
    var score = 0;

    for (index = 0; index < optionNameList.length; index++) {
        //LogEvent("ComputeScoreFromSelectedValues. index: " + index);
        currentOptionName = optionNameList[index];
        currentOptionValue = MedNote_GetCPOptionToggleState(currentOptionName);
        if (currentOptionValue >= 0) {
            score += currentOptionValue;
        }
    } // for (index = 0; index < optionNameList.length; index++)

    return(score);
} // ComputeScoreFromSelectedValues






////////////////////////////////////////////////////////////////////////////////
//
// [WritePreOpPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WritePreOpPlan() {
    //LogEvent("WritePreOpPlan");
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Preoperative Evaluation";
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "PreopPlan");
    if (!activeControlPanel) {
        LogEvent("WritePreOpPlan. activeControlPanel is null");
        return;
    }
    // bibEntry name="ACCPreop2014"
    // bibEntry name="RCRI1999"

    WriteCommentIfSelected(activeControlPanel, "PREOP_SURGERY_URGENCY_OPTION");
    WriteCommentIfSelected(activeControlPanel, "PREOP_SURGERY_RISK_OPTION");
    WriteCommentIfSelected(activeControlPanel, "PREOP_PATIENT_FUNCTIONAL_STATUS_OPTION");
    WriteCommentIfSelected(activeControlPanel, "PREOP_MI_IN_60DAYS_OPTION");

    // bibEntry name="RCRI1999" 
    //WriteComment("The patient has xxx cardiac risk factors (CHF, CAD, CVA, Insulin-dependant DM, CKD with Cr over 2.0, High risk surgery)");
    //WriteComment("    Where patients with 0 risk factors have estimated 0.4 percent risk of major cardiac events based on RCRI");
    //WriteComment("    Where patients with 1 risk factors have estimated 1-1.3 percent risk of major cardiac events based on RCRI");
    //WriteComment("    Where patients with 2 risk factors have estimated 4-7 percent risk of major cardiac events based on RCRI");
    //WriteComment("    Where patients with 3 or more risk factors have estimated 9-11 percent risk of major cardiac events based on RCRI");
    var optionNameList = [ 'PREOP_CARDIAC_RISK_FACTORS_CHF_OPTION', 'PREOP_CARDIAC_RISK_FACTORS_CAD_OPTION', 'PREOP_CARDIAC_RISK_FACTORS_CVA_OPTION', 'PREOP_CARDIAC_RISK_FACTORS_IDDM_OPTION', 'PREOP_CARDIAC_RISK_FACTORS_CrOver2_OPTION', 'PREOP_CARDIAC_RISK_FACTORS_High_Risk_OR_OPTION' ]; 
    var scorePointList = [ 1, 1, 1, 1, 1, 1];
    var percentRiskList = [ "0.4", "1 - 1.3", "4 - 7", "9 - 11"];
    WriteScoreFromSelectedValues(
                activeControlPanel, 
                optionNameList, 
                scorePointList, 
                percentRiskList, 
                0,
                "The patient has ", 
                "cardiac risk factors", 
                " of major cardiac events based on RCRI");   

    // ThakarPreOpESRDRisk
    //WriteComment("The patient has xxx risk factors for perioperative AKI requiring Dialysis (Preop Cr 1.2-2.1(2pts), Preop Cr over 2.1(5pts), CHF, LVEF below 35, IABP(2pts), COPD, Insulin-dependant DM, Past Cardiac Surgery(2pts), Past CABG(2pts), Past Valvular surgery, Emergency Surgery(2pts), Female)");
    //WriteComment("    Where 0 points suggests a 0.1 percent risk of AKI requiring dialysis");
    //WriteComment("    Where 1 points suggests a 0.3 percent risk of AKI requiring dialysis");
    //WriteComment("    Where 2 points suggests a 0.5 percent risk of AKI requiring dialysis");
    //WriteComment("    Where 3 points suggests a 1 percent risk of AKI requiring dialysis");
    //WriteComment("    Where 4 points suggests a 2.3 percent risk of AKI requiring dialysis");
    //WriteComment("    Where 5 points suggests a 2.6 percent risk of AKI requiring dialysis");
    //WriteComment("    Where 6 points suggests a 8 percent risk of AKI requiring dialysis");
    //WriteComment("    Where 7 points suggests a 9.8 percent risk of AKI requiring dialysis");
    //WriteComment("    Where 8 points suggests a 14 percent risk of AKI requiring dialysis");
    //WriteComment("    Where 9 points suggests a 17 percent risk of AKI requiring dialysis");
    //WriteComment("    Where 10 points suggests a 19.5 percent risk of AKI requiring dialysis");
    //WriteComment("    Where 11 points suggests a 38.9 percent risk of AKI requiring dialysis");
    //WriteComment("    Where 12 points suggests a 25 percent risk of AKI requiring dialysis");
    var optionNameList = [ 'PREOP_AKI_RISKS_Cr_12_21_OPTION', 'PREOP_AKI_RISKS_Cr_over_21_OPTION', 'PREOP_AKI_RISKS_CHF_OPTION', 'PREOP_AKI_RISKS_EF_below_35_OPTION', 'PREOP_AKI_RISKS_IABP_OPTION', 'PREOP_AKI_RISKS_COPD_OPTION', 'PREOP_AKI_RISKS_IDDM_OPTION', 'PREOP_AKI_RISKS_PAST_CARDIAC_SURGERY_OPTION', 'PREOP_AKI_RISKS_PAST_CABG_OPTION', 'PREOP_AKI_RISKS_PAST_VALVULAR_SURGERY_OPTION', 'PREOP_AKI_RISKS_Emergency_Surgery_OPTION', 'PREOP_AKI_RISKS_Female_OPTION' ]; 
    var scorePointList = [ 2, 5, 1, 1, 2, 1, 1, 2, 2, 1, 2, 1];
    var percentRiskList = [ "0.1", "0.3", "0.5", "1", "2.3", "2.6", "8", "9.8", "14", "17", "19.5", "38.9", "25"];
    WriteScoreFromSelectedValues(
                activeControlPanel, 
                optionNameList, 
                scorePointList, 
                percentRiskList, 
                0,
                "The patient has ", 
                "risk factors for severe AKI", 
                " of perioperative AKI requiring Dialysis");   


    // NSQIP AKI Risk
    //WriteComment("The patient has xxx risk factors for any perioperative AKI with a rise of Cr over 2 (Age over 55, Male, CHF, Ascites, HTN, Emergency Surgery, Intraperitoneal surgery, Preop Cr 1.2 or higher, Insulin-dependant DM)");
    //WriteComment("    Where 0-2 points suggests a 0.2 percent risk of any AKI");
    //WriteComment("    Where 3 points suggests a 0.8 percent risk of any AKI");
    //WriteComment("    Where 4 points suggests a 1.8 percent risk of any AKI");
    //WriteComment("    Where 5 points suggests a 3.3 percent risk of any AKI");
    //WriteComment("    Where 6 or more points suggests a 8.9 percent risk of any AKI");
    var optionNameList = [ 'PREOP_AKI2_RISKS_Over_55yo_OPTION', 'PREOP_AKI2_RISKS_Male_OPTION', 'PREOP_AKI2_RISKS_CHF_OPTION', 'PREOP_AKI2_RISKS_Ascites_OPTION', 'PREOP_AKI2_RISKS_HTN_OPTION', 'PREOP_AKI2_RISKS_IDDM_OPTION', 'PREOP_AKI2_RISKS_Emergent_Surgery_OPTION', 'PREOP_AKI2_RISKS_Intraperitoneal_OPTION', 'PREOP_AKI2_RISKS_Preop_Cr_11_OPTION' ]; 
    var scorePointList = [ 1, 1, 1, 1, 1, 1, 1, 1, 1];
    var percentRiskList = [ "0.2", "0.2", "0.2", "0.8", "1.8", "3.3", "8.9" ];
    WriteScoreFromSelectedValues(
                activeControlPanel, 
                optionNameList, 
                scorePointList, 
                percentRiskList, 
                0,
                "The patient has ", 
                "risk factors for any AKI", 
                " for any perioperative AKI with a rise of Cr over 2");   


    //WriteCommentIfSelected(activeControlPanel, "PREOP_Show_NSQIP_Risk_OPTION");
    WriteCommentIfSelected(activeControlPanel, "PREOP_OTHER_CARDIAC_RISKS_Symptomatic_CHF_OPTION");
    WriteCommentIfSelected(activeControlPanel, "PREOP_OTHER_CARDIAC_RISKS_Asymptomatic_LV_Dysfunction_OPTION");

    WriteActionIfSelected(activeControlPanel, "PREOP_CHECK_EKG_OPTION");
    WriteActionIfSelected(activeControlPanel, "PREOP_CHECK_Echo_OPTION");
    WriteActionIfSelected(activeControlPanel, "PREOP_CHECK_BMP_OPTION");
    WriteActionIfSelected(activeControlPanel, "PREOP_CHECK_NECK_XR_OPTION");

    WriteActionIfSelected(activeControlPanel, "PREOP_BP_TARGET_OPTION");
    WriteActionIfSelected(activeControlPanel, "PREOP_START_BETA_BLOCKER_OPTION");

    WriteActionIfSelected(activeControlPanel, "PREOP_NO_CATH_OPTION");
    WriteActionIfSelected(activeControlPanel, "PREOP_Stress_Test_OPTION");
    WriteActionIfSelected(activeControlPanel, "PREOP_MITRAL_REPAIR_OPTION");

    WriteActionIfSelected(activeControlPanel, "PREOP_ANTICOAG_HOLD_ANTICOAG_OPTION");
    WriteActionIfSelected(activeControlPanel, "PREOP_ANTICOAG_HOLD_ASPIRIN_OPTION");
    WriteActionIfSelected(activeControlPanel, "PREOP_ANTICOAG_HOLD_PLAVIX_OPTION");
    WriteActionIfSelected(activeControlPanel, "PREOP_ANTICOAG_Check_PTT_OPTION");
    WriteActionIfSelected(activeControlPanel, "PREOP_ANTICOAG_HOLD_COUMADIN_OPTION");
    WriteActionIfSelected(activeControlPanel, "PREOP_ANTICOAG_BRIDGE_HEPARIN_OPTION");

    WriteActionIfSelected(activeControlPanel, "PREOP_DAY_OF_SURGERY_BETA_BLOCKER_OPTION");
    WriteActionIfSelected(activeControlPanel, "PREOP_DAY_OF_SURGERY_HOLD_SSRI_OPTION");
    WriteActionIfSelected(activeControlPanel, "PREOP_DAY_OF_SURGERY_HALF_INSULIN_OPTION");
    WriteActionIfSelected(activeControlPanel, "PREOP_DAY_OF_SURGERY_HOLD_ACE_OPTION");
    WriteActionIfSelected(activeControlPanel, "PREOP_DAY_OF_SURGERY_HOLD_DIURETICS_OPTION");
    WriteActionIfSelected(activeControlPanel, "PREOP_DAY_OF_SURGERY_CONTINUE_NARCOTICS_OPTION");
    WriteActionIfSelected(activeControlPanel, "PREOP_DAY_OF_SURGERY_CONTINUE_STATINS_OPTION");
    WriteActionIfSelected(activeControlPanel, "PREOP_DAY_OF_SURGERY_HOLD_NSAIDS_OPTION");
    WriteActionIfSelected(activeControlPanel, "PREOP_DAY_OF_SURGERY_HOLD_PO_DIABETES_MEDS_OPTION");

    WriteActionIfSelected(activeControlPanel, "PREOP_SCREEN_MRSA_OPTION");
    WriteActionIfSelected(activeControlPanel, "PREOP_DECOLONIZE_MRSA_OPTION");
} // WritePreOpPlan






////////////////////////////////////////////////////////////////////////////////
//
// [WriteHypothyroidPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteHypothyroidPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Hypothyroid";
    if (PrintSingleLinePlanAtEnd('HypothyroidPlan', planStr, "Continue home medications:")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "HypothyroidPlan");
    if (!activeControlPanel) {
        LogEvent("WriteHypothyroidPlan. activeControlPanel is null");
        return;
    }

    WriteActionIfSelected(activeControlPanel, "HYPOTHYROID_TREAT_LEVOTHYROXINE_OPTION");
} // WriteHypothyroidPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteHepatitisCPlan]
//
// 2023-11-15 - Combined workup labs into a single task
////////////////////////////////////////////////////////////////////////////////
function 
WriteHepatitisCPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Chronic Hepatitis C";
    var modifierStr = MedNote_GetCPOptionValue("HEPC_ANTIBODY_POSITIVE_MODIFIER");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr;
    }

    if (PrintSingleLinePlanAtEnd('HepCPlan', planStr, "Refer to GI clinic on discharge")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "HepCPlan");
    if (!activeControlPanel) {
        LogEvent("WriteHepatitisCPlan. activeControlPanel is null");
        return;
    }

    WriteCommentIfSelected(activeControlPanel, "HEPC_STATUS_VL_OPTION");
    WriteCommentIfSelected(activeControlPanel, "HEPC_STATUS_GENOTYPE_OPTION");
    WriteCommentIfSelected(activeControlPanel, "HEPC_STATUS_HAV_OPTION");
    WriteCommentIfSelected(activeControlPanel, "HEPC_STATUS_HBV_OPTION");
    WriteCommentIfSelected(activeControlPanel, "HEPC_STATUS_HIV_OPTION");

    var optionNameList = [ 'HEPC_CHECK_VIRAL_LOAD_OPTION', 'HEPC_CHECK_GENOTYPE_OPTION', 'HEPC_CHECK_HIV_OPTION',
                            'HEPC_CHECK_HAV_OPTION', 'HEPC_CHECK_HBV_OPTION']; 
    WriteListOfSelectedActions(activeControlPanel, "Check ", optionNameList)

    WriteActionIfSelected(activeControlPanel, "HEPC_TREAT_HAV_VACCINE_OPTION");
    WriteActionIfSelected(activeControlPanel, "HEPC_TREAT_HBV_VACCINE_OPTION");
    WriteActionIfSelected(activeControlPanel, "HEPC_TREAT_GI_CLINIC_OPTION");
} // WriteHepatitisCPlan







////////////////////////////////////////////////////////////////////////////////
//
// [WriteEncephalopathyPlan]
//
// Updated: 2022-4-4
// Updated: 2023-9-19
////////////////////////////////////////////////////////////////////////////////
function 
WriteEncephalopathyPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Encephalopathy";
    var modifierStr = MedNote_GetCPOptionValue("AMS_ACUTE_MODIFIER");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr + planStr;
    }

    activeControlPanel = MedNote_StartNewPlanSection(planStr, "EncephalopathyPlan");
    if (!activeControlPanel) {
        LogEvent("WriteEncephalopathyPlan. activeControlPanel is null");
        return;
    }

    var optionNameList = [ "AMS_CHECK_HEAD_CT_OPTION", "AMS_CHECK_Prolactin_OPTION", "AMS_CHECK_EEG_OPTION"];
    WriteListOfSelectedActions(activeControlPanel, "Check for CNS causes: ", optionNameList)

    var optionNameList = [ "AMS_INTOXICATION_CHECK_EtOH_OPTION", "AMS_INTOXICATION_CHECK_UDS_OPTION", 
                    "AMS_INTOXICATION_CHECK_LEAD", "AMS_INTOXICATION_CHECK_HEAVY_METALS",
                    "AMS_INTOXICATION_CHECK_Salicylate_OPTION", "AMS_INTOXICATION_CHECK_acetaminophen_OPTION",
                    "AMS_INTOXICATION_CHECK_Serum_OSM_OPTION"];
    WriteListOfSelectedActions(activeControlPanel, "Check for intoxications: ", optionNameList)

    var optionNameList = [ "AMS_CHECK_VMG_OPTION", "AMS_CHECK_CO_OPTION"];
    WriteListOfSelectedActions(activeControlPanel, "Check for pulmonary causes: ", optionNameList)

    var optionNameList = [ "AMS_CHECK_Blood_CX_OPTION", "AMS_CHECK_Urine_CX_OPTION", "AMS_CHECK_CXR_OPTION",
                            "AMS_CHECK_RPR_OPTION"];
    WriteListOfSelectedActions(activeControlPanel, "Check for infectious causes: ", optionNameList)

    var optionNameList = ["AMS_CHECK_Glucose_OPTION", "AMS_CHECK_A1c_OPTION", "AMS_METABOLIC_CHECK_B12",
                        "AMS_METABOLIC_CHECK_Thiamine", "AMS_CHECK_CPK_OPTION"];
    WriteListOfSelectedActions(activeControlPanel, "Check for metabolic causes: ", optionNameList)

    var optionNameList = [ "AMS_CHECK_TSH_OPTION"];
    WriteListOfSelectedActions(activeControlPanel, "Check for Endocrine causes: ", optionNameList)

    var optionNameList = [ "AMS_CHECK_Gabapentin_OPTION", "AMS_CHECK_Lithium_OPTION", "AMS_CHECK_Digoxin_OPTION",
                    "AMS_CHECK_Amitriptylene_OPTION"];
    WriteListOfSelectedActions(activeControlPanel, "Check for Medication causes: ", optionNameList)

    var optionNameList = [ "AMS_HOLD_OPIOIDS_OPTION", "AMS_HOLD_BENZOS_OPTION", "AMS_HOLD_MUSCLE_RELAXANTS_OPTION", "AMS_HOLD_ANTIHISTAMINES_OPTION", "AMS_HOLD_PROMETHAZINE_OPTION", "AMS_HOLD_GABAPENTIN_OPTION"];
    WriteListOfSelectedActions(activeControlPanel, "Hold home medications: ", optionNameList)
    
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_SWALLOW_STUDY_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_Treat_Thiamine_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_Treat_Memantine_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_Treat_Donepezil_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_Treat_Lorazepam_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_Treat_Haloperidol_OPTION");

    var optionNameList = [ "AMS_SLEEP_MED_OPTION"];
    WriteListOfSelectedActions(activeControlPanel, "Manage sleep: ", optionNameList)
} // WriteEncephalopathyPlan






////////////////////////////////////////////////////////////////////////////////
//
// [WriteMBDPlan]
//
// 2021-2-15 - Updated
// 2022-10-30 - Updated
// 2022-11-2 - Updated
// 2024-1-8 - Add workup
////////////////////////////////////////////////////////////////////////////////
function 
WriteMBDPlan() {
    var activeControlPanel = null;
    var planStr = "";

    planStr = "Metabolic Bone Disease";
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "MBDPlan");
    if (!activeControlPanel) {
        LogEvent("WriteMBDPlan. activeControlPanel is null");
        return;
    }
    MedNote_AddRelatedProblemIfSelected(activeControlPanel, "MBDHyperphosModifier");

    // Get the inputs
    var currentCa = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_Ca_CP');
    var currentPhos = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_Phos_CP');
    var currentPTH = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_PTH_CP');
    var currentiCal = GetFloatInputForControlPanel(activeControlPanel, 'INPUT_SERUM_iCal_CP');

    var optionNameList = [ "MBD_OPTION_SHOW_Ca", "MBD_OPTION_SHOW_Phos", "MBD_OPTION_SHOW_PTH", "MBD_OPTION_SHOW_ICal"];
    var valueList = [ "", "", "", ""];
    var valueNameList = [ "INPUT_SERUM_Ca_CP", "INPUT_SERUM_Phos_CP", "INPUT_SERUM_PTH_CP", "INPUT_SERUM_iCal_CP"];
    WriteListOfSelectedValuesWithDescriptions(activeControlPanel, optionNameList, valueList, valueNameList)

    var optionNameList = [ "MBD_OPTION_CHECK_PTH", "MBD_OPTION_CHECK_VITD"];
    WriteListOfSelectedActions(activeControlPanel, "Check: ", optionNameList)

    WriteActionIfSelected(activeControlPanel, "MBD_OPTION_TEAT_BINDER");
    WriteActionIfSelected(activeControlPanel, "MBD_OPTION_TEAT_CALCITRIOL");
} // WriteMBDPlan






////////////////////////////////////////////////////////////////////////////////
//
// [WriteDysphagiaPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteDysphagiaPlan() {
    var activeControlPanel = null;
    var planStr = "";

    planStr = "Dysphagia";
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "DysphagiaPlan");
    if (!activeControlPanel) {
        LogEvent("WriteDysphagiaPlan. activeControlPanel is null");
        return;
    }


    WriteCommentIfSelected(activeControlPanel, "DYSPHAGIA_Speech_Eval_Result_OPTION");
    WriteActionIfSelected(activeControlPanel, "DYSPHAGIA_Mod_Barium_OPTION");
    WriteActionIfSelected(activeControlPanel, "DYSPHAGIA_Place_DHT_OPTION");
    WriteActionIfSelected(activeControlPanel, "DYSPHAGIA_Tube_Feeds_OPTION");
} // WriteDysphagiaPlan






////////////////////////////////////////////////////////////////////////////////
//
// [WriteIVContrastPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteIVContrastPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "IV Contrast";
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "IVContrastPlan");
    if (!activeControlPanel) {
        LogEvent("WriteIVContrastPlan. activeControlPanel is null");
        return;
    }

    WriteActionIfSelected(activeControlPanel, "CONTRAST_PPX_HOLD_ACE_OPTION");
    WriteActionIfSelected(activeControlPanel, "CONTRAST_PPX__Hold_Diuretics_OPTION");
    WriteActionIfSelected(activeControlPanel, "CONTRAST_PPX__PRE_FLUIDS_OPTION");
    WriteActionIfSelected(activeControlPanel, "CONTRAST_PPX_POST_FLUIDS_OPTION");
    WriteActionIfSelected(activeControlPanel, "CONTRAST_PPX_BICARB_OPTION");
    WriteActionIfSelected(activeControlPanel, "CONTRAST_PPX_NAC_OPTION");
} // WriteIVContrastPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteHepatitisPlan]
//
// 2020-4-19 - Updated
// 2021-4-24 - Get all new user input values.
// 2022-10-30 - Updated
// 2023-11-14 - Combined workup labs into a single task
////////////////////////////////////////////////////////////////////////////////
function 
WriteHepatitisPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Hepatitis";
    modifierStr = MedNote_GetCPOptionValue("HepatitisViralOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr + " " + planStr;
    }
    modifierStr = MedNote_GetCPOptionValue("HepatitisAlcoholOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr + " " + planStr;
    }
    modifierStr = MedNote_GetCPOptionValue("HepatitisAcuteChronicOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr + " " + planStr;
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "HepatitisPlan");
    if (!activeControlPanel) {
        LogEvent("WriteHepatitisPlan. activeControlPanel is null");
        return;
    }


    ///////////////////
    // Read Inputs
    var currentPT = GetFloatInputForControlPanel(activeControlPanel, 'HEPATITIS_PT_INPUT');
    var tBiliAtDay0 = GetFloatInputForControlPanel(activeControlPanel, 'HEPATITIS_TBili_INPUT');
    var tBiliAtDay7 = GetFloatInputForControlPanel(activeControlPanel, 'HEPATITIS_TBiliDay7_INPUT');
    var currentCr = GetFloatInputForControlPanel(activeControlPanel, 'HEPATITIS_CR_INPUT');
    var currentAge = GetFloatInputForControlPanel(activeControlPanel, 'HEPATITIS_AGE_INPUT');
    var currentAlbumin = GetFloatInputForControlPanel(activeControlPanel, 'HEPATITIS_Albumin_INPUT');


    ///////////////////
    // Status
    WriteCommentIfSelected(activeControlPanel, "HEPATITIS_ALTAST_OPTION");

    // Maddrey Discriminant Function
    //
    // Maddrey WC, Boitnott JK, Bedine MS, Weber FL, Mezey E, White RI (1978). 
    // "Corticosteroid therapy of alcoholic hepatitis"
    // Gastroenterology 75 (2): 193–9. PMID 352788
    //
    // Soultati AS, et. al. 
    // Predicting utility of a model for end stage liver disease in alcoholic liver disease
    // World J Gastroenterol 2006 July 07;12(25):4020-4025
    planStr = MedNote_GetCPOptionValue("HEPATITIS_Maddrey_OPTION");
    if ((planStr != null) && (planStr != "")) {
        if ((tBiliAtDay0 > 0) && (currentPT > 0)) {
            //LogEvent("tBiliAtDay0 = " + tBiliAtDay0 + ", currentPT = " + currentPT);
            // The reference range for prothrombin time is 9.5-13.5 seconds.
            var ReferencePT = 12.0;
            var discriminantFunction = (4.6 * (currentPT - ReferencePT)) + tBiliAtDay0;
            discriminantFunction = Math.round((discriminantFunction + 0.00001) * 10) / 10;
            //LogEvent("discriminantFunction = " + discriminantFunction);
            planStr += discriminantFunction;
         }
        WriteComment(planStr);
    }

    // Lille
    planStr = MedNote_GetCPOptionValue("HEPATITIS_Lille_OPTION");
    if ((planStr != null) && (planStr != "")) {
        // Compute the Lille Score
        // Louvet A, et al 
        // "The Lille model: a new tool for therapeutic strategy in patients with severe alcoholic 
        //   hepatitis treated with steroids"
        // Hepatology. 2007; 45(6):1348-54.
        if ((tBiliAtDay0 > 0) && (tBiliAtDay7 > 0) && (currentCr > 0) && (currentAge > 0) 
                 && (currentAlbumin > 0) && (currentPT > 0)) {
            // Convert g/dL to g/L. This is not explicitly explained in a lot of the online calculators
            // but they all do it behind the scenes.
            currentAlbumin = currentAlbumin * 10.0

            // Convert mmol/L to mg/dL
            if (true) {
                tBiliAtDay0 = tBiliAtDay0 * 17.1;
                tBiliAtDay7 = tBiliAtDay7 * 17.1;
            }
            var changeInBili = tBiliAtDay0 - tBiliAtDay7;

            // Renal insufficiency = 1 (if Cr >1.3 mg/dL (115 µmol/L)) or 0 (if ≤1.3 mg/dL (115 µmol/L))
            var renalInsufficiency = 0.0;
            if (currentCr > 1.3) {
                renalInsufficiency = 1.0;
            }

            // RScore
            var rScore = 3.19 + (-0.101 * currentAge) + (0.147 * currentAlbumin) + (0.0165 * changeInBili) + (-0.206 * renalInsufficiency) + (-0.0065 * tBiliAtDay0) + (-0.0096 * currentPT);

            // Lille Model Score = (exp(-R))/(1 + exp(-R))
            var expNegR = Math.exp(-1.0 * rScore);
            var lilleScore = expNegR / (1.0 + expNegR);
            //LogEvent("Lille. expNegR = " + expNegR + ", lilleScore = " + lilleScore);
            lilleScore = Math.round((lilleScore + 0.00001) * 1000) / 1000;
            //LogEvent("Lille. Rounded lilleScore = " + lilleScore);

            planStr += lilleScore;
            //LogEvent("Lille. planStr = " + planStr);
            // The Lille Model predicts mortality rates within 6 months.
            //    Scores >0.45 predict a 6-month survival of 25%.
            //    Scores <0.45 predict a 6-month survival of 85%.
            if (lilleScore > 0.45) {
                planStr += " (25 percent 6-month survival)";
            } else {
                planStr += " (85 percent 6-month survival)";
            }
        } // End of Computing Lille

        WriteComment(planStr);
    } // if ((planStr != null) && (planStr != ""))

    WriteCommentIfSelected(activeControlPanel, "HEPATITIS_Trend_OPTION");

    // Diff
    var optionNameList = [ "HEPATITIS_Diff_Viral_OPTION", "HEPATITIS_Alcohol_OPTION", "HEPATITIS_Dif_Toxicity_OPTION", "HEPATITIS_Autoimmune_OPTION"];
    WriteListOfSelectedValues(activeControlPanel, "Possible causes include: ", false, "", optionNameList, "")

    // Workup
    var optionNameList = [ 'HEPATITIS_CheckHepAIgG_OPTION', 'HEPATITIS_CheckHepAIgM_OPTION', 'HEPATITIS_CheckHepBIgAg_OPTION',
                            'HEPATITIS_CheckHepBPCR_OPTION',  'HEPATITIS_CheckHepDIgG_OPTION', 'HEPATITIS_CheckHepEIgG_OPTION',
                            'HEPATITIS_CheckCMV_OPTION', 'HEPATITIS_CheckEBV_OPTION', 'HEPATITIS_CheckCeruloplasm_OPTION', 'HEPATITIS_CheckApap_OPTION']; 
    WriteListOfSelectedActions(activeControlPanel, "Check ", optionNameList)

    // Treat
    WriteActionIfSelected(activeControlPanel, "HEPATITIS_POSteroids_OPTION");
    WriteActionIfSelected(activeControlPanel, "HEPATITIS_Pentoxifylline_OPTION");
} // WriteHepatitisPlan






////////////////////////////////////////////////////////////////////////////////
//
// [WritePancreatitisPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WritePancreatitisPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Pancreatitis";
    modifierStr = MedNote_GetCPOptionValue("PancreatitisAcuteChronicOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr + " " + planStr;
    }
    if (PrintSingleLinePlanAtEnd('PancPlan', planStr, "Continue home medications")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "PancPlan");
    if (!activeControlPanel) {
        LogEvent("WriteIVContrastPlan. activeControlPanel is null");
        return;
    }

    //WriteComment("APACHE Score on admission = ");
    //WriteComment("Ransons Score on admission = (WBC over 16, Glc over 200, age over 55, AST over 250, LDH over 350)");
    //WriteComment("Ransons Score at 48hrs = (Hct drop over 10%, BUN increase over 5, Ca below 8, PaO2 below 60mm, (24-HCO3) over 4, IVF over 6L)");

    // Criteria
    var optionNameList = [ "PANCREATITIS_Pain_OPTION", "PANCREATITIS_Imaging_OPTION", "PANCREATITIS_Lipsase_OPTION"];
    WriteListOfSelectedValues(activeControlPanel, "Meets criteria with: ", false, "", optionNameList, "")

    // Pain
    WriteActionIfSelected(activeControlPanel, "PANCREATITIS_MORPHINE_IR_OPTION");
    WriteActionIfSelected(activeControlPanel, "PANCREATITIS_Oxycodone_OPTION");
    WriteActionIfSelected(activeControlPanel, "PANCREATITIS_Dilaudid_PO_OPTION");
    WriteActionIfSelected(activeControlPanel, "PANCREATITIS_Dilaudid_IV_OPTION");
    WriteActionIfSelected(activeControlPanel, "PANCREATITIS_PCA_OPTION");
    // Fluids
    WriteActionIfSelected(activeControlPanel, "PANCREATITIS_FluidBolusOption");
    WriteActionIfSelected(activeControlPanel, "PANCREATITIS_MaintFluidOption");
    // Nausea
    WriteActionIfSelected(activeControlPanel, "PANCREATITIS_ONDANSETRON_PRN_OPTION");
    WriteActionIfSelected(activeControlPanel, "PANCREATITIS_ONDANSETRON_SCHEDULED_OPTION");
    WriteActionIfSelected(activeControlPanel, "PANCREATITIS_Prochlorperazine_OPTION");
    WriteActionIfSelected(activeControlPanel, "PANCREATITIS_Phenergan_OPTION");
    // Diet
    WriteActionIfSelected(activeControlPanel, "PANCREATITIS_Diet_OPTION");
    WriteActionIfSelected(activeControlPanel, "PANCREATITIS_Pancrealipase_OPTION");
} // WritePancreatitisPlan




////////////////////////////////////////////////////////////////////////////////
//
// [WriteGISymptomsPlan]
//
// Created 2022-6-14
// Updated 2022-11-3
////////////////////////////////////////////////////////////////////////////////
function 
WriteGISymptomsPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Nausea and Vomiting";
    modifierStr = MedNote_GetCPOptionValue("GISymptomTypeOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr;
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "GISymptomsPlan");
    if (!activeControlPanel) {
        LogEvent("WriteIVContrastPlan. activeControlPanel is null");
        return;
    }

    var optionNameList = [ "GISymptoms_EmesisBilious_OPTION", "GISymptoms_EmesisBloodyOption"];
    WriteListOfSelectedValues(activeControlPanel, "The emesis is ", false, "", optionNameList, "")

    var optionNameList = [ "GISymptoms_DiarrheaBloodyOption", "GISymptoms_Melena_OPTION"];
    WriteListOfSelectedValues(activeControlPanel, "There diarrhea is ", false, "", optionNameList, "")

    WriteCommentIfSelected(activeControlPanel, 'GISymptoms_StartTimeOption');

    var optionNameList = [ "GISymptoms_SxLocation_OPTION", "GISymptoms_SxQuality_OPTION", "GISymptoms_SxRadiate_OPTION", "GISymptoms_SxSevere_OPTION", "GISymptoms_SxConstant_OPTION", "GISymptoms_SxUnique_OPTION", "GISymptoms_SxWithFood_OPTION", "GISymptoms_SxWithStool_OPTION"];
    WriteListOfSelectedValues(activeControlPanel, "The abdominal pain is ", false, "", optionNameList, "")


    ///////////////////////////
    //Workup
    ///////////////////////////
    var optionNameList = [ "GISymptoms_CheckLactate_Option", "GISymptoms_CheckLipase_Option", "GISymptoms_CheckCRP_Option", 
                            "GISymptoms_CheckA1c_Option", "GISymptoms_CheckAcuteHep_Option", "GISymptoms_CheckApap_Option", 
                            "GISymptoms_CheckAsa_Option", "GISymptoms_CheckHCG_Option", "GISymptoms_CheckCMV_Option", 
                            "GISymptoms_CheckTTG_Option", "GISymptoms_CheckGliadin_Option", "GISymptoms_CheckEndomysial_Option",
                            "GISymptoms_CheckCA125_Option", "GISymptoms_CheckCEA_Option", "GISymptoms_CheckCA19_Option"];
    WriteListOfSelectedActions(activeControlPanel, "Check serum labs: ", optionNameList)

    var optionNameList = [ "GISymptoms_CheckCDiff_Option", "GISymptoms_CheckGIPanel_Option", 
            "GISymptoms_CheckLactoferrin_Option", "GISymptoms_CheckHPylori_Option",  "GISymptoms_CheckStoolCMV_Option",
            "GISymptoms_CheckStoolCalprotectin_Option"];
    WriteListOfSelectedActions(activeControlPanel, "Check stool labs: ", optionNameList)

    var optionNameList = [ "GISymptoms_CheckUDS_Option"];
    WriteListOfSelectedActions(activeControlPanel, "Check urine labs: ", optionNameList)

    WriteActionIfSelected(activeControlPanel, "GISymptoms_CheckCT_Option");
    WriteActionIfSelected(activeControlPanel, "GISymptoms_CheckCTAMesenteric_Option");
    WriteActionIfSelected(activeControlPanel, "GISymptoms_CheckDopplerMesenteric_Option");


    ///////////////////////////
    //Treat
    ///////////////////////////
    // Antibiotics
    var actionNameList = [ "GISymptoms_PipTazoOption", "GISymptoms_CeftriaxoneOption", "GISymptoms_FlagylOption"];
    WriteListOfSubActions("Antibiotics", actionNameList);

    // Fluids
    WriteActionIfSelected(activeControlPanel, "GISymptoms_FluidBolusOption");
    WriteActionIfSelected(activeControlPanel, "GISymptoms_MaintFluidOption");

    // Pain Control
    var actionNameList = [ "GISymptoms_MORPHINE_IR_OPTION", "GISymptoms_Oxycodone_OPTION", "GISymptoms_Dilaudid_PO_OPTION", "GISymptoms_Dilaudid_IV_OPTION", "GISymptoms_PCA_OPTION"];
    WriteListOfSubActions("Analgesics", actionNameList);

    // Nausea
    var actionNameList = [ "GISymptoms_ONDANSETRON_PRN_OPTION", "GISymptoms_ONDANSETRON_SCHEDULED_OPTION", "GISymptoms_Prochlorperazine_OPTION", "GISymptoms_Phenergan_OPTION"];
    WriteListOfSubActions("Antiemetics", actionNameList);
    WriteActionIfSelected(activeControlPanel, "GISymptoms_Cyproheptadine_OPTION");
    WriteActionIfSelected(activeControlPanel, "GISymptoms_Amitriptylene_OPTION");
} // WriteGISymptomsPlan







////////////////////////////////////////////////////////////////////////////////
//
// [WriteGoutPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteGoutPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Gout";
    modifierStr = MedNote_GetCPOptionValue("GoutAcuteChronicOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr + " " + planStr;
    }
    if (PrintSingleLinePlanAtEnd('GoutPlan', planStr, "Continue home medications")) {
        return
    }

    activeControlPanel = MedNote_StartNewPlanSection(planStr, "GoutPlan");
    if (!activeControlPanel) {
        LogEvent("WriteIVContrastPlan. activeControlPanel is null");
        return;
    }

    // Status
    WriteCommentIfSelected(activeControlPanel, "GOUT_FLARING_OPTION");
    WriteCommentIfSelected(activeControlPanel, "GOUT_LAST_FLARE_OPTION");
    planStr = MedNote_GetCPOptionValue("GOUT_SHOW_URATE_OPTION");
    if ((planStr != null) && (planStr != "")) {
        var ageStarted = GetFloatInputForControlPanel(activeControlPanel, 'GOUT_SERUM_URATE_INPUT');
        if (ageStarted > 0) {
            planStr = planStr.replace("xxxx", ageStarted);
        }
        WriteComment(planStr);
    }

    // Home Meds
    var optionNameList = [ "GOUT_HOME_ALLOPURINOL_OPTION"];
    WriteListOfSelectedValues(activeControlPanel, "Home medications: ", false, "", optionNameList, "")

    // Treat
    WriteActionIfSelected(activeControlPanel, "GOUT_Target_OPTION");
    WriteActionIfSelected(activeControlPanel, "GOUT_Allopurinol_OPTION");
    WriteActionIfSelected(activeControlPanel, "GOUT_Prednisone_OPTION");
    WriteActionIfSelected(activeControlPanel, "GOUT_Febuxostat_OPTION");
    WriteActionIfSelected(activeControlPanel, "GOUT_SLOW_DIURETICS_OPTION");
} // WriteGoutPlan






////////////////////////////////////////////////////////////////////////////////
//
// [WriteSyncopePlan]
//
// 2023-9-25 - Merged plan items into 1 line
////////////////////////////////////////////////////////////////////////////////
function 
WriteSyncopePlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Syncope";
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "SyncopePlan");
    if (!activeControlPanel) {
        LogEvent("WriteIVContrastPlan. activeControlPanel is null");
        return;
    }

    // Cardiogenic
    WriteCommentIfSelected(activeControlPanel, "SYNCOPE_Orthostatic_OPTION");
    WriteCommentIfSelected(activeControlPanel, "SYNCOPE_SHOW_EKG_OPTION");
    // Differential
    var optionNameList = [ "SYNCOPE_DIFFERENTIAL_Medications_OPTION", "SYNCOPE_DIFFERENTIAL_Cardiogenic_OPTION", "SYNCOPE_DIFFERENTIAL_Neuro_OPTION", "SYNCOPE_DIFFERENTIAL_Hematologic_OPTION", "SYNCOPE_DIFFERENTIAL_Infectious_OPTION"];
    WriteListOfSelectedValues(activeControlPanel, "Possible causes include: ", false, "", optionNameList, "")

    // Workup
    var optionNameList = [ "SYNCOPE_CT_HEAD_OPTION", "SYNCOPE_UDS_OPTION", "SYNCOPE_EEG_OPTION"];
    WriteListOfSelectedActions(activeControlPanel, "Check CNS causes: ", optionNameList)

    var optionNameList = [ "SYNCOPE_GET_EKG_OPTION", "SYNCOPE_Interrogate_ICD_OPTION", "SYNCOPE_Telemetry_OPTION"];
    WriteListOfSelectedActions(activeControlPanel, "Check cardiac causes: ", optionNameList)

    var optionNameList = [ "SYNCOPE_PROCAL_OPTION", "SYNCOPE_BLOOD_CULTURES_OPTION"];
    WriteListOfSelectedActions(activeControlPanel, "Check infectious causes: ", optionNameList)

    // Treat
    WriteActionIfSelected(activeControlPanel, "SYNCOPE_IV_FLUIDS_OPTION");
    WriteActionIfSelected(activeControlPanel, "SYNCOPE_HOLTER_OPTION");
} // WriteSyncopePlan






////////////////////////////////////////////////////////////////////////////////
//
// [WritePressureUlcersPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WritePressureUlcersPlan() { 
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Pressure Ulcer";
    modifierStr = MedNote_GetCPOptionValue("PressureUlcer_StageOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr += " " + modifierStr;
    }
    planStr += " (Present on admission)";

    if (PrintSingleLinePlanAtEnd('PressureUlcersPlan', planStr, "Wound care")) {
        return
    }

    activeControlPanel = MedNote_StartNewPlanSection(planStr, "PressureUlcersPlan");
    if (!activeControlPanel) {
        LogEvent("WriteIVContrastPlan. activeControlPanel is null");
        return;
    }

    // Treat
    WriteActionIfSelected(activeControlPanel, "PRESSURE_ULCER_WOUND_CARE_OPTION");
} // WritePressureUlcersPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteLegFracturePlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteLegFracturePlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Femoral neck fracture";
    modifierStr = MedNote_GetCPOptionValue("LegFracture_JointMODIFIER");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr + " fracture";
    }
    modifierStr = MedNote_GetCPOptionValue("LegFracture_SideMODIFIER");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr + " " + planStr;
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "LegFracturePlan");
    if (!activeControlPanel) {
        LogEvent("WriteIVContrastPlan. activeControlPanel is null");
        return;
    }

    // Pain
    WriteActionIfSelected(activeControlPanel, "LEG_FRACTURE_Opioids_OPTION");
    // Pre Op
    WriteActionIfSelected(activeControlPanel, "LEG_FRACTURE_NON_WEIGHT_BEARING_OPTION");
    WriteActionIfSelected(activeControlPanel, "LEG_FRACTURE_INR_OPTION");
    WriteActionIfSelected(activeControlPanel, "LEG_FRACTURE_NPO_OPTION");
    // Prevent
    WriteActionIfSelected(activeControlPanel, "LEG_FRACTURE_CHECK_VIT_D_OPTION");
} // WriteLegFracturePlan




////////////////////////////////////////////////////////////////////////////////
//
// [WriteDICPlan]
//
// Updated 2020-4-19
// 2023-11-14 - Combined workup labs into a single task
////////////////////////////////////////////////////////////////////////////////
function 
WriteDICPlan() {
    var planStr = "";
    var modifierStr = "";
    var planConfigState = null;
    var activeControlPanel = null;

    ///////////////////
    // Start the plan section
    planStr = "DIC";
    //modifierStr = MedNote_GetCPOptionValue("OSAPossibleModifier");

    activeControlPanel = MedNote_StartNewPlanSection(planStr, "DICPlan");
    if (!activeControlPanel) {
        LogEvent("WriteDICPlan. activeControlPanel is null");
        return;
    }

    var optionNameList = [ "DIC_Diagnose_ISTH_PLTS_Option", "DIC_Diagnose_ISTH_PT_Option", 
                            "DIC_Diagnose_ISTH_Fibrinogen_Option", "DIC_Diagnose_ISTH_D_DIMER_Option"];
    MedNote_WriteScoreFromSelectedValues(activeControlPanel, "The ISTH score is ", " with: ", optionNameList, "");

    // Status
    WriteCommentIfSelected(activeControlPanel, "DICHgbTrendOption");
    WriteCommentIfSelected(activeControlPanel, "DICPlateletTrendOption");
    WriteCommentIfSelected(activeControlPanel, "DICINRTrendOption");
    WriteCommentIfSelected(activeControlPanel, "DICFibrinogenOption");
    WriteCommentIfSelected(activeControlPanel, "DICDDimerTrendOption");

    // Monitor
    var optionNameList = [ 'DIC_Check_CBC_Option', 'DIC_Check_Fibrinogen_Option', 'DIC_Check_INR_Option', 'DIC_Check_DDimer_Option']; 
    WriteListOfSelectedActions(activeControlPanel, "Check daily ", optionNameList)

    // Transfuse
    WriteActionIfSelected(activeControlPanel, "DIC_Treat_PRN_PRBC_Option");
    WriteActionIfSelected(activeControlPanel, "DIC_Treat_PRN_PLTS_Option");
    WriteActionIfSelected(activeControlPanel, "DIC_Treat_PRN_FFP_Option");
    WriteActionIfSelected(activeControlPanel, "DIC_Treat_PRN_Cryo_Option");

    // Other
    WriteActionIfSelected(activeControlPanel, "DIC_Infection_Option");
} // WriteDICPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteCovidPlan]
//
// Updated 2020-4-17
// Updated 2020-5-1
// Updated 2020-5-23
// Updated 2020-11-1
// Updated 2020-12-2
// Updated 2020-12-30
// Updated 2021-1-15
// Updated 2022-2-14
// Updated 2022-7-18
// 2023-11-14 - Combined workup labs into a single task
////////////////////////////////////////////////////////////////////////////////
function 
WriteCovidPlan() {
    var planStr = "";
    var modifierStr = "";
    var planConfigState = null;
    var activeControlPanel = null;

    ///////////////////
    // Start the plan section
    planStr = "Viral pneumonia secondary to SARS/CoVID-19 pneumonia";
    modifierStr = MedNote_GetCPOptionValue("CovidPossibleModifier");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr + planStr;
    }
    MedNote_StartNewPlanSection(planStr, "CovidPlan");
    MedNote_AddRelatedProblem("Acute hypoxic respiratory failure requiring supplemental oxygen secondary to COVID 19");

    // Get the control panel. 
    // This was set up by the call to MedNote_StartNewPlanSection.
    planConfigState = g_AllPlansDeclaration['CovidPlan'];
    activeControlPanel = planConfigState.activeControlPanel;
    if (!activeControlPanel) {
        LogEvent("WriteCovidPlan. activeControlPanel is null");
        return;
    }

    // History
    WriteCommentIfSelected(activeControlPanel, "CovidSxStartedOption");
    WriteCommentIfSelected(activeControlPanel, "CovidTestPositiveOption");
    WriteCommentIfSelected(activeControlPanel, "CovidAsymptomaticOption");

    // Status
    WriteCommentIfSelected(activeControlPanel, "CovidSpO2TrendOption");
    WriteCommentIfSelected(activeControlPanel, "CovidCRPTrendOption");
    WriteCommentIfSelected(activeControlPanel, "CovidPMNToLymphTrendOption");
    WriteCommentIfSelected(activeControlPanel, "CovidPltsTrendOption");

    var optionNameList = [ "CovidRiskCRPOver100Option", "CovidRiskDDimerOver1000Option", "CovidRiskLymphsUnder800Option", 
                            "CovidRiskLDHOver245Option", "CovidRiskFerritinOver500Option"];
    WriteListOfSelectedValues(activeControlPanel, "The patient has the following lab risk factors: ", false, "", optionNameList, "")

    var optionNameList = [ "CovidRiskAgeOver65Option", "CovidRiskDM2Option", "CovidRiskAsthmaOption", "CovidRiskCOPDOption", 
                           "CovidRiskTobaccoOption", "CovidRiskObeseOption", "CovidRiskCADOption", "CovidRiskCHFOption", 
                           "CovidRiskCVAOption", "CovidRiskLungDiseaseOption", "CovidRiskCirrhosisOption", 
                           "CovidRiskImmuneSuppressionOption", "CovidRiskCFOption", "CovidRiskSickleCellOption", "CovidRiskCancerOption"]
    WriteListOfSelectedValues(activeControlPanel, "The patient has the following clinical risk factors: ", false, "", optionNameList, "")

    // Care Plan
    WriteCommentIfSelected(activeControlPanel, "CovidNoTreatOption");
    WriteCommentIfSelected(activeControlPanel, "CovidRemdesivirOnlyOption");
    WriteCommentIfSelected(activeControlPanel, "CovidNirmatrelvirOnlyOption");

    // Workup
    var optionNameList = [ 'CovidWUPCROption', 'CovidWUXRayOption', 'CovidWUProcalOption', 'CovidWURVPOption',
                            'CovidCTPEOption']; 
    WriteListOfSelectedActions(activeControlPanel, "Check ", optionNameList)

    // Monitor
    var optionNameList = [ "CovidCRPDailyOption", "CovidCBCDiffPDailyOption",
                           "CovidVBGDailyOption", "CovidDDimerDailyOption"];
    WriteListOfSelectedActions(activeControlPanel, "Check daily labs: ", optionNameList)

    // Treat
    WriteActionIfSelected(activeControlPanel, "CovidDexamethasoneOption");
    WriteActionIfSelected(activeControlPanel, "CovidRemdesivirOption");
    WriteActionIfSelected(activeControlPanel, "CovidBaricitinibOption");
    WriteActionIfSelected(activeControlPanel, "CovidDiureticsOption");
    WriteActionIfSelected(activeControlPanel, "CovidNirmatrelvirOption");
    WriteActionIfSelected(activeControlPanel, "CovidAntibioticsOption");

    // Other treat
    WriteActionIfSelected(activeControlPanel, "CovidO2Option");
    WriteActionIfSelected(activeControlPanel, "CovidPrecautionsOption");
    WriteActionIfSelected(activeControlPanel, "CovidProneOption");

    WriteActionIfSelected(activeControlPanel, "CovidAlbuterolOption");
    WriteActionIfSelected(activeControlPanel, "CovidApapOption");
    WriteActionIfSelected(activeControlPanel, "CovidGuaifenesinOption");
    WriteActionIfSelected(activeControlPanel, "CovidPPIOption");
    WriteActionIfSelected(activeControlPanel, "CovidInsulinOption");
} // WriteCovidPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteAnemiaPlan]
//
// Updated 2022-9-25
// Updated 2022-1-18
// Updated 2020-5-24
////////////////////////////////////////////////////////////////////////////////
function 
WriteAnemiaPlan() {
    var planStr = "";
    var modifierStr = "";
    var activeControlPanel = null;

    ///////////////////
    // Start the plan section
    planStr = "Anemia";
    modifierStr = MedNote_GetCPOptionValue("AnemiaAcuteChronicModifier");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr + " " + planStr;
    }
    modifierStr = MedNote_GetCPOptionValue("AnemiaChronicDiseaseModifier");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr;
    }
    if (PrintSingleLinePlanAtEnd('AnemiaPlan', planStr, "Transfuse for Hgb below 7")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "AnemiaPlan");
    if (!activeControlPanel) {
        LogEvent("WriteAnemiaPlan. activeControlPanel is null");
        return;
    }

    // Modifiers
    MedNote_AddRelatedProblemIfSelected(activeControlPanel, "AnemiaCKDModifier");
    MedNote_AddRelatedProblemIfSelected(activeControlPanel, "AnemiaBloodLossModifier");
    MedNote_AddRelatedProblemIfSelected(activeControlPanel, "AnemiaMicrocyticModifier");

    // Type
    var optionNameList = [ "AnemiaShowHgbOption", "AnemiaShowMCVOption"];
    WriteListOfSelectedValues(activeControlPanel, "", false, "", optionNameList, "")
    WriteCommentIfSelected(activeControlPanel, "AnemiaShowBUNOption");

    var optionNameList = [ "AnemiaDiffBloodLossOption", "AnemiaDiffHemolysisOption", "AnemiaDiffChronicdiseaseOption", 
                            "AnemiaDiffUnderproductionOption", "AnemiaDiffSequestrationOption"];
    WriteListOfSelectedValues(activeControlPanel, "Possible causes include: ", false, "", optionNameList, "")

    ////////////////////////////////////////////////////////////
    // Results
    normalResults = "";
    possibleACDResults = "";
    possibleFeDeficiencyResults = "";
    possibleNutritionResults = "";
    bloodLossResults = "";


    //////////////////////////
    // Iron Binding Results
    optionName = "AnemiaTIBCStatusOption"
    toggleState = MedNote_GetCPOptionToggleState(optionName);
    if (toggleState == 0) {
        possibleACDResults = AddItemToCauseList(activeControlPanel, optionName, possibleACDResults);
    } else if (toggleState > 0) {
        normalResults = AddItemToCauseList(activeControlPanel, optionName, normalResults);
    }
    optionName = "AnemiaTransferrinStatusOption"
    toggleState = MedNote_GetCPOptionToggleState(optionName);
    if (toggleState == 0) {
        possibleACDResults = AddItemToCauseList(activeControlPanel, optionName, possibleACDResults);
    } else if (toggleState > 0) {
        normalResults = AddItemToCauseList(activeControlPanel, optionName, normalResults);
    }
    optionName = "AnemiaFeSatStatusOption"
    toggleState = MedNote_GetCPOptionToggleState(optionName);
    if (toggleState == 0) {
        possibleACDResults = AddItemToCauseList(activeControlPanel, optionName, possibleACDResults);
    } else if (toggleState > 0) {
        normalResults = AddItemToCauseList(activeControlPanel, optionName, normalResults);
    }

    ////////////////////////////
    // Nutritional Results
    optionName = "AnemiaB12StatusOption"
    toggleState = MedNote_GetCPOptionToggleState(optionName);
    //LogEvent("B12 toggleState = " + toggleState);
    if (toggleState > 0) {
        possibleNutritionResults = AddItemToCauseList(activeControlPanel, optionName, possibleNutritionResults);
        //LogEvent("B12 toggleState = " + toggleState);
    } else if (toggleState == 0) {
        normalResults = AddItemToCauseList(activeControlPanel, optionName, normalResults);
    }
    optionName = "AnemiaFolateStatusOption"
    toggleState = MedNote_GetCPOptionToggleState(optionName);
    if (toggleState > 0) {
        possibleNutritionResults = AddItemToCauseList(activeControlPanel, optionName, possibleNutritionResults);
    } else if (toggleState == 0) {
        normalResults = AddItemToCauseList(activeControlPanel, optionName, normalResults);
    }

    ////////////////////////////
    // Blood Loss Results
    optionName = "AnemiaHemoccultStatusOption"
    toggleState = MedNote_GetCPOptionToggleState(optionName);
    //LogEvent("B12 toggleState = " + toggleState);
    if (toggleState > 0) {
        bloodLossResults = AddItemToCauseList(activeControlPanel, optionName, bloodLossResults);
        //LogEvent("B12 toggleState = " + toggleState);
    } else if (toggleState == 0) {
        normalResults = AddItemToCauseList(activeControlPanel, optionName, normalResults);
    }
    optionName = "AnemiaHPyloriStatusOption"
    toggleState = MedNote_GetCPOptionToggleState(optionName);
    if (toggleState > 0) {
        bloodLossResults = AddItemToCauseList(activeControlPanel, optionName, bloodLossResults);
    } else if (toggleState == 0) {
        normalResults = AddItemToCauseList(activeControlPanel, optionName, normalResults);
    }


    if (normalResults != "") {
        WriteComment(normalResults);
    }
    if (bloodLossResults != "") {
        WriteComment("Findings that suggest blood loss include: " + bloodLossResults);
    }
    if (possibleACDResults != "") {
        WriteComment("Findings that suggest anemia of chronic inflammation include: " + possibleACDResults);
    }
    if (possibleNutritionResults != "") {
        WriteComment("Findings that suggest nutritional deficiencies include: " + possibleNutritionResults);
    }


    ///////////////////////////
    //Workup
    var optionNameList = [ "AnemiaCheckPeripheralSmearOption", "AnemiaCheckLDHOption", "AnemiaCheckHaptoglobinOption", 
                            "AnemiaCheckReticulocyteCountOption" ];
    WriteListOfSelectedActions(activeControlPanel, "Check for hemolysis: ", optionNameList)

    ///////////////////////////
    var optionNameList = [ "AnemiaCheckTransferrinOption", "AnemiaCheckTIBCOption", "AnemiaCheckIronBindingSaturationOption", "AnemiaCheckFerritinOption"];
    WriteListOfSelectedActions(activeControlPanel, "Check iron levels: ", optionNameList)

    ///////////////////////////
    var optionNameList = [ "AnemiaCheckHemoccultOption", "AnemiaCheckHPyloriOption", "AnemiaCheckCeliacOption", 
                            "AnemiaCheckINROption"];
    WriteListOfSelectedActions(activeControlPanel, "Check GI loss: ", optionNameList)

    ///////////////////////////
    var optionNameList = [ "AnemiaCheckB12Option", "AnemiaCheckFolateOption", "AnemiaCheckZincOption", 
                            "AnemiaCheckCopperOption", "AnemiaCheckVitKOption"];
    WriteListOfSelectedActions(activeControlPanel, "Check nutrients: ", optionNameList)

    ///////////////////////////
    var optionNameList = [ "AnemiaCheckHIVOption", "AnemiaCheckEBVOption", "AnemiaCheckHBVOption", 
                            "AnemiaCheckParvoOption"];
    WriteListOfSelectedActions(activeControlPanel, "Check infectious causes: ", optionNameList)

    ///////////////////////////
    var optionNameList = [ "AnemiaCheckDirectCoombsOption", "AnemiaCheckWarmAgglutininsOption", 
                            "AnemiaCheckColdAgglutininsOption", "AnemiaCheckANAOption"];
    WriteListOfSelectedActions(activeControlPanel, "Check autoimmune causes: ", optionNameList)


    // Monitor
    WriteActionIfSelected(activeControlPanel, "AnemiaMonitorHgbOption");
    WriteActionIfSelected(activeControlPanel, "AnemiaTrendLDHOption");
    WriteActionIfSelected(activeControlPanel, "AnemiaTrendHaptoglobinOption");

    // Treat
    WriteActionIfSelected(activeControlPanel, "AnemiaTypeScreenOption");
    WriteActionIfSelected(activeControlPanel, "AnemiaPOIronOption");
    WriteActionIfSelected(activeControlPanel, "AnemiaPRNTransfuseOption");
    WriteActionIfSelected(activeControlPanel, "AnemiaPPIOption");
} // WriteAnemiaPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WritePEDVTPlan]
//
// Created 2020-5-25
////////////////////////////////////////////////////////////////////////////////
function 
WritePEDVTPlan() {
    //LogEvent("WritePEDVTPlan");
    var modifierStr = "";
    var planNameStr = "Pulmonary Embolism";
    var str;
    var activeControlPanel = null;

    ///////////////////////////
    // Start the section
    str = MedNote_GetCPOptionValue("PEDVTAcuteChronicOption");
    if ((str != null) && (str != "")) {
        modifierStr = modifierStr + str;
    }
    str = MedNote_GetCPOptionValue("PEDVTMassiveOption");
    if ((str != null) && (str != "")) {
        modifierStr = modifierStr + str;
    }
    planNameStr = MedNote_GetCPOptionValue("PEDVTPEvsDVTOption");
    if ((planNameStr == null) || (planNameStr == "")) {
        planNameStr = "Pulmonary Embolism";
    }
    planNameStr = modifierStr + planNameStr;
    activeControlPanel = MedNote_StartNewPlanSection(planNameStr, "PEDVTPlan");
    if (!activeControlPanel) {
        LogEvent("WritePEDVTPlan. activeControlPanel is null");
        return;
    }

    ///////////////////////////////
    // Type
    WriteCommentIfSelected(activeControlPanel, 'PEDVTShowEchoOption');
    WriteCommentIfSelected(activeControlPanel, 'PEDVTProvokedOption');

    ///////////////////////////////
    var optionNameList = [ "PEDVTRisksPastDVTOption", "PEDVTRisksPastCVAOption", 
                            "PEDVTRisksCADOption", "PEDVTRisksOCPOption",
                            "PEDVTRisksMiscarriageOption", "PEDVTRisksFamilyOption"];
    WriteListOfSelectedValues(activeControlPanel, "Additional risk factors include ", false, "", optionNameList, "");

    ///////////////////////////////
    var optionNameList = [ "PEDVTHomeCoumadinOption", "PEDVTHomeApixibanOption" ];
    WriteListOfSelectedValues(activeControlPanel, "Home medications are ", false, "", optionNameList, "");



    ///////////////////////////////
    // Workup
    WriteActionIfSelected(activeControlPanel, 'PEDVTGetEchoOption');
    WriteActionIfSelected(activeControlPanel, 'PEDVTGetINROption');

    ///////////////////////////////
    // Anticoag
    WriteActionIfSelected(activeControlPanel, 'PEDVTLovenoxOption');
    WriteActionIfSelected(activeControlPanel, 'PEDVTApixibanOption');
    WriteActionIfSelected(activeControlPanel, 'PEDVTRivaroxabanOption');
    WriteActionIfSelected(activeControlPanel, 'PEDVTCoumadinOption');
    WriteActionIfSelected(activeControlPanel, 'PEDVTHeparinOption');
} // WritePEDVTPlan




////////////////////////////////////////////////////////////////////////////////
//
// [WriteGERDPlan]
//
// Updated 2020-5-29
////////////////////////////////////////////////////////////////////////////////
function 
WriteGERDPlan() {
    var activeControlPanel = null;
    var planStr = "";

    planStr = "Gastroesophageal Reflux Disease";
    if (PrintSingleLinePlanAtEnd('GERDPlan', planStr, "Continue home PPI")) {
        //LogEvent("WriteGERDPlan. Bail out");
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "GERDPlan");
    if (!activeControlPanel) {
        LogEvent("WriteGERDPlan. activeControlPanel is null");
        return;
    }

    WriteActionIfSelected(activeControlPanel, "OPTION_HOME_PPI_NAME");
} // WriteGERDPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteDepressionPlan]
//
// Updated 2020-5-29
////////////////////////////////////////////////////////////////////////////////
function 
WriteDepressionPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Mood Disorder";
    if (PrintSingleLinePlanAtEnd('DepressionPlan', planStr, "Continue home medications:")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "DepressionPlan");
    if (!activeControlPanel) {
        LogEvent("WriteDepressionPlan. activeControlPanel is null");
        return;
    }

    modifierStr = MedNote_GetCPOptionValue("Mood_Disorder_DepressionOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        MedNote_AddRelatedProblem(modifierStr);
    }
    modifierStr = MedNote_GetCPOptionValue("Mood_Disorder_AnxietyOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        MedNote_AddRelatedProblem(modifierStr);
    }

    // DHM
    var optionNameList = [ "MOOD_DISORDER_AxisI_OPTION"];
    WriteListOfSelectedValues(activeControlPanel, "Axis I: ", false, "", optionNameList, "")
    var optionNameList = [ "MOOD_DISORDER_AxisII_OPTION"];
    WriteListOfSelectedValues(activeControlPanel, "Axis II: ", false, "", optionNameList, "")
    var optionNameList = [ "MOOD_DISORDER_AxisIII_OPTION"];
    WriteListOfSelectedValues(activeControlPanel, "Axis III: ", false, "", optionNameList, "")
    var optionNameList = [ "MOOD_DISORDER_AxisIV_OPTION"];
    WriteListOfSelectedValues(activeControlPanel, "Axis IV: ", false, "", optionNameList, "")
    // PHQ-9 score (anhedonia + SIGECAPS, give a score 0=none,1=several days,2=over half days,3=nearly all days)Score over 9 is moderate depression

    // SIGECAPS
    var optionNameList = [ "MOOD_DISORDER_Sleep_OPTION", "MOOD_DISORDER_Interest_OPTION", "MOOD_DISORDER_Guilt_OPTION", "MOOD_DISORDER_Energy_OPTION", "MOOD_DISORDER_Concentraion_OPTION", "MOOD_DISORDER_Appetite_OPTION", "MOOD_DISORDER_Psychomotor_OPTION", "MOOD_DISORDER_Suicidal_OPTION"];
    WriteListOfSelectedValues(activeControlPanel, "PHQ-9 factors include: ", false, "", optionNameList, "")

    // Status
    WriteCommentIfSelected(activeControlPanel, "MOOD_DISORDER_SUICIDE_RISK_OPTION");
    WriteCommentIfSelected(activeControlPanel, "MOOD_DISORDER_SHOW_QTC_OPTION");

    // Comorbidities
    var optionNameList = [ "MOOD_DISORDER_MANIA_OPTION", "MOOD_DISORDER_PTSD_OPTION", "MOOD_DISORDER_ANXIETY_OPTION"];
    WriteListOfSelectedValues(activeControlPanel, "Comorbidities include: ", false, "", optionNameList, "")

    // Workup
    WriteActionIfSelected(activeControlPanel, "MOOD_DISORDER_HYPOTHYROID_OPTION");
    WriteActionIfSelected(activeControlPanel, "MOOD_DISORDER_DRUG_USE_OPTION");

    // Treat
    WriteActionIfSelected(activeControlPanel, "MOOD_DISORDER_START_SSRI_OPTION");
    WriteActionIfSelected(activeControlPanel, "MOOD_DISORDER_HOME_MEDS_OPTION");
} // WriteDepressionPlan




////////////////////////////////////////////////////////////////////////////////
//
// [WriteTobaccoPlan]
//
// Updated 2020-5-30
// Updated 2022-10-30
////////////////////////////////////////////////////////////////////////////////
function 
WriteTobaccoPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Tobacco Dependance";
    if (PrintSingleLinePlanAtEnd('TobaccoPlan', planStr, "Nicotine replacement (gum, patch)")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "TobaccoPlan");
    if (!activeControlPanel) {
        LogEvent("WriteTobaccoPlan. activeControlPanel is null");
        return;
    }

    planStr = MedNote_GetCPOptionValue("TobaccoStartedSmokingOption");
    if ((planStr != null) && (planStr != "")) {
        var ageStarted = GetFloatInputForControlPanel(activeControlPanel, 'TOBBACO_START_AGE_INPUT_CP');
        if (ageStarted > 0) {
            planStr = planStr.replace("xxx", ageStarted);
        }
        WriteComment(planStr);
    }

    WriteCommentIfSelected(activeControlPanel, 'TobaccoPacksPerDayOption');
    WriteCommentIfSelected(activeControlPanel, 'TobaccoCounseledCessationOption');
    WriteCommentIfSelected(activeControlPanel, 'TobaccoLatestChestCTOption');
    //WriteComment("At precontemplation/contemplation/preparation/action/maintenance stage");

    var optionNameList = [ "TobaccoNicotinePatchOption", "TobaccoNicotineGumOption" ];
    WriteListOfSelectedValues(activeControlPanel, "Nicotine replacement (", false, "", optionNameList, ")");
    WriteActionIfSelected(activeControlPanel, "TobaccoDeclinesNicotineReplacementOption");
    WriteActionIfSelected(activeControlPanel, "TobaccoScreenCTOption");

    //WriteAction("Varencycline");
    //WriteAction("Refer to smoking cessation program");
} // WriteTobaccoPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteObesityPlan]
//
// Updated 2020-5-30
// Updated 2022-2-14
// Updated 2022-10-30
////////////////////////////////////////////////////////////////////////////////
function 
WriteObesityPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Obesity";
    modifierStr = MedNote_GetCPOptionValue("ObesityClassOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr;
    }
    if (PrintSingleLinePlanAtEnd('ObesityPlan', planStr, "Counsel weight loss")) {
        return
    }

    activeControlPanel = MedNote_StartNewPlanSection(planStr, "ObesityPlan");
    if (!activeControlPanel) {
        LogEvent("WriteObesityPlan. activeControlPanel is null");
        return;
    }

    var optionNameList = [ "ObesityShowBMIOption"];
    var valueList = [ ""];
    var valueNameList = [ "Obesity_BMI_INPUT_CP"];
    WriteListOfSelectedValuesWithDescriptions(activeControlPanel, optionNameList, valueList, valueNameList)

    WriteCommentIfSelected(activeControlPanel, 'ObesityComplicatesOption');
    WriteCommentIfSelected(activeControlPanel, 'ObesityNoMRIOption');
    WriteCommentIfSelected(activeControlPanel, 'NoCTOption');
    WriteCommentIfSelected(activeControlPanel, 'ObesityNoIROption');

    WriteActionIfSelected(activeControlPanel, "ObesityConsultNutritionOption");
    WriteActionIfSelected(activeControlPanel, "ObesityBariatricBedOption");

    WriteActionIfSelected(activeControlPanel, "ObesityScreenLipidsOption");
    WriteActionIfSelected(activeControlPanel, "ObesityCheckA1cOption");
} // WriteObesityPlan



////////////////////////////////////////////////////////////////////////////////
//
// [WriteMalnutritionPlan]
//
// Updated 2020-5-30
////////////////////////////////////////////////////////////////////////////////
function 
WriteMalnutritionPlan() {
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Calorie and Protein Malnutrition";
    if (PrintSingleLinePlanAtEnd('MalnutritionPlan', planStr, "Diet supplements")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "MalnutritionPlan");
    if (!activeControlPanel) {
        LogEvent("xxxxx. activeControlPanel is null");
        return;
    }

    planStr = MedNote_GetCPOptionValue("MalnutritionMalnutritionOption");
    if ((planStr != null) && (planStr != "")) {
        MedNote_AddRelatedProblem(planStr);
    }
    planStr = MedNote_GetCPOptionValue("MalnutritionUnderweightOption");
    if ((planStr != null) && (planStr != "")) {
        MedNote_AddRelatedProblem(planStr);
    }
    planStr = MedNote_GetCPOptionValue("MalnutritionWtLossOption");
    if ((planStr != null) && (planStr != "")) {
        MedNote_AddRelatedProblem(planStr);
    }
    planStr = MedNote_GetCPOptionValue("MalnutritionFatLossOption");
    if ((planStr != null) && (planStr != "")) {
        MedNote_AddRelatedProblem(planStr);
    }

    if (MedNote_GetCPOptionBool("MalnutritionShowBMIOption")) {
        planStr = "On admission, BMI is ";
        bmiStr = GetStrInputForControlPanel(activeControlPanel, 'MalnutritionInputBMI_CP');
        if (bmiStr) {
            planStr += bmiStr;
        }
        WriteComment(planStr);
    }
    if (MedNote_GetCPOptionBool("MalnutritionShowPrealbuminOption")) {
        planStr = "Prealbumin is ";
        prealbStr = GetStrInputForControlPanel(activeControlPanel, 'MalnutritionInputPrealbumin_CP');
        if (prealbStr) {
            planStr += prealbStr;
        }
        WriteComment(planStr);
    }

    WriteCommentIfSelected(activeControlPanel, 'MalnutritionComplicatesCareOption');

    WriteActionIfSelected(activeControlPanel, "MalnutritionNutritionConsultOption");
    WriteActionIfSelected(activeControlPanel, "MalnutritionSupplementsOption");
    WriteActionIfSelected(activeControlPanel, "MalnutritionMultivitaminOption");
    WriteActionIfSelected(activeControlPanel, "MalnutritionDronabinolOption");
} // WriteMalnutritionPlan





////////////////////////////////////////////////////////////////////////////////
//
// [AddItemToCauseList]
//
////////////////////////////////////////////////////////////////////////////////
function 
AddItemToCauseList(activeControlPanel, itemControlID, currentList) {
    newCauseStr = MedNote_GetCPOptionValue(itemControlID);
    if (newCauseStr != "") {
        if (currentList != "") {
            currentList = currentList + ", ";
        }
        currentList += newCauseStr
    }

    return(currentList)
} // AddItemToCauseList





////////////////////////////////////////////////////////////////////////////////
//
// [PrintAKIPlan]
//
// 2020-7-22-25 - Updated
// 2021-4-24 - Get all new user input values.
// 2023-11-14 - Combined workup labs into a single task
// 2024-1-3 - Add Cardiorenal
////////////////////////////////////////////////////////////////////////////////
function 
PrintAKIPlan() {
    var activeControlPanel = null;
    var planStr;
    var modifierStr;
    var FENa = -1;
    var FEUrea = -1;
    var UPCR = -1;
    var baselineCrStr = null;
    var baselineGFRStr = null;
    var possibleCauses = "";
    var excludedCauses = "";
    var toggleState = 0;


    planStr = "Acute Kidney Injury";
    modifierStr = MedNote_GetCPOptionValue("AKIOnCKDOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr += modifierStr;
    }

    activeControlPanel = MedNote_StartNewPlanSection(planStr, "AKIPlan");
    if (!activeControlPanel) {
        return;
    }
    planStr = MedNote_GetCPOptionValue("AKICardiorenalOption");
    if ((planStr != null) && (planStr != "")) {
        MedNote_AddRelatedProblem(planStr);
    }
    planStr = MedNote_GetCPOptionValue("AKIATNOption");
    if ((planStr != null) && (planStr != "")) {
        MedNote_AddRelatedProblem(planStr);
    }

                    
    ////////////////////////////////////////////////////////////
    // Load the integer values and Calculate values
    var currentCr = GetFloatInputForControlPanel(activeControlPanel, 'Creatinine_CP');
    var currentBaselineCr = GetFloatInputForControlPanel(activeControlPanel, 'InputBaselineCreatinine_CP');
    var currentNa = GetFloatInputForControlPanel(activeControlPanel, 'InputNa_CP');
    var currentBUN = GetFloatInputForControlPanel(activeControlPanel, 'InputBUN_CP');
    var currentUrCr = GetFloatInputForControlPanel(activeControlPanel, 'InputUrineCr_CP');
    var currentUrUN = GetFloatInputForControlPanel(activeControlPanel, 'InputUUN_CP');
    var currentUrNa = GetFloatInputForControlPanel(activeControlPanel, 'InputUNa_CP');
    var currentUrProt = GetFloatInputForControlPanel(activeControlPanel, 'InputUProt_CP');
    var currentCystatinC = GetFloatInputForControlPanel(activeControlPanel, 'AKI_INPUT_CP_CysC');
    var currentAge = GetFloatInputForControlPanel(activeControlPanel, 'AKI_INPUT_CP_AGE');
    var fIsMale = GetBoolInputForControlPanel(activeControlPanel, "AKI_Male_Modifier");
    var recentCrStr = GetStrInputForControlPanel(activeControlPanel, 'Creatinine_CP');
    baselineCrStr = GetStrInputForControlPanel(activeControlPanel, 'InputBaselineCreatinine_CP');

    // FENa - Fractional Excretion Sodium
    if ((currentUrNa > 0) && (currentNa > 0) && (currentUrCr > 0) && (currentCr > 0)) {
        FENa = ((currentUrNa / currentNa) / (currentUrCr / currentCr));
        // Convert to a percentage
        FENa = FENa * 100;
        // Round it to 2 decimal places. We add 0.00001 to work around a Javascript bug.
        FENa = Math.round((FENa + 0.00001) * 100) / 100;
        SetStrOutputForControlPanel(activeControlPanel, 'ResultFENa_CP', null, "FENa = " + FENa + " percent");
    }
    // FEUrea - Fractional Excretion Urea
    if ((currentUrUN  > 0) && (currentBUN > 0) && (currentUrCr > 0) && (currentCr > 0)) {
        FEUrea = ((currentUrUN / currentBUN) / (currentUrCr / currentCr));
        // Convert to a percentage
        FEUrea = FEUrea * 100;
        // Round it to 2 decimal places. We add 0.00001 to work around a Javascript bug.
        FEUrea = Math.round((FEUrea + 0.00001) * 100) / 100;
        SetStrOutputForControlPanel(activeControlPanel, 'ResultFEUrea_CP', null, "FEUrea = " + FEUrea + " percent");
    }
    // UPCR - Urine Prot/Cr ratio
    if ((currentUrProt  > 0) && (currentUrCr > 0)) {
        UPCR = (currentUrProt / currentUrCr);
        // Round it to 2 decimal places. We add 0.00001 to work around a Javascript bug.
        UPCR = Math.round((UPCR + 0.00001) * 100) / 100;
        SetStrOutputForControlPanel(activeControlPanel, 'ResultUPCr_CP', null, "UPCR = " + UPCR);
    }


    ////////////////////////////////////////////////////////////
    planStr = "";
    if (MedNote_GetCPOptionBool("AKITrendCrOption")) {
        planStr = "Recent Creatinine trend: ";
        if (currentCr > 0) {
            planStr += currentCr;
        } else {
            planStr += recentCrStr;            
        }
        planStr += "        ";
        WriteComment(planStr);
    }
    if (MedNote_GetCPOptionBool("AKIBaselineCrOption")) {
        planStr = "Baseline Creatinine is ";
        if (baselineCrStr) {
            planStr += baselineCrStr;
        }
        if (baselineGFRStr) {
            planStr += ", Baseline GFR=" + baselineGFRStr;
        }
        WriteComment(planStr);
    }
    if (MedNote_GetCPOptionBool("AKICystatinCTrendOption")) {
        planStr = "Recent Cystatin C trend: ";
        if (currentCystatinC > 0) {
            planStr += currentCystatinC;
        }
        planStr += "        ";
        WriteComment(planStr);
    }
    WriteCommentIfSelected(activeControlPanel, "AKIEstimateGFROption");
    WriteCommentIfSelected(activeControlPanel, "AKITrendUrineOption");

    // KDIGO
    planStr = MedNote_GetCPOptionValue("AKIKDIGOOption");
    if ((planStr != null) && (planStr != "")) {
        if (planStr == 'CALCULATE') {
            if ((currentCr < 0) || (baselineCr < 0)) {
                planStr = "This is KDIGO Stage xxxx";
            } else if (currentCr >= (3 * baselineCr)) {
                planStr = MedNote_GetCPOptionValueForIndex('AKIKDIGOOption', 2);
            } else if (currentCr >= (2 * baselineCr)) {
                planStr = MedNote_GetCPOptionValueForIndex('AKIKDIGOOption', 1);
            } else if ((currentCr >= (0.3 + baselineCr)) || (currentCr >= (1.5 * baselineCr))) {
                planStr = MedNote_GetCPOptionValueForIndex('AKIKDIGOOption', 0);
            } else if ((currentCr >= (0.3 + baselineCr)) || (currentCr >= (1.5 * baselineCr))) {
                planStr = MedNote_GetCPOptionValueForIndex('AKIKDIGOOption', 0);
            } else {
                planStr = MedNote_GetCPOptionValueForIndex('AKIKDIGOOption', 0);
            }
        }
        WriteComment(planStr);
    } // KDIGO



    //////////////////////////////////
    // Results
    // FEUrea
    planStr = MedNote_GetCPOptionValue("AKIFEUreaOption");
    if ((planStr != null) && (planStr != "")) {
        if (planStr == 'COMPUTE') {
            if (FEUrea >= 0) {
                if (FEUrea <= 35.0) {
                    planStr = MedNote_GetCPOptionValueForIndex('AKIFEUreaOption', 0);
                } else {
                    planStr = MedNote_GetCPOptionValueForIndex('AKIFEUreaOption', 1);
                }
            } else {
                planStr = "FEUrea is xxxx";
            }
        }
        if (FEUrea > 0) {
            FEUreaStr = "" + FEUrea;
            planStr = planStr.replace("xxxx", FEUreaStr);
        }
        WriteComment(planStr);
    } // FEUrea

    // FENa
    planStr = MedNote_GetCPOptionValue("AKIFENaOption");
    if ((planStr != null) && (planStr != "")) {
        if (planStr == 'COMPUTE') {
            if (FENa >= 0) {
                if (FENa <= 1.0) {
                    planStr = MedNote_GetCPOptionValueForIndex('AKIFENaOption', 0);
                } else {
                    planStr = MedNote_GetCPOptionValueForIndex('AKIFENaOption', 1);
                }
            } else {
                planStr = "FENa is xxxx";
            }
        }
        if (FENa > 0) {
            FENaStr = "" + FENa;
            planStr = planStr.replace("xxxx", FENaStr);
        }
        WriteComment(planStr);
    } // FENa
    WriteCommentIfSelected(activeControlPanel, 'AKIUAInfectionOption');
    WriteCommentIfSelected(activeControlPanel, 'AKIUSHydroOption');
    WriteCommentIfSelected(activeControlPanel, 'AKISpunUrineOption');
    WriteCommentIfSelected(activeControlPanel, 'AKIUPCROption');
    WriteCommentIfSelected(activeControlPanel, 'AKIAbdSoftOption');
    WriteCommentIfSelected(activeControlPanel, 'AKIHasFoleyOption');


    ////////////////////////////////////////////////////////////
    // HRS
    possibleHRS = "";
    excludedHRS = "";
    toggleState = MedNote_GetCPOptionToggleState("AKIHRSAscitesOption");
    if (toggleState == 0) {
        possibleHRS = AddItemToCauseList(activeControlPanel, "AKIHRSAscitesOption", possibleHRS);
    } else if (toggleState > 0) {
        excludedHRS = AddItemToCauseList(activeControlPanel, "AKIHRSAscitesOption", excludedHRS);
    }
    toggleState = MedNote_GetCPOptionToggleState("AKIHRSLowBPOption");
    if (toggleState == 0) {
        possibleHRS = AddItemToCauseList(activeControlPanel, "AKIHRSLowBPOption", possibleHRS);
    } else if (toggleState > 0) {
        excludedHRS = AddItemToCauseList(activeControlPanel, "AKIHRSLowBPOption", excludedHRS);
    }
    toggleState = MedNote_GetCPOptionToggleState("AKIHRSLowNaOption");
    if (toggleState == 0) {
        possibleHRS = AddItemToCauseList(activeControlPanel, "AKIHRSLowNaOption", possibleHRS);
    } else if (toggleState > 0) {
        excludedHRS = AddItemToCauseList(activeControlPanel, "AKIHRSLowNaOption", excludedHRS);
    }
    if (excludedHRS != "") {
        WriteComment("Findings that are inconsistent with Hepatorenal include: " + excludedHRS);
    }
    if (possibleHRS != "") {
        WriteComment("Findings consistent with possible Hepatorenal include: " + possibleHRS);
    }


    ////////////////////////////////////////////////////////////
    // Cardionrenal
    possibleCardionrenal = "";
    excludedCardionrenal = "";
    toggleState = MedNote_GetCPOptionToggleState("AKIOverloadedOption");
    if (toggleState == 0) {
        excludedCardionrenal = AddItemToCauseList(activeControlPanel, "AKIOverloadedOption", excludedCardionrenal);
    } else if (toggleState > 0) {
        possibleCardionrenal = AddItemToCauseList(activeControlPanel, "AKIOverloadedOption", possibleCardionrenal);
    }
    toggleState = MedNote_GetCPOptionToggleState("AKICXRResultsOption");
    if (toggleState == 0) {
        excludedCardionrenal = AddItemToCauseList(activeControlPanel, "AKICXRResultsOption", excludedCardionrenal);
    } else if (toggleState > 0) {
        possibleCardionrenal = AddItemToCauseList(activeControlPanel, "AKICXRResultsOption", possibleCardionrenal);
    }
    toggleState = MedNote_GetCPOptionToggleState("AKIBNPLowOption");
    if (toggleState == 0) {
        excludedCardionrenal = AddItemToCauseList(activeControlPanel, "AKIBNPLowOption", excludedCardionrenal);
    } else if (toggleState > 0) {
        possibleCardionrenal = AddItemToCauseList(activeControlPanel, "AKIBNPLowOption", possibleCardionrenal);
    }
    if (excludedCardionrenal != "") {
        WriteComment("Findings that are inconsistent with Cardionrenal include: " + excludedCardionrenal);
    }
    if (possibleCardionrenal != "") {
        WriteComment("Findings consistent with possible Cardionrenal include: " + possibleCardionrenal);
    }


    ////////////////////////////////////////////////////////////
    // Possible Causes
    WriteCommentIfSelected(activeControlPanel, 'AKIStartedOption');
    possibleCauses = "";
    excludedCauses = "";

    toggleState = MedNote_GetCPOptionToggleState("AKISepsisption");
    if (toggleState == 0) {
        possibleCauses = AddItemToCauseList(activeControlPanel, "AKISepsisption", possibleCauses);
    } else if (toggleState > 0) {
        excludedCauses = AddItemToCauseList(activeControlPanel, "AKISepsisption", excludedCauses);
    }
    toggleState = MedNote_GetCPOptionToggleState("AKIInfectionOption");
    if (toggleState == 0) {
        possibleCauses = AddItemToCauseList(activeControlPanel, "AKIInfectionOption", possibleCauses);
    } else if (toggleState > 0) {
        excludedCauses = AddItemToCauseList(activeControlPanel, "AKIInfectionOption", excludedCauses);
    }
    toggleState = MedNote_GetCPOptionToggleState("AKIOverdiuresisOption");
    if (toggleState == 0) {
        possibleCauses = AddItemToCauseList(activeControlPanel, "AKIOverdiuresisOption", possibleCauses);
    } else if (toggleState > 0) {
        excludedCauses = AddItemToCauseList(activeControlPanel, "AKIOverdiuresisOption", excludedCauses);
    }
    toggleState = MedNote_GetCPOptionToggleState("AKICHFOption");
    if (toggleState == 0) {
        possibleCauses = AddItemToCauseList(activeControlPanel, "AKICHFOption", possibleCauses);
    } else if (toggleState > 0) {
        excludedCauses = AddItemToCauseList(activeControlPanel, "AKICHFOption", excludedCauses);
    }
    toggleState = MedNote_GetCPOptionToggleState("AKIObstructionOption");
    if (toggleState == 0) {
        possibleCauses = AddItemToCauseList(activeControlPanel, "AKIObstructionOption", possibleCauses);
    } else if (toggleState > 0) {
        excludedCauses = AddItemToCauseList(activeControlPanel, "AKIObstructionOption", excludedCauses);
    }
    toggleState = MedNote_GetCPOptionToggleState("AKIBloodLossOption");
    if (toggleState == 0) {
        possibleCauses = AddItemToCauseList(activeControlPanel, "AKIBloodLossOption", possibleCauses);
    } else if (toggleState > 0) {
        excludedCauses = AddItemToCauseList(activeControlPanel, "AKIBloodLossOption", excludedCauses);
    }
    toggleState = MedNote_GetCPOptionToggleState("AKIPoorPOOption");
    if (toggleState == 0) {
        possibleCauses = AddItemToCauseList(activeControlPanel, "AKIPoorPOOption", possibleCauses);
    } else if (toggleState > 0) {
        excludedCauses = AddItemToCauseList(activeControlPanel, "AKIPoorPOOption", excludedCauses);
    }
    toggleState = MedNote_GetCPOptionToggleState("AKIMedChangesOption");
    if (toggleState == 0) {
        possibleCauses = AddItemToCauseList(activeControlPanel, "AKIMedChangesOption", possibleCauses);
    } else if (toggleState > 0) {
        excludedCauses = AddItemToCauseList(activeControlPanel, "AKIMedChangesOption", excludedCauses);
    }
    toggleState = MedNote_GetCPOptionToggleState("AKINSAIDsOption");
    if (toggleState == 0) {
        possibleCauses = AddItemToCauseList(activeControlPanel, "AKINSAIDsOption", possibleCauses);
    } else if (toggleState > 0) {
        excludedCauses = AddItemToCauseList(activeControlPanel, "AKINSAIDsOption", excludedCauses);
    }
    toggleState = MedNote_GetCPOptionToggleState("AKICTContrastOption");
    if (toggleState == 0) {
        possibleCauses = AddItemToCauseList(activeControlPanel, "AKICTContrastOption", possibleCauses);
    } else if (toggleState > 0) {
        excludedCauses = AddItemToCauseList(activeControlPanel, "AKICTContrastOption", excludedCauses);
    }
    toggleState = MedNote_GetCPOptionToggleState("AKISurgeryOption");
    if (toggleState == 0) {
        possibleCauses = AddItemToCauseList(activeControlPanel, "AKISurgeryOption", possibleCauses);
    } else if (toggleState > 0) {
        excludedCauses = AddItemToCauseList(activeControlPanel, "AKISurgeryOption", excludedCauses);
    }
    toggleState = MedNote_GetCPOptionToggleState("AKIAbdomCompartmentOption");
    if (toggleState == 0) {
        possibleCauses = AddItemToCauseList(activeControlPanel, "AKIAbdomCompartmentOption", possibleCauses);
    } else if (toggleState > 0) {
        excludedCauses = AddItemToCauseList(activeControlPanel, "AKIAbdomCompartmentOption", excludedCauses);
    }
    toggleState = MedNote_GetCPOptionToggleState("AKIHRS1Option");
    if (toggleState == 0) {
        possibleCauses = AddItemToCauseList(activeControlPanel, "AKIHRS1Option", possibleCauses);
    } else if (toggleState > 0) {
        excludedCauses = AddItemToCauseList(activeControlPanel, "AKIHRS1Option", excludedCauses);
    }
    toggleState = MedNote_GetCPOptionToggleState("AKIHRS2Option");
    if (toggleState == 0) {
        possibleCauses = AddItemToCauseList(activeControlPanel, "AKIHRS2Option", possibleCauses);
    } else if (toggleState > 0) {
        excludedCauses = AddItemToCauseList(activeControlPanel, "AKIHRS2Option", excludedCauses);
    }
    if (excludedCauses != "") {
        WriteComment("Excluded causes include: " + excludedCauses);
    }
    if (possibleCauses != "") {
        WriteComment("Possible causes include: " + possibleCauses);
    }


    //////////////////////////////////
    // Workup
    var optionNameList = [ 'AKICPKOption'];
    WriteListOfSelectedActions(activeControlPanel, "Check ", optionNameList)

    var optionNameList = [ 'AKIUrinalysisOption', 'AKILytesOption'];
    WriteListOfSelectedActions(activeControlPanel, "Check ", optionNameList)

    var optionNameList = [ 'AKIBNPOption', 'AKICXROption'];
    WriteListOfSelectedActions(activeControlPanel, "Workup Cardiorenal and check ", optionNameList)

    WriteActionIfSelected(activeControlPanel, 'AKIBladderPressureOption');
    WriteActionIfSelected(activeControlPanel, 'AKIRenalUltrasoundOption');
    WriteActionIfSelected(activeControlPanel, 'AKIDopplersOption');


    //////////////////////////////////
    // Treat
    WriteActionIfSelected(activeControlPanel, 'AKIFluidBolusOption');
    WriteActionIfSelected(activeControlPanel, 'AKIMaintFluidOption');

    // HRS
    WriteActionIfSelected(activeControlPanel, 'AKIHRSAlbuminOption');
    WriteActionIfSelected(activeControlPanel, 'AKIHRSMidodrineOption');
    WriteActionIfSelected(activeControlPanel, 'AKIHRSOctreotideOption');

    WriteActionIfSelected(activeControlPanel, 'AKITreatUTIOption');
    WriteActionIfSelected(activeControlPanel, 'AKIDiureseOption');
    WriteActionIfSelected(activeControlPanel, 'AKITreatBladderScanOption');
    WriteActionIfSelected(activeControlPanel, 'AKITreatFoleyOption');
    WriteActionIfSelected(activeControlPanel, 'AKITreatTamsulosinOption');
    WriteActionIfSelected(activeControlPanel, 'AKIHoldDiureticsOption');
    WriteActionIfSelected(activeControlPanel, 'AKIHoldACEARBOption');
    WriteActionIfSelected(activeControlPanel, 'AKIHoldNSAIDsOption');
    var actionNameList = [ "AKITitratePipTazoOption", "AKIConvertOpioidsOption", 
                            "AKITitrateGabapentinOption", "AKITitrateColchicineOption"];
    WriteListOfSubActions("Titrate Medications for current estimated eGFR", actionNameList);

    // Recovery
    planStr = MedNote_GetCPOptionValue("AKIRecoveryFluidsOption");
    if ((planStr != null) && (planStr != "")) {
        WriteComment("This is likely a post-ATN diuresis (while injured, the kidney lost salt gradient in the interstitium and so now cannot reabsorb water effectively until this gradient is restored over the next few days).");
        WriteAction(planStr);
    }

//WriteComment("BUN = xxxx. The elevated BUN may be due to steroids (they stimulate protein catabolism, resulting in increased waste Nitrogen in the form of urea)");
//WriteComment("There is no indication for renal replacement therapy today. Specifically, the patient is not severely volume overloaded, and is oxygenating well. There are no significant electrolyte abnormalities, or acid-base abnormalities that cannot be medically managed and there are no clinical signs of uremia (no pericardial rub or encephalopathy).");
} // PrintAKIPlan







////////////////////////////////////////////////////////////////////////////////
//
// [WriteChestPainPlan]
//
// Last Updated 7/27-28/2020
////////////////////////////////////////////////////////////////////////////////
function 
WriteChestPainPlan() {
    //LogEvent("WriteChestPainPlan")
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Chest Pain";
    modifierStr = MedNote_GetCPOptionValue("NSTEMITitleOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr;
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "NSTEMIPlan");
    if (!activeControlPanel) {
        LogEvent("WriteChestPainPlan. activeControlPanel is null");
        return;
    }

    planStr = MedNote_GetCPOptionValue("NSTEMICADOption");
    if ((planStr != null) && (planStr != "")) {
        MedNote_AddRelatedProblem(planStr);
    }

    ///////////////////
    // Symptoms
    var optionNameList = ["NSTEMISubSternalOption", "NSTEMIExertionOption", "NSTEMIRestOption"];
    var numPainQualities = CountSelectedValues(activeControlPanel, optionNameList);
    var painType = "non-cardiac";
    if (numPainQualities == 3) {
        painType = "typical angina";
    } else if (numPainQualities == 2) {
        painType = "atypical angina";
    }
    planstring = "The pain is " + painType + ", with ";
    WriteListOfSelectedValues(activeControlPanel, planstring, true, " properties: ", optionNameList, "");

    ///////////////////
    // Results
    var optionNameList = ["NSTEMITropOption", "NSTEMITropDeltaOption"];
    WriteListOfSelectedValues(activeControlPanel, "", false, "", optionNameList, "");
    WriteCommentIfSelected(activeControlPanel, 'NSTEMIEKGOption');
    WriteCommentIfSelected(activeControlPanel, 'NSTEMITypeOption');

    ///////////////////
    // Risks
    var optionNameList = [ "NSTEMIRiskDiabetesOption", "NSTEMIRiskHypertensionOption", "NSTEMIRiskTobaccoOption", 
                            "NSTEMIRiskHighLDLOption", "NSTEMIRiskLowLDLOption", "NSTEMIRiskMaleOver65Option"];
    WriteListOfSelectedValues(activeControlPanel, "The patient has ", true, " TIMI cardiovascular risk factors: ", optionNameList, "");

    var optionNameList = [ "NSTEMIRiskDiabetesOption", "NSTEMIRiskHypertensionOption", "NSTEMIRiskTobaccoOption", 
                            "NSTEMIRiskLowLDLOption", "NSTEMIRiskObesityOption", "NSTEMIRiskFamilyHistoryOption", "NSTEMIRiskVascularDiseaseOption"];
    WriteListOfSelectedValues(activeControlPanel, "The patient has ", true, " HEART cardiovascular risk factors: ", optionNameList, "");

    ///////////////////
    // HEART and TIMI
    var optionNameList = [ "NSTEMIHEARTHistoryOption", "NSTEMIHEARTEKGOption", "NSTEMIHEARTAGEOption", 
                            "NSTEMIHEARTRiskOption", "NSTEMIHEARTTroponinsOption"];
    MedNote_WriteScoreFromSelectedValues(activeControlPanel, "The HEART score is ", " with: ", optionNameList, "");

    var optionNameList = [ "NSTEMITIMITroponinsOption", "NSTEMITIMIEKGChangesOption", "NSTEMITIMI3RiskFactorsOption", 
                            "NSTEMITIMIOver65yoOption", "NSTEMITIMIKnownCADOption", "NSTEMITIMIOnAspirinOption", 
                            "NSTEMITIMI2Episodes24hrsOption"];
    WriteListOfSelectedValues(activeControlPanel, "The TIMI score is ", true, " with: ", optionNameList, "");

    ///////////////////
    // Eval
    var optionNameList = [ "NSTEMICheckEKGOption", "NSTEMICheckTroponinsOption", "NSTEMIAMEKGOption", 
                            "NSTEMIUDSOption", "NSTEMIGetLipidOption", "NSTEMIGetA1cOption"];
    WriteListOfSelectedActions(activeControlPanel, "Check ", optionNameList)

    ///////////////////
    // Management
    WriteActionIfSelected(activeControlPanel, "NSTEMIStatinOption");
    WriteActionIfSelected(activeControlPanel, "NSTEMIMetoprololTarOption");
    WriteActionIfSelected(activeControlPanel, "NSTEMIMetoprololSuccOption");
    WriteActionIfSelected(activeControlPanel, "NSTEMICarvedilolOption");

    ///////////////////
    // ACE/ARB
    WriteActionIfSelected(activeControlPanel, "NSTEMILisinoprilOption");
    WriteActionIfSelected(activeControlPanel, "NSTEMILosartanOption");
    WriteActionIfSelected(activeControlPanel, "NSTEMISpironiolactoneOption");

    ///////////////////
    // Antiplatelet
    WriteActionIfSelected(activeControlPanel, "NSTEMIAsaOption");
    WriteActionIfSelected(activeControlPanel, "NSTEMITicagrelorOption");
    WriteActionIfSelected(activeControlPanel, "NSTEMIPlavixOption");

    ///////////////////
    // Anticoag
    WriteActionIfSelected(activeControlPanel, "NSTEMIHeparinDripOption");
    WriteActionIfSelected(activeControlPanel, "NSTEMILovenoxOption");

    ///////////////////
    // Workup
    WriteActionIfSelected(activeControlPanel, "NSTEMIGetEchoOption");
    WriteActionIfSelected(activeControlPanel, "NSTEMICheckICDOption");

    ///////////////////
    // Other
    WriteActionIfSelected(activeControlPanel, "NSTEMIStressTestOption");
    WriteActionIfSelected(activeControlPanel, "NSTEMITeleOption");
    WriteActionIfSelected(activeControlPanel, "NSTEMIHoldNSAIDsOption");
    WriteActionIfSelected(activeControlPanel, "NSTEMIHTNControlOption");
} // WriteChestPainPlan







////////////////////////////////////////////////////////////////////////////////
//
// [WriteHyponatremiaPlan]
//
// Updated 2020-7-30
// Updated 2022-10-30
// 2023-11-14 - Combined workup labs into a single task
////////////////////////////////////////////////////////////////////////////////
function 
WriteHyponatremiaPlan() {
    var planStr = "";
    var modifierStr = "";
    var activeControlPanel = null;
    var adjustedNa = -1;
    var electrolyteFreeWaterClearancePercent = -1;
    var osmFreeWaterClearancePercent = -1
    var estimatedFreeWaterClearancePercent = -1

    ///////////////////
    // Start the plan section
    planStr = MedNote_GetCPOptionValue("HypONaPseudoModifierOption");
    if ((planStr == null) || (planStr == "")) {
        planStr = "Hyponatremia";
        modifierStr = MedNote_GetCPOptionValue("HypONaVolumeModifierOption");
        if ((modifierStr != null) && (modifierStr != "")) {
            planStr = modifierStr;
        }
    }
    if (PrintSingleLinePlanAtEnd('HyponatremiaPlan', planStr, "Monitor and fluid restriction")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "HyponatremiaPlan");
    if (!activeControlPanel) {
        LogEvent("WriteHyponatremiaPlan. activeControlPanel is null");
        return;
    }

    planStr = MedNote_GetCPOptionValue("HypONaSIADHModifierOption");
    if ((planStr != null) && (planStr != "")) {
        MedNote_AddRelatedProblem(planStr);
    }

    ///////////////////
    // Read Inputs and do Calculations
    var currentNa = GetIntInputForControlPanel(activeControlPanel, 'InputNa_CP');
    var currentGlc = GetIntInputForControlPanel(activeControlPanel, 'InputGlucose_CP');
    var currentUOsm = GetIntInputForControlPanel(activeControlPanel, 'InputUrineOsm_CP');
    var currentUrineNa = GetIntInputForControlPanel(activeControlPanel, 'InputUrineNa_CP');
    var currentUrineK = GetIntInputForControlPanel(activeControlPanel, 'InputUrineK_CP');
    var currentSOsmStr = GetStrInputForControlPanel(activeControlPanel, 'InputSerumOsm_CP');
    var currentSOsm = -1;
    if (currentSOsmStr) {
        currentSOsm = parseInt(currentSOsmStr);
        if (isNaN(currentSOsm)) {
            currentSOsm = -1;
        }
    }

    // Adjust Na for Glucose
    if ((currentNa > 0) && (currentGlc > 0)) {
        adjustedNa = currentNa + (2.4 * ((currentGlc - 100) / 100));
        // Round off the fraction.
        adjustedNa = Math.round(adjustedNa);
        SetStrOutputForControlPanel(activeControlPanel, 'ResultAdjustedNa_CP', null, 'Adjusted Glc = ' + adjustedNa);
    }


    // Electrolyte-Free Water Clearance
    // See Minhtri K. Nguyen and Ira Kurtz, 
    // "Derivation of a new formula for calculating urinary electrolyte-free water clearance based on the Edelman equation"
    // Am J Physiol Renal Physiol 288: F1–F7, 2005;
    // http://ajprenal.physiology.org/content/ajprenal/288/1/F1.full.pdf
    if ((currentNa > 0) && (currentUrineNa > 0) && (currentUrineK > 0)) {
        var urineLyteConcentration = currentUrineNa + currentUrineK;
        var fractionOfUrineThatIsIsoOsmolar = urineLyteConcentration / currentNa;
        var fractionOfUrineThatIsIsPureWater = 1 - fractionOfUrineThatIsIsoOsmolar;
        electrolyteFreeWaterClearancePercent = fractionOfUrineThatIsIsPureWater * 100;
        // Round to an integer
        electrolyteFreeWaterClearancePercent = Math.round(electrolyteFreeWaterClearancePercent);
        estimatedFreeWaterClearancePercent = electrolyteFreeWaterClearancePercent;
    }
    if ((estimatedFreeWaterClearancePercent < 0) && (currentUOsm > 0) && (currentSOsm > 0)) {
        var fractionOfUrineThatIsIsoOsmolar = currentUOsm / currentSOsm;
        var fractionOfUrineThatIsIsPureWater = 1 - fractionOfUrineThatIsIsoOsmolar;
        osmFreeWaterClearancePercent = fractionOfUrineThatIsIsPureWater * 100;
        // Round to an integer
        osmFreeWaterClearancePercent = Math.round(osmFreeWaterClearancePercent);
        estimatedFreeWaterClearancePercent = osmFreeWaterClearancePercent;
    }
    if (estimatedFreeWaterClearancePercent > 0) {
        // This is in liters, so round to the nearest 10th
        //var volumeOfUrineThatIsIsPureWater = fractionOfUrineThatIsIsPureWater * UrineVolume;
        //volumeOfUrineThatIsIsPureWater = Math.round((volumeOfUrineThatIsIsPureWater + 0.00001) * 10) / 10;
        SetStrOutputForControlPanel(activeControlPanel, 'ResultFreeWaterClearance_CP', null, 'Urine is ' + estimatedFreeWaterClearancePercent + '% free water');
    }



    ///////////////////
    // Labs and Current Status
    planStr = MedNote_GetCPOptionValue("HypONaShowCurrentNaOption");
    if ((planStr != null) && (planStr != "")) {
        if (currentNa > 0) {
            planStr += currentNa
        }
        WriteComment(planStr);
    }
    if (MedNote_GetCPOptionBool('HypONaShowAdjustedNaOption')) {
        var adjustedNaStr = 'xxxx';
        if (adjustedNa > 0) {
            adjustedNaStr = adjustedNa;
        }
        WriteComment("Adjusted Sodium=" + adjustedNaStr 
                + ", given Glc=" + GetStrInputForControlPanel(activeControlPanel, 'InputGlucose_CP') 
                + " (increase Na by 2.4 for each 100mmol Glc over 100)");  
    }
    WriteCommentIfSelected(activeControlPanel, 'HypONaNeuroSxOption');
    WriteCommentIfSelected(activeControlPanel, 'HypONaExplainOption');
    planStr = MedNote_GetCPOptionValue("HypONaShowSOsmOption");
    if ((planStr != null) && (planStr != "")) {
        if ((currentSOsmStr != null) && (currentSOsmStr != "")) {
            planStr += currentSOsmStr
        }
        WriteComment(planStr);
    }


    ///////////////////
    // ADH Status
    WriteCommentIfSelected(activeControlPanel, 'HypONaHighADHOption');
    planStr = MedNote_GetCPOptionValue("HypONaShowUOsmOption");
    if ((planStr != null) && (planStr != "")) {
        if (currentUOsm > 0) {
            planStr += currentUOsm
        }
        WriteComment(planStr);
    }
    WriteCommentIfSelected(activeControlPanel, 'HypONaExplainHighUOsmOption');
    planStr = MedNote_GetCPOptionValue("HypONaShowFreeWaterClearanceOption");
    if ((planStr != null) && (planStr != "")) {
        if (estimatedFreeWaterClearancePercent > 0) {
            planStr += estimatedFreeWaterClearancePercent + "% free water"
        } else {
            planStr += "xxxx % free water";
        }
        WriteComment(planStr);
    }
    WriteCommentIfSelected(activeControlPanel, 'HypONaExplainFreeWaterClearanceOption');


    ///////////////////
    // ADH Status
    WriteCommentIfSelected(activeControlPanel, 'HypONaAldoStatusOption');
    WriteCommentIfSelected(activeControlPanel, 'HypONaExplainAldoOption');
    var optionNameList = [ "HypONaResultofNaChallengeOption", "HypONaShowUNaOption", "HypONaShowUKOption", 
                        "HypONaShowUrateOption", "HypONaShowBicarbOption" ]; // HypONaShowPhysExamOption    
    WriteListOfSelectedValues(activeControlPanel, "Evidence of high Aldo levels include: ", false, "", optionNameList, "")

    ///////////////////
    // SIADH Triggers
    var optionNameList = [ "HypONaLungCancerOption", "HypONaPneumoniaOption", "HypONaSepticEmboliOption", "HypONaInterstitialOption" ];
    WriteListOfSelectedValues(activeControlPanel, "The patient has possible triggers for SIADH including: ", false, "", optionNameList, "")

    ///////////////////
    // SSRI Meds
    var optionNameList = [ "HypONaSSRIOption", "HypONaCiprofloxacinOption", "HypONaCyclophosphamideOption", "HypONaCisplatinOption", 
                            "HypONaImatinibOption", "HypONaMethotrexateOption", "HypONaVincristineOption", "HypONaHaloperidolOption", 
                            "HypONaTCAsOption" ];
    WriteListOfSelectedValues(activeControlPanel, "The patient is taking medications associated with SIADH including: ", false, "", optionNameList, "")

    ///////////////////
    // Malnutrition
    WriteCommentIfSelected(activeControlPanel, 'HypONaShowBUBOption');
    WriteCommentIfSelected(activeControlPanel, 'HypONaLowOsmOption');
    WriteCommentIfSelected(activeControlPanel, 'HypONaExplainLowOsmOption');

    ///////////////////
    // Causes
    var optionNameList = [ "HypONaCirrhosisOption", "HypONaVolumeDepletionOption", "HypONaHighIntakeOption", "HypONaSIADHOption", 
                            "HypONaHypoVolemiaOption", "HypONaHypotensionOption",  "HypONaOverDiuresisOption", 
                            "HypONaCHFOption", "HypONaMalnutritionOption", "HypONaAdrenalOption"];
    WriteListOfSelectedValues(activeControlPanel, "Possible causes of the hyponatremia include: ", false, "", optionNameList, "")

    ///////////////////
    // Target and  OverCorrect
    WriteCommentIfSelected(activeControlPanel, 'HypONaDilyTargetOption');

    ///////////////////
    // Workup
    WriteActionIfSelected(activeControlPanel, 'HypONaCheckNaQ6hOption');
    var optionNameList = [ 'HypONaCheckUOsmOption', 'HypONaCheckULytesOption', 'HypONaCheckTSHOption',
                            'HypONaCheckSOsmOption',  'HypONaCheckUrateOption', 'HypONaCheckLipidsOption',
                            'HypONaAMcortisolOption']; 
    WriteListOfSelectedActions(activeControlPanel, "Check ", optionNameList)

    ///////////////////
    // Treat
    WriteActionIfSelected(activeControlPanel, 'HypoNaBolusOption');
    WriteActionIfSelected(activeControlPanel, 'HypoNaMaintFluidOption');

    WriteActionIfSelected(activeControlPanel, 'HypONaFreeWaterRestrictionOption');
    WriteActionIfSelected(activeControlPanel, 'HypONaLasixOption');
    WriteActionIfSelected(activeControlPanel, 'HypONaStopThiazidesOption');
    WriteActionIfSelected(activeControlPanel, 'HypONaExplainLasixOption');
    WriteActionIfSelected(activeControlPanel, 'HypONaHTSOption');

    ///////////////////
    // Overcorrection
    WriteActionIfSelected(activeControlPanel, 'HypONaD5WOption');
    WriteActionIfSelected(activeControlPanel, 'HypONaDDAVPOption');

    WriteActionIfSelected(activeControlPanel, 'HypONaNeuroChecksOption');
    WriteActionIfSelected(activeControlPanel, 'HypONaSeizurePrecautionsOption');
} // WriteHyponatremiaPlan






////////////////////////////////////////////////////////////////////////////////
//
// [OLD_WritePreventionPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
OLD_WritePreventionPlan(patientAge, fIsMale) {    
    MedNote_StartNewPlanSection("Prevention", null);

    /////////////////////////////
    // Vaccinations
    WriteAction("Influenza vaccine: ");
    WriteAction("Pneumovax: ");
    WriteAction("Last Td/Tdap: ");
    WriteAction("Check A1c: ");

    /////////////////////////////
    // Colon Cancer
    if (patientAge < 0) {
        WriteAction("Colon Cancer Screening: Last Colonoscopy ");
    } else if ((patientAge > 0) && (patientAge >= 40) && (patientAge < 50)) {
        WriteAction("Colon Cancer Screening if 1st degree relative with colorectal cancer: Last Colonoscopy ");
    } else if ((patientAge > 0) && (patientAge > 50) && (patientAge < 75)) {
        WriteAction("Colon Cancer Screening with colonoscopy Q10yr: Last Colonoscopy ");
    } else if ((patientAge > 0) && (patientAge > 75)) {
        WriteAction("Colon Cancer Screening no longer required");
    }

    /////////////////////////////
    // Breast Cancer
    if (!fIsMale) {
        if (patientAge < 0) {
            WriteAction("Breast Cancer Screening mammogram Q2yr: Last Mammogram ");
        } else if ((patientAge > 0) && (patientAge > 50) && (patientAge < 75)) {
            WriteAction("Breast Cancer Screening mammogram Q2yr: Last Mammogram ");
        } else if ((patientAge > 0) && (patientAge > 75)) {
            WriteAction("Breast Cancer Screening no longer required");
        }
    } // Female

    /////////////////////////////
    // Prostate Cancer
    if ((fIsMale) && (patientAge > 0) && (patientAge >= 50) && (patientAge <= 75)) {
        WriteAction("Prostate cancer Screening PSA Q1yr: Patient declines annual PSA");
    }

    /////////////////////////////
    // Lung Cancer
    if ((patientAge > 0) && (patientAge >= 50) && (patientAge <= 75)) {
        WriteAction("Lung Cancer Screening with low power CT Q1yr if over 30 pack years");
    }

    /////////////////////////////
    // Cervical Cancer
    if (!fIsMale) {
        if (patientAge < 0) {
            WriteAction("Cervical Cancer Screening");
        } else if ((patientAge > 0) && (patientAge >= 21) && (patientAge < 30)) {
            WriteAction("Cervical Cancer Screening (Pap Q3yr): Last Pap ");
        } else if ((patientAge > 0) && (patientAge >= 30) && (patientAge <= 65)) {
            WriteAction("Cervical Cancer Screening (Pap Q3yr or Pap with HPV Q5ys): Last Pap ");
        } else if ((patientAge > 0) && (patientAge > 65)) {
            WriteAction("Cervical Cancer Screening no longer required");
        }
    } // Female

    /////////////////////////////
    // AAA
    if ((fIsMale) && (patientAge > 0) && (patientAge >= 65) && (patientAge <= 75)) {
        WriteAction("AAA Screening");
    }

    /////////////////////////////
    // Bone Density
    if ((!fIsMale) && (patientAge >= 65) && (patientAge <= 75)) {
        WriteAction("Bone density screening (DEXA Q2yr): Last DEXA ");
    } // Female

    /////////////////////////////
    // Lipids
    if (((fIsMale) && (patientAge >= 35))   ||    ((!fIsMale) && (patientAge >= 55))) {
        WriteAction("Lipid screening (FLP): Last lipid panel (LDL=, HDL=)");
        WriteAction("Check LDL-Direct");
    }

    /////////////////////////////
    // Geriatrics
    if ((patientAge >= 60)) {
        WriteAction("Zoster vaccine");
    }
    if ((patientAge >= 65)) {
        WriteAction("Fall Prevention: Last Vitamin D");
        WriteAction("Pneumovax");
    } // Geriatrics

    /////////////////////////////
    // Diabetics
    if (DiabetesPlanButtonState) {        
        WriteAction("Annual urine microalbumin/Cr ratio in diabetics to screen for CKD");
    }
} // WritePreventionPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WritePreventionPlan]
//
// Updated: 2020-11-22
////////////////////////////////////////////////////////////////////////////////
function 
WritePreventionPlan() { 
    var activeControlPanel = null;
    var planStr = "";

    planStr = "Prevention";
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "PreventionPlan");
    if (!activeControlPanel) {
        LogEvent("WritePreventionPlan. activeControlPanel is null");
        return;
    }

    WriteCommentIfSelected(activeControlPanel, "Prevention_Colonoscopy_Status_Option");
    WriteCommentIfSelected(activeControlPanel, "Prevention_Mammogram_Status_Option");
    WriteCommentIfSelected(activeControlPanel, "Prevention_ChestCT_Status_Option");
    WriteCommentIfSelected(activeControlPanel, "Prevention_LDL_Status_Option");
    WriteCommentIfSelected(activeControlPanel, "Prevention_Pap_Status_Option");

    var optionNameList = [ "Prevention_ColonRisks_Age_Option", "Prevention_ColonRisks_Family_History_Option", "Prevention_ColonRisks_Past_Adenoma_Option"];
    WriteListOfSelectedValues(activeControlPanel, "Risks for colon cancer include: ", false, "", optionNameList, "")

    var optionNameList = [ "Prevention_LungRisks_Age_Option", "Prevention_LungRisks_Smoking_Option", "Prevention_LungRisks_Smoked_Past_15yrs_Option" ];
    WriteListOfSelectedValues(activeControlPanel, "Risks for lung cancer include: ", false, "", optionNameList, "")

    var optionNameList = [ "Prevention_BreastRisks_Age_Option", "Prevention_BreastRisks_Family_Option" ];
    WriteListOfSelectedValues(activeControlPanel, "Risks for breast cancer include: ", false, "", optionNameList, "")

    // Lipids
    WriteActionIfSelected(activeControlPanel, "Prevention_Check_Lipids_Option");

    // Colon Cancer
    WriteActionIfSelected(activeControlPanel, "Prevention_Hemoccult_Option");
    WriteActionIfSelected(activeControlPanel, "Prevention_Colonoscopy_Option");

    // Breast Cancer
    WriteActionIfSelected(activeControlPanel, "Prevention_CheckBRCA_Option");
    WriteActionIfSelected(activeControlPanel, "Prevention_CheckMammogram_Option");

    // Lung Cancer
    WriteActionIfSelected(activeControlPanel, "Prevention_ChestCT_Option");

    // Cervical Cancer
    WriteActionIfSelected(activeControlPanel, "Prevention_Pap_Option");
} // WritePreventionPlan







////////////////////////////////////////////////////////////////////////////////
//
// [WriteWeaknessPlan]
//
// Updated: 2023-9-25
// Updated: 2022-4-4
// Updated: 2021-2-15
// Updated: 2020-5-30
// Updated: 2020-5-1
////////////////////////////////////////////////////////////////////////////////
function 
WriteWeaknessPlan() { 
    var activeControlPanel = null;
    var planStr = "";
    var fWrotePlan = false;
    

    // Find all of the possible plans
    planStr = "";
    var currentPlanStr = MedNote_GetCPOptionValue("WeaknessWeaknessOption");
    if ((currentPlanStr != null) && (currentPlanStr != "")) {
        planStr += currentPlanStr;
    }
    currentPlanStr = MedNote_GetCPOptionValue("WeaknessFallsOption");
    if ((currentPlanStr != null) && (currentPlanStr != "")) {
        if (planStr != "") {
           planStr += ", ";
        }
        planStr += currentPlanStr;
    }
    currentPlanStr = MedNote_GetCPOptionValue("WeaknessDebilityOption");
    if ((currentPlanStr != null) && (currentPlanStr != "")) {
        if (planStr != "") {
           planStr += ", ";
        }
        planStr += currentPlanStr;
    }
    currentPlanStr = MedNote_GetCPOptionValue("WeaknessReducedMobilityOption");
    if ((currentPlanStr != null) && (currentPlanStr != "")) {
        if (planStr != "") {
           planStr += ", ";
        }
        planStr += currentPlanStr;
    }
    currentPlanStr = MedNote_GetCPOptionValue("WeaknessMyopathyOption");
    if ((currentPlanStr != null) && (currentPlanStr != "")) {
        if (planStr != "") {
           planStr += ", ";
        }
        planStr += currentPlanStr;
    }
    if (planStr == "") {
       planStr = "Weakness";
    }

    if (PrintSingleLinePlanAtEnd('WeaknessPlan', planStr, "Physical and Occupational therapy")) {
        return
    }

    // Start the problem.
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "WeaknessPlan");
    if (!activeControlPanel) {
        LogEvent("WriteWeaknessPlan. activeControlPanel is null");
        return;
    }


    var optionNameList = [ "WeaknessFRAILScaleFatigueOption", "WeaknessFRAILScaleResistanceOption", 
                            "WeaknessFRAILScaleWalk100YdsOption", "WeaknessFRAILScaleChronicIllnessOption", 
                            "WeaknessFRAILScaleWtLossOption" ];
    numDeficits = ComputeScoreFromSelectedValues(activeControlPanel, optionNameList);
    frailComment = "FRAIL Score=";
    if (numDeficits == 0) {
        frailComment = frailComment + "0, No Frailty";
    } else if (numDeficits <= 2) {
        frailComment = frailComment + "1, Intermediate frailty";
    } else {
        frailComment = frailComment + "2, Frail";
    }
    frailComment = frailComment + ", (" + numDeficits + " deficits: ";
    WriteListOfSelectedValues(activeControlPanel, frailComment, false, "", optionNameList, ")");

    WriteCommentIfSelected(activeControlPanel, "WeaknessCFSScoreScaleOption");

    var optionNameList = [ "WeaknessEtiologyOrthostatic", "WeaknessEtiologyNeuropathy", "WeaknessEtiologyVision", "WeaknessEtiologyAMS", "WeaknessEtiologyMeds"];
    WriteListOfSelectedValues(activeControlPanel, "Possible causes include: ", false, "", optionNameList, "")


    // Workup
    var optionNameList = [ "WeaknessCheckHeadCTOption", "WeaknessCheckCTSpineOption", "WeaknessCheckOrthostaticsOption", 
                        "WeaknessCheckABIOption", "WeaknessCheckEKGOption"];
    WriteListOfSelectedActions(activeControlPanel, "Check imaging: ", optionNameList)

    var optionNameList = [ "WeaknessCheckKOption", "WeaknessCheckVitDOption", "WeaknessCheckB12Option", 
                        "WeaknessCheckThiamineOption", "WeaknessCheckCPKOption", "WeaknessCheckTSHOption"];
    WriteListOfSelectedActions(activeControlPanel, "Check serum levels: ", optionNameList)


    var optionNameList = [ "Weakness_HOLD_OPIOIDS_OPTION", "Weakness_HOLD_BENZOS_OPTION", "Weakness_HOLD_BETA_BLOCKERS_OPTION", "Weakness_HOLD_ANTIHISTAMINES_OPTION", "Weakness_HOLD_PROMETHAZINE_OPTION"];
    WriteListOfSelectedActions(activeControlPanel, "Hold home medications: ", optionNameList)

    WriteActionIfSelected(activeControlPanel, "WeaknessIVFluids");
    WriteActionIfSelected(activeControlPanel, "WeaknessCholecal");
    WriteActionIfSelected(activeControlPanel, "WeaknessThiamine");
    WriteActionIfSelected(activeControlPanel, "WeaknessPTOption");
    WriteActionIfSelected(activeControlPanel, "WeaknessPrecautionsOption");
    WriteActionIfSelected(activeControlPanel, "WeaknessUpInChairOption");
} // WriteWeaknessPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteMigrainePlan]
//
// Updated 2022-11-3
////////////////////////////////////////////////////////////////////////////////
function
WriteMigrainePlan() {
    if (PrintSingleLinePlanAtEnd('MigrainesPlan', "Migraines", "PRN Fiorocet")) {
        return
    }

    planNameStr = "Migraine Headaches";
    modifierStr = MedNote_GetCPOptionValue("MigraineAuraModifier");
    if ((modifierStr != null) && (modifierStr != "")) {
        planNameStr = planNameStr + " " + modifierStr;
    }

    // Start the problem.
    activeControlPanel = MedNote_StartNewPlanSection(planNameStr, "MigrainesPlan");
    if (!activeControlPanel) {
        LogEvent("WriteMigrainePlan. activeControlPanel is null");
        return;
    }

    WriteCommentIfSelected(activeControlPanel, "MigraineNumMonthOption");
    WriteCommentIfSelected(activeControlPanel, "MigraineDurationOption");

    var optionNameList = [ "MigraineUnilateralOption", "MigrainePulsatileOption" ];
    WriteListOfSelectedValues(activeControlPanel, "Headaches are ", false, "", optionNameList, "")

    var optionNameList = [ "MigraineNauseaOption", "MigrainePhotophobiaOption" ];
    WriteListOfSelectedValues(activeControlPanel, "Headaches are associated with ", false, "", optionNameList, "")

    // Home Regimen
    planStr = MedNote_GetCPOptionValue("MigraineHomeRegimenOption");
    if ((planStr != null) && (planStr != "")) {
        WriteComment("Home regimen: " + planStr);
    }

    WriteActionIfSelected(activeControlPanel, "MigraineBenadrylCompazineOption");
    WriteActionIfSelected(activeControlPanel, "MigraineSumatriptanOption");
    WriteActionIfSelected(activeControlPanel, "MigraineFiorocetOption");

    WriteActionIfSelected(activeControlPanel, "MigrainePropranololOption");
    WriteActionIfSelected(activeControlPanel, "MigraineMagnesiumOption");

    WriteActionIfSelected(activeControlPanel, "MigraineDiaryOption");

    var optionNameList = [ "MigraineEtOHOption", "MigraineNicotineOption", "MigraineCaffeineOption" ];
    WriteListOfSelectedValues(activeControlPanel, "Counseled to avoid ", false, "", optionNameList, "")
} // WriteMigrainePlan




////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_ComputeSOFAScore]
//
////////////////////////////////////////////////////////////////////////////////
function
MedNote_ComputeSOFAScore(activeControlPanel, currentSOFAOptionList, baselineSOFAOptionList, SOFAValueNameList, promptStr) {
    //LogEvent("==========================================\nMedNote_ComputeSOFAScore.");
    var index = 0;
    var fShowBaselineScore = 0;
    var fShowCurrentScore = 0;
    var totalDiffInScores = 0;
    var planStr;

    g_BASELINE_SOFA_SCORE = 0;
    g_CURRENT_SOFA_SCORE = 0;
    g_SOFA_DIFFERENNCES = "";

    //LogEvent("MedNote_ComputeSOFAScore. currentSOFAOptionList.length=" + currentSOFAOptionList.length);
    for (index = 0; index < currentSOFAOptionList.length; index++) {
        var currentValueOptionName = currentSOFAOptionList[index];
        var baselineValueOptionName = baselineSOFAOptionList[index];
        var valueName = SOFAValueNameList[index];
        //LogEvent("MedNote_ComputeSOFAScore. index=" + index);
        //LogEvent("MedNote_ComputeSOFAScore. currentValueOptionName=" + currentValueOptionName);
        //LogEvent("MedNote_ComputeSOFAScore. baselineValueOptionName=" + baselineValueOptionName);

        var currentSOFAIndex = MedNote_GetCPOptionToggleState(currentValueOptionName);
        if (currentSOFAIndex >= 0) {
            fShowCurrentScore = 1;
        }
        if (currentSOFAIndex < 0) {
            currentSOFAIndex = 0;
        }

        var baselineSOFAIndex = MedNote_GetCPOptionToggleState(baselineValueOptionName);
        if (baselineSOFAIndex >= 0) {
            fShowBaselineScore = 1;
        }
        if (baselineSOFAIndex < 0) {
            baselineSOFAIndex = 0;
        }
        //LogEvent("MedNote_ComputeSOFAScore. " + valueName + ": currentSOFAIndex=" + currentSOFAIndex);
        //LogEvent("MedNote_ComputeSOFAScore. " + valueName + ": baselineSOFAIndex=" + baselineSOFAIndex);

        g_CURRENT_SOFA_SCORE += currentSOFAIndex;
        g_BASELINE_SOFA_SCORE += baselineSOFAIndex;
        if (currentSOFAIndex > baselineSOFAIndex) {
            g_SOFA_DIFFERENNCES = g_SOFA_DIFFERENNCES + valueName + ", ";
        }
    } // for (index = 0; index < currentSOFAOptionList.length; index++)

    if (g_SOFA_DIFFERENNCES != "") {
        // Remove the last ", "
        g_SOFA_DIFFERENNCES = g_SOFA_DIFFERENNCES.substring(0, g_SOFA_DIFFERENNCES.length - 2);
    }
} // MedNote_ComputeSOFAScore
 




////////////////////////////////////////////////////////////////////////////////
//
// [ComputeEstGFR]
//
// This uses several formula:
//
// 1. MDRD
//    175 × SCr-1.154 × age-0.203 × (0.742 if female) × (1.212 if black)
//    Results are stored in g_GFR_MDRD
// See https://www.kidney.org/content/mdrd-study-equation
//
// 2. Cockroft-Gault
//    (140 – age) × (weight, kg) × (0.85 if female) / (72 × Cr)
//
// 3. CKD-EPI Cystatin C (2012)
//    133 × min(CysC/0.8, 1)-0.499 × max(CysC/0.8, 1)-1.328 x 0.996^age × (0.932 if female)
// See https://www.kidney.org/content/ckd-epi-cystatin-c-equation-2012
//
// 4. CKD EPI (2021)
//   eGFR = 142 x min(SCr/κ, 1)^α x max(SCr/κ, 1)^-1.209 x 0.9938^Age x 1.012 [if female] 
//   Where:
//      SCr (standardized serum creatinine) = mg/dL
//      kappa = 0.7 (females) or 0.9 (males)
//      alpha = -0.241 (females) or -0.302 (males)
// See: https://www.kidney.org/content/ckd-epi-creatinine-equation-2021
//
//5. CKD EPI Creatinine Systatin C (2021)
//  eGFR = 135 × min(SCr/kappa, 1)^alpha × max(SCr/kappa, 1)^-0.544 × min(Scys/0.8, 1)^-0.323
//              × max(Scys/0.8, 1)^-0.778 × 0.9961^age × 0.963 [if female]
//  Where:
//      kappa = 0.7 (females) or 0.9 (males)
//      alpha = -0.219 (females) or -0.144 (males)
// See: https://www.kidney.org/content/ckd-epi-creatinine-cystatin-equation-2021
//
//
// Updated 2022-9-20
// Updated 2021-7-12
////////////////////////////////////////////////////////////////////////////////
function
ComputeEstGFR(currrentCr, patientAge, cystatinC, weightInKg, fIsMale) {
    //LogEvent("ComputeEstGFR");
    //LogEvent("ComputeEstGFR currrentCr = " + currrentCr);
    //LogEvent("ComputeEstGFR patientAge = " + patientAge);
    //LogEvent("ComputeEstGFR cystatinC = " + cystatinC);
    //LogEvent("ComputeEstGFR weightInKg = " + weightInKg);
    //LogEvent("ComputeEstGFR fIsMale = " + fIsMale);
    var scaler;

    g_GFR_MDRD = 0;
    g_GFR_CockroftGault = 0;
    g_GFR_CKDEPI = 0;
    g_GFR_CKDEPI_CystatinC = 0;
    g_GFR_CKDEPI_Creatinine_CystatinC = 0;


    ////////////////////////////////////
    // MDRD
    if ((currrentCr > 0) && (patientAge > 0)) {
        g_GFR_MDRD = 175;

        scaler = Math.pow(currrentCr, -1.154);
        //LogEvent("ComputeEstGFR scaler = " + scaler);
        g_GFR_MDRD = g_GFR_MDRD * scaler;

        scaler = Math.pow(patientAge, -0.203);
        g_GFR_MDRD = g_GFR_MDRD * scaler;

        if (!fIsMale) {
            g_GFR_MDRD = g_GFR_MDRD * 0.742;
        }        
        g_GFR_MDRD = Math.round((g_GFR_MDRD + 0.00001) * 1) / 1;
        //LogEvent("ComputeEstGFR g_GFR_MDRD = " + g_GFR_MDRD);
    } // MDRD
    

    ////////////////////////////////////
    // Cockroft-Gault
    if ((patientAge > 0) && (weightInKg > 0) && (currrentCr > 0)) {
        g_GFR_CockroftGault = ((140 - patientAge) * weightInKg) / (72 * currrentCr);
        if (!fIsMale) {
            g_GFR_CockroftGault = g_GFR_CockroftGault * 0.85;
        }
        g_GFR_CockroftGault = Math.round((g_GFR_CockroftGault + 0.00001) * 1) / 1;
        //LogEvent("ComputeEstGFR g_GFR_CockroftGault = " + g_GFR_CockroftGault);
    } // Cockroft-Gault


    ////////////////////////////////////
    // CKD-EPI Cystatin C (2012)
    if ((cystatinC > 0) && (patientAge > 0)) {
        cystatinCRatio = cystatinC / 0.8;

        g_GFR_CKDEPI_CystatinC = 133;
        if (cystatinCRatio < 1) {
            g_GFR_CKDEPI_CystatinC = g_GFR_CKDEPI_CystatinC * Math.pow(cystatinCRatio, -0.499);
        } 
        if (cystatinCRatio > 1) {
            g_GFR_CKDEPI_CystatinC = g_GFR_CKDEPI_CystatinC * Math.pow(cystatinCRatio, -1.328);
        }
        g_GFR_CKDEPI_CystatinC = g_GFR_CKDEPI_CystatinC * Math.pow(0.996, patientAge);
        if (!fIsMale) {
            g_GFR_CKDEPI_CystatinC = g_GFR_CKDEPI_CystatinC * 0.932;
        }

        g_GFR_CKDEPI_CystatinC = Math.round((g_GFR_CKDEPI_CystatinC + 0.00001) * 1) / 1;
        //LogEvent("ComputeEstGFR g_GFR_CKDEPI_CystatinC = " + g_GFR_CKDEPI_CystatinC);
    } // CKD-EPI Cystatin C (2012)


    ////////////////////////////////////
    // CKD-EPI (2021)
    if ((currrentCr > 0) && (patientAge > 0)) {
        // Default to female
        var kappa = 0.7;
        var alpha = -0.241;
        if (fIsMale) {
            kappa = 0.9;
            alpha = -0.302;
        }

        var creatKappaRatio = currrentCr / kappa;

        g_GFR_CKDEPI = 142;
        if (creatKappaRatio < 1) {
            g_GFR_CKDEPI = g_GFR_CKDEPI * Math.pow(creatKappaRatio, alpha);
        }
        if (creatKappaRatio > 1) {
            g_GFR_CKDEPI = g_GFR_CKDEPI * Math.pow(creatKappaRatio, -1.209);
        }

        g_GFR_CKDEPI = g_GFR_CKDEPI * Math.pow(0.9938, patientAge);

        if (!fIsMale) {
            g_GFR_CKDEPI = g_GFR_CKDEPI * 1.018;
        }

        g_GFR_CKDEPI = Math.round((g_GFR_CKDEPI + 0.00001) * 1) / 1;
        //LogEvent("ComputeEstGFR g_GFR_CKDEPI = " + g_GFR_CKDEPI);
    } // // CKD-EPI (2021)


    ////////////////////////////////////
    // CKD-EPI Creatinine Cystatin C (2021)
    if ((currrentCr > 0) && (cystatinC > 0) && (patientAge > 0)) {
        // Default to female
        var kappa = 0.7;
        var alpha = -0.219;
        if (fIsMale) {
            kappa = 0.9;
            alpha = -0.144;
        }

        g_GFR_CKDEPI_Creatinine_CystatinC = 135;

        var creatKappaRatio = currrentCr / kappa;
        if (creatKappaRatio < 1) {
            g_GFR_CKDEPI_Creatinine_CystatinC = g_GFR_CKDEPI_Creatinine_CystatinC * Math.pow(creatKappaRatio, alpha);
        }
        if (creatKappaRatio > 1) {
            g_GFR_CKDEPI_Creatinine_CystatinC = g_GFR_CKDEPI_Creatinine_CystatinC * Math.pow(creatKappaRatio, -0.544);
        }

        cystatinCRatio = cystatinC / 0.8;
        if (cystatinCRatio < 1) {
            g_GFR_CKDEPI_Creatinine_CystatinC = g_GFR_CKDEPI_Creatinine_CystatinC * Math.pow(cystatinCRatio, -0.323);
        }
        if (cystatinCRatio > 1) {
            g_GFR_CKDEPI_Creatinine_CystatinC = g_GFR_CKDEPI_Creatinine_CystatinC * Math.pow(cystatinCRatio, -0.778);
        }

        g_GFR_CKDEPI_Creatinine_CystatinC = g_GFR_CKDEPI_Creatinine_CystatinC * Math.pow(0.9961, patientAge);

        if (!fIsMale) {
            g_GFR_CKDEPI_Creatinine_CystatinC = g_GFR_CKDEPI_Creatinine_CystatinC * 0.963;
        }

        g_GFR_CKDEPI_Creatinine_CystatinC = Math.round((g_GFR_CKDEPI_Creatinine_CystatinC + 0.00001) * 1) / 1;
        //LogEvent("ComputeEstGFR g_GFR_CKDEPI_Creatinine_CystatinC = " + g_GFR_CKDEPI_Creatinine_CystatinC);
    } // CKD-EPI Creatinine Cystatin C (2021)
} // ComputeEstGFR





////////////////////////////////////////////////////////////////////////////////
//
// [ComputeRiskOfESRD]
//
// Updated: 24-9-2022 - Fixed the equations. Factored out common code.
//
// There is an implementation in Javascript on a web page that is linked to by NKF.
// It is very readable (not compressed or obfuscated) Javascript:
//  https://kidneyfailurerisk.com/assets/js/kidney-app.js
//
// The research papers:
//    Tangri N, Stevens LA, Griffith J, et al. "A predictive model for progression of chronic kidney disease to kidney failure" JAMA. 2011;305(15)
//    Tangri N, Grams ME, Levey AS et al, "Multinational Assessment of Accuracy of Equations for Predicting Risk of Kidney Failure: A Meta-analysis", JAMA. 2016;315(2):1-11
//
// The actual equations are in the papers, buried in the "Supplementary Materials". Here is a link
// sources:
//  https://cdn.jamanetwork.com/ama/content_public/journal/jama/934847/joi150162supp1_prod.pdf?Expires=1667050261&Signature=nVrVdlFwcpHjlLqKDclQqdyvPfkVQPkgSirW7lK2socS0TAHp7KMF8W7-C2AFukAsZHuDTUx3FYTnK3uTRomGC~Fsrc4uGdyYBvXXZbnLaLNnz4CfxcfX9NAJxoDZ8NiOCN8aujALYvhFbKeYvy1P-KtsJUdMf2q-ReoPrMqUAITu2UM-gD0tPue0IzAnpHGLT0jMuCvALFaog1DDhvuXx7YB2ez-FMVZHO4JWSKme-SaFqA8EWSQiLNU5SkNcR42Cc-DGgQjeNwhotGWay-Hq7DFJSbNaRec45K5LfJRGASxPi6az-~Xz9AFNK-xXcm8-3x0yqzPTeuJi1lsQNmZA__&Key-Pair-Id=APKAIE5G5CRDK6RD3PGA
//
// Some handy websites for checking my implementation.
// https://qxmd.com/calculate/calculator_125/kidney-failure-risk-equation-8-variable
// http://kidneyfailurerisk.com/
// http://kidneyfailurerisk.com/assets/js/kidney-app.js
//
////////////////////////////////////////////////////////////////////////////////
function
ComputeRiskOfESRD(patientAge, isMale, estimatedGFR, urineAlbumin, urineCr, serumAlbumin, serumCa, serumBicarb, serumPhos) {
    //LogEvent("ComputeRiskOfESRD");
    var maleValue;
    var baselineChanceOfHealthy;
    var riskExponent;
    var chanceHealthy;
    var sumOfRiskTerms = 0;

    g_2YearESRDRisk = -1;
    g_5YearESRDRisk = -1;

    var urineAlbCrRatio = 0;
    if (urineCr > 0) {
        urineAlbCrRatio = urineAlbumin / urineCr; // mg/g
    }
    //LogEvent("ComputeRiskOfESRD. urineAlbCrRatio=" + urineAlbCrRatio);    
    var lnUrineAlbCrRatio = Math.log(urineAlbCrRatio);
        
    if (isMale) {
        maleValue = 1;
    } else {
        maleValue = 0; 
    }

    // Calculate the sum of risk terms.
    // NOTE! These are the *SAME* for the 2-year and 5-year formula. Only the base of the exponent is different
    // NOTE! I use the US version by default
    ////////////////////////////////////////////
    // Calculate the Two-year risk. There are several formulae:
    //
    // 4-Variable - North America - Two-year Risk.
    // 1 – 0.9751 ^ exp (-0.2201 × (age/10 – 7.036) + 0.2467 × (male – 0.5642) – 0.5567 × (eGFR/5 – 7.222) + 0.4510 × (logACR – 5.137))
    //
    // 4-Variable - Global - Two-year Risk
    // 1 – 0.9676 ^ exp (-0.2245 × (age/10 – 7.036) + 0.3212 × (male – 0.5642) – 0.4553 × (eGFR/5 – 7.222) + 0.4469 × (logACR – 5.137))
    //
    // 8-Variable - North America - Two-year Risk.
    // 1 – 0.9757 ^ exp (-0.1992 × (age/10 – 7.036) + 0.1602 × (male – 0.5642) – 0.4919 × (eGFR/5 – 7.222) 
    //                   + 0.3364 × (logACR – 5.137) – 0.3441 × (albumin – 3.997) + 0.2604 × (phosphorous – 3.916) 
    //                   – 0.07354 × (bicarbonate – 25.57) – 0.2228 × (calcium – 9.355))
    //
    // 8-Variable - Global Two-year Risk
    // 1 – 0.9629 ^ exp (-0.1848 × (age/10 – 7.036) + 0.2906 × (male – 0.5642) – 0.4156 × (eGFR/5 – 7.222) 
    //                   + 0.3480 × (logACR – 5.137) – 0.3569 × (albumin – 3.997) + 0.1582 × (phosphorous – 3.916)
    //                   – 0.01199 × (bicarbonate – 25.57) – 0.1581 × (calcium – 9.355))
    //
    ////////////////////////////////////////////
    // Calculate the Five-year risk. There are several formulae:
    //
    // Four-Variable - North America - Five-year Risk.
    // 1 – 0.8996 ^ exp (-0.2201 × (age/10 – 7.036) + 0.2467 × (male – 0.5642) – 0.5567 × (eGFR/5 – 7.222) + 0.4510 × (logACR – 5.137))
    //
    // Four-Variable - Global - Five-year Risk
    // 1 – 0.8762 ^ exp (-0.2245 × (age/10 – 7.036) + 0.3212 × (male – 0.5642) – 0.4553 × (eGFR/5 – 7.222) + 0.4469 × (logACR – 5.137))
    //
    // 8-Variable - North America - Five-year Risk.
    // 1 – 0.9096 ^ exp (-0.1992 × (age/10 – 7.036) + 0.1602 × (male – 0.5642) – 0.4919 × (eGFR/5 – 7.222)
    //                   + 0.3364 × (logACR – 5.137) – 0.3441 × (albumin – 3.997) + 0.2604 × (phosphorous – 3.916) 
    //                   – 0.07354 × (bicarbonate – 25.57) – 0.2228 × (calcium – 9.355))
    //
    // 8-Variable - Global Five-year Risk
    // 1 – 0.8636 ^ exp (-0.1848 × (age/10 – 7.036) + 0.2906 × (male – 0.5642) – 0.4156 × (eGFR/5 – 7.222) 
    //                   + 0.3480 × (logACR – 5.137) – 0.3569 × (albumin – 3.997) + 0.1582 × (phosphorous – 3.916) 
    //                   – 0.01199 × (bicarbonate – 25.57) – 0.1581 × (calcium – 9.355))
    //
    // If we have values for albumin, phosphorous, bicarbonate, and calcium then we can compute the 8-variable form.
    if ((serumAlbumin > 0) && (serumPhos > 0) && (serumBicarb > 0) && (serumCa > 0)) {
        sumOfRiskTerms = 0.0
        sumOfRiskTerms = AddTermToESRDRiskScore(sumOfRiskTerms, "Age", -0.1992, 7.036, patientAge / 10);
        sumOfRiskTerms = AddTermToESRDRiskScore(sumOfRiskTerms, "Sex", 0.1602, 0.5642, maleValue);
        sumOfRiskTerms = AddTermToESRDRiskScore(sumOfRiskTerms, "GFR", -0.4919, 7.222, estimatedGFR / 5);
        sumOfRiskTerms = AddTermToESRDRiskScore(sumOfRiskTerms, "Urine Albumin/Cr Ratio", 0.3364, 5.137, lnUrineAlbCrRatio);
        sumOfRiskTerms = AddTermToESRDRiskScore(sumOfRiskTerms, "Albumin", -0.3441, 3.997, serumAlbumin);
        sumOfRiskTerms = AddTermToESRDRiskScore(sumOfRiskTerms, "Phos", 0.2604, 3.916, serumPhos);
        sumOfRiskTerms = AddTermToESRDRiskScore(sumOfRiskTerms, "Bicarb", -0.07354, 25.57, serumBicarb);
        sumOfRiskTerms = AddTermToESRDRiskScore(sumOfRiskTerms, "Calcium", -0.2228, 9.355, serumCa);    
    } // Compute the Eight-variable form.
    else {
        sumOfRiskTerms = 0.0
        sumOfRiskTerms = AddTermToESRDRiskScore(sumOfRiskTerms, "Age", -0.2201, 7.036, patientAge / 10);
        sumOfRiskTerms = AddTermToESRDRiskScore(sumOfRiskTerms, "Sex", 0.2467, 0.5642, maleValue);
        sumOfRiskTerms = AddTermToESRDRiskScore(sumOfRiskTerms, "GFR", -0.5567, 7.222, estimatedGFR / 5);
        sumOfRiskTerms = AddTermToESRDRiskScore(sumOfRiskTerms, "Urine Albumin/Cr Ratio", 0.451, 5.137, lnUrineAlbCrRatio);
    } // Compute the Two-variable form
    // First get e**sum, which is the exponent we will use to compute the the chance of survival. 
    riskExponent = Math.exp(sumOfRiskTerms);



    // Calculate the Two-year risk. There are several formulae:
    if ((serumAlbumin > 0) && (serumPhos > 0) && (serumBicarb > 0) && (serumCa > 0)) {
        baselineChanceOfHealthy = 0.978;
    } else {
        baselineChanceOfHealthy = 0.975;
    } // Compute the Two-variable form

    // Now, compute the survival probability. This is the chance of NOT being ESRD. 
    chanceHealthy = Math.pow(baselineChanceOfHealthy, riskExponent);
    // The risk of ESRD is 100% - chance of avoiding ESRD
    g_2YearESRDRisk = (1.0 - chanceHealthy);
    // This will convert from a fraction to a interger-percent, and also round to 2-decimals
    g_2YearESRDRisk = Math.round(((g_2YearESRDRisk * 100.0) + Number.EPSILON) * 100) / 100;

    
    ////////////////////////////////////////////
    // Calculate the Five-year risk. There are several formulae:
    if ((serumAlbumin > 0) && (serumPhos > 0) && (serumBicarb > 0) && (serumCa > 0)) {
        baselineChanceOfHealthy = 0.9301;
    } else {
        baselineChanceOfHealthy = 0.924;
    } // Compute the Two-variable form

    // Now, compute the survival probability. This is the chance of NOT being ESRD. 
    chanceHealthy = Math.pow(baselineChanceOfHealthy, riskExponent);
    // The risk of ESRD is 100% - chance of avoiding ESRD
    g_5YearESRDRisk = (1.0 - chanceHealthy);
    // This will convert from a fraction to a interger-percent, and also round to 2-decimals
    g_5YearESRDRisk = Math.round(((g_5YearESRDRisk * 100.0) + Number.EPSILON) * 100) / 100;
} // ComputeRiskOfESRD





////////////////////////////////////////////////////////////////////////////////
//
// [AddTermToESRDRiskScore]
// Called by ComputeRiskOfESRD for computing ESRD risk.
////////////////////////////////////////////////////////////////////////////////
function
AddTermToESRDRiskScore(currentDelta, labelStr, coefficient, xOffset, xVal) {
    //LogEvent(labelStr + ": xVal=" + xVal + ", coefficient=" + coefficient + ", xBar=" + xBar);
    currentDelta = currentDelta + (coefficient * (xVal - xOffset));
    return(currentDelta);
} // AddTermToESRDRiskScore





////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_ComputeMELD]
//
// Latest UNOS Transplant guidelines.
// https://optn.transplant.hrsa.gov/media/1575/policynotice_20151101.pdf
//
// There may be better scores. See:
// Ming Jiang, Fei Liu, Wu-Jun Xiong, Lan Zhong, and Xi-Mei Chen
// "Comparison of four models for end-stage liver disease in evaluating the prognosis of cirrhosis"
// World J Gastroenterol. 2008 Nov 14; 14(42): 6546–6550.
// https://www.ncbi.nlm.nih.gov/pmc/articles/PMC2773344/
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_ComputeMELD(INR, sodium, creatinine, Tbili) {
    //LogEvent("MedNote_ComputeMELD INR = " + INR);
    //LogEvent("MedNote_ComputeMELD sodium = " + sodium);
    //LogEvent("MedNote_ComputeMELD creatinine = " + creatinine);
    //LogEvent("MedNote_ComputeMELD Tbili = " + Tbili);
    //LogEvent("MedNote_ComputeMELD log(10) = " + Math.log(10)); // Used to verify that log() is actually ln()

    if ((INR > 0) && (sodium > 0) && (creatinine > 0) && (Tbili > 0)) {
        // If bilirubin, Cr, or INR is <1.0, use 1.0.
        if (INR < 1.0) {
            INR = 1.0
        }
        if (creatinine < 1.0) {
            creatinine = 1.0
        }
        if (Tbili < 1.0) {
            Tbili = 1.0
        }

        // If on dialysis, or Cr >4.0, then use Cr = 4.0
        if (creatinine > 4.0) {
            creatinine = 4.0
        }
        if (sodium < 125) {
            sodium = 125
        }
        if (sodium > 137) {
            sodium = 137
        }

        //MELD(i) = 0.957 × ln(Cr) + 0.378 × ln(bilirubin) + 1.120 × ln(INR) + 0.643
        // Be careful, some formula will rearrange the parens, so add 6.43 rather than 10*0.643, 
        // but it is the same.
        var meldScore = (0.957 * Math.log(creatinine)) + (0.378 * Math.log(Tbili)) + (1.12 * Math.log(INR)) + 0.643;
        meldScore = 10 * meldScore

        //LogEvent("MedNote_ComputeMELD meldScore = " + meldScore);
        if (meldScore > 11.0) {
            // MELD = MELD(i) + 1.32*(137-Na) – [0.033*MELD(i)*(137-Na)]
            meldScore = meldScore + (1.32 * (137 - sodium)) - (0.033 * meldScore * (137 - sodium));
            //LogEvent("MedNote_ComputeMELD Na-meldScore = " + meldScore);
        }

        meldScore = Math.round(meldScore);
        //LogEvent("MedNote_ComputeMELD meldScore = " + meldScore);
        return(meldScore);
    }

    return(-1);
} // MedNote_ComputeMELD 





////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_ComputeChildPugh]
//
// Child-Pugh
//    ascitesScore = "none", "slight", "large"
//    encephalopathy = "none", "grade 1", "grade 2"
//
// François Durand, Dominique Valla
// Assessment of the prognosis of cirrhosis: Child–Pugh versus MELD
// Journal of hepatology April 2005 Volume 42, Issue 1, Supplement, Pages S100–S107
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_ComputeChildPugh(albumin, INR, Tbili, ascitesScore, encephalopathyScore) {
    if ((albumin > 0) && (Tbili > 0) && (INR > 0) && (ascitesScore != null) && (encephalopathyScore != null)) {
        ascitesScore = ascitesScore.toLowerCase(); 
        encephalopathyScore = encephalopathyScore.toLowerCase(); 

        var score = 0;
        
        if (Tbili < 2) {
            score += 1;
        } else if (Tbili <= 3) {
            score += 2;
        } else {
            score += 3;
        }

        if (albumin > 3.5) {
            score += 1;
        } else if (albumin >= 2.8) {
            score += 2;
        } else {
            score += 3;
        }
        
        if (INR < 1.7) {
            score += 1;
        } else if (INR <= 2.2) {
            score += 2;
        } else {
            score += 3;
        }

        if (ascitesScore == "none") {
            score += 1;
        } else if (ascitesScore == "slight") {
            score += 2;
        } else {
            score += 3;
        }

        if (encephalopathyScore == "none") {
            score += 1;
        } else if (encephalopathyScore == "grade 1") {
            score += 2;
        } else {
            score += 3;
        }

        score = Math.round(score);
        // HTML entities for percent character: &#37;
        var className = " (Class A, 1year survival 100%, 2year survival 80%)";
        if ((score >= 7) && (score <= 9)) {
            className = " (Class B, 1year survival 80%, 2year survival 60%)";
        } else if (score >= 10) {
            className = " (Class C, 1year survival 45%, 2year survival 35%)";
        }

        return(score + className);
    }

    return(null);
} // MedNote_ComputeChildPugh





////////////////////////////////////////////////////////////////////////////////
//
// [WriteVancomycinPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteVancomycinPlan(patientAge, weightInKg, eGFR, allowPharmacy, seriousInfection) { 
    var dose;
    var minDose;
    var maxDose;
    var targetDoseRoundDown;
    var targetDoseRoundUp;
    var pStr = "Vancomycin (cover gram positives including MRSA";
    var explanationStr = "";

    if ((weightInKg < 0) || (eGFR < 0) || (patientAge < 0)) {
        if (allowPharmacy) {
            pStr = pStr + ") - Pharmacy to dose";
        }
        WriteComment(pStr);
        return;
    }

    // Special case ESRD
    if (eGFR <= 30) {
        pStr = pStr + ", dose adjusted for CKD-V or ESRD since CrCl=" + eGFR + ") ";
         
        // The min dose is 15 mg/kg and the max dose is 20 mg/kg
        minDose = weightInKg * 15;
        maxDose = weightInKg * 20;

        // The target dose is in the middle, 17mg/kg
        dose = weightInKg * 17;
        
        var intDose = dose / 250;
        intDose = intDose.toFixed();

        // Now, round to the nearest 250
        targetDoseRoundDown = intDose * 250;
        targetDoseRoundUp = targetDoseRoundDown + 250;
        if ((targetDoseRoundUp - dose) < (dose - targetDoseRoundDown)) {
            dose = targetDoseRoundUp;
        } else {
            dose = targetDoseRoundDown;
        }

        pStr = pStr + dose + "mg (17mg/kg rounded to 250), repeat dose of " + dose + "mg when serum level below 20mg/dL";
        WriteComment(pStr);
        return;
    } // ESRD

    
    pStr = pStr + ") ";

    // Select the dose based on weight
    if (weightInKg >= 111) {
        pStr = pStr + "1750mg ";
    } else if ((weightInKg >= 90) && (weightInKg < 111)) {
        pStr = pStr + "1500mg";
    } else if ((weightInKg >= 75) && (weightInKg < 90)) {
        pStr = pStr + "1250mg";
    } else if ((weightInKg >= 60) && (weightInKg < 75)) {
        pStr = pStr + "1000mg";
    } else if ((weightInKg >= 50) && (weightInKg < 60)) {
        pStr = pStr + "750mg";
    } else { // if ((weightInKg <= 50)) {
        pStr = pStr + "500mg";
    }
    explanationStr = explanationStr + "TBW=" + weightInKg + "kg"

    // Select the frequency based on Cr Clearance
    // May do Q8h if < 50yo and CrCl>100 and severe infection
    if (eGFR >= 100) {
        if ((patientAge < 50) && (seriousInfection)) {
            pStr = pStr + " Q8h";
            explanationStr = explanationStr + ", age=" + patientAge + "yo";
        } else {
            pStr = pStr + " Q12h";
        }
    } else if ((eGFR >= 50) && (eGFR < 100)) {
        pStr = pStr + " Q12h";
    } else if ((eGFR >= 30) && (eGFR < 50)) {
        pStr = pStr + " Q24h";
    }


    explanationStr = explanationStr + ", CrCl=" + eGFR;  
    if (explanationStr != "") {
        pStr = pStr + " (" + explanationStr + ")";
    }
    WriteComment(pStr);
    

    if ((seriousInfection) && (weightInKg >= 30)) {
        pStr = "Start with one-time initial Vanc loading dose of ";
        
        // Select the dose based on weight
        if (weightInKg >= 90) {
            pStr = pStr + "3000mg over 6hrs";
        } else if ((weightInKg >= 75) && (weightInKg < 90)) {
            pStr = pStr + "2500mg over 5hrs";
        } else if ((weightInKg >= 60) && (weightInKg < 75)) {
            pStr = pStr + "2000mg over 4hrs";
        } else if ((weightInKg >= 50) && (weightInKg < 60)) {
            pStr = pStr + "1500mg over 3hrs";
        } else if ((weightInKg >= 30) && (weightInKg < 50)) {
            pStr = pStr + "1500mg over 2hrs";
        }
        
        WriteAction(pStr);
    } // if (seriousInfection)


    WriteAction("Check Vanc trough immediately before 4th dose");

    WriteAction("Doses of 15–20 mg/kg (as actual body weight) given every 8–12 hr");
    WriteComment("See Therapeutic monitoring of vancomycin in adult patients: A consensus review of the American Society of Health-System Pharmacists, the Infectious Diseases Society of America, and the Society of Infectious Diseases Pharmacists");
    WriteComment("The recommendations are summarized on page 3 of the report, which is labelled page 84 of the journal it appeared in");
    WriteComment("http://www.idsociety.org/uploadedFiles/IDSA/Guidelines-Patient_Care/PDF_Library/Vancomycin.pdf");
    WriteComment("Management of MRSA Infections in Adult Patients 2011 Clinical Practice Guidelines by the Infectious Diseases Society of America");
    WriteComment("http://www.idsociety.org/uploadedFiles/IDSA/Guidelines-Patient_Care/PDF_Library/MRSA%20slideset%2010%2012%2011%20Final.pdf");
    WriteComment("Clinical Practice Guidelines by the Infectious Diseases Society of America for the Treatment of Methicillin-Resistant Staphylococcus Aureus Infections in Adults and Children");
    WriteComment("http://www.idsociety.org/uploadedfiles/idsa/guidelines-patient_care/pdf_library/mrsa.pdf");
} // WriteVancomycinPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WritePipTazoPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WritePipTazoPlan(eGFR, allowPharmacy) { 
    var pStr = "Pip/Tazo (cover gram negatives and anaerobes)";
        
    if ((eGFR > 0) && (eGFR <= 15)) {
        pStr = pStr + " 2.25g IV  Q8h (dose adjusted for CrCl=" + eGFR + ")";
    } else if ((eGFR > 15) && (eGFR <= 50)) {
        pStr = pStr + " 3.375g IV Q8h (dose adjusted for CrCl=" + eGFR + ")";
    } else {
        pStr = pStr + " 3.375g IV Q6h";
    }

    WriteAction(pStr);
} // WritePipTazoPlan






////////////////////////////////////////////////////////////////////////////////
//
// [WriteBillingPlan]
//
// HPI Billing buttons
// ==============================
// ROS: 10 systems
// Physical: 2-3 items in 8+ systems
//
// MDM - Need 2 of three:
// 1. Complexity - 1 or more problems with:
//   1 button: "Acute Severe exacerbation of" or "Severe Progression of "
// 2. Data - 2 of 3
//   Button: "Data Review" - ideally 3 labs
//   Button: "Personal review of EKG or CXR"
//   Button: "Discussion of management or Interpretation of results with consultant"
// 3. Risk
//   Button: "Monitor for renal toxicity from Vanc"/"Parenteral controlled substances"
//
// Subsequent Note
// ==============================
// ROS: 2 systems
// Physical: 2 items in 8+ systems
//
// 1. Complexity 1 or more problems:
//   1 button: "Acute Severe exacerbation of" or "Severe Progression of "
//
//
//
// Created 8/16/2023
// Updated 8/29/2023
////////////////////////////////////////////////////////////////////////////////
function 
WriteBillingPlan() {
    var newLineStr = "\n";
    var indentStr = "    ";
    var currentStr = null;
    var complexityStr = "";
    var data1Str = "";
    var data2Str = "";
    var data3Str = "";
    var riskStr = "";
    var totalStr = "";
    var numComplexity = 0;
    var numData1 = 0;
    var numData2 = 0;
    var numData3 = 0;
    var numRisk = 0;
    var numTotalData = 0;
    var numTotalScore = 0;


    activeControlPanel = MedNote_StartNewPlanSection(null, "BillingPlan");
    if (!activeControlPanel) {
        LogEvent("WriteBillingPlan. activeControlPanel is null");
        return;
    }

    ///////////////////////
    // Complexity
    currentStr = MedNote_GetCPOptionValue("BILLING_COMPLEXITY_EXACERBATION");
    if ((currentStr != null) && (currentStr != "")) {
        complexityStr += currentStr;
        numComplexity = 1;
    }
    currentStr = MedNote_GetCPOptionValue("BILLING_COMPLEXITY_PROGRESSION");
    if ((currentStr != null) && (currentStr != "")) {
        if ((complexityStr != null) && (complexityStr != "")) {
            complexityStr += ", ";
        }
        complexityStr += currentStr;
        numComplexity = 1;
    }

    ///////////////////////
    // Data 1
    currentStr = MedNote_GetCPOptionValue("BILLING_DATA_INFLAMM_LABS");
    if ((currentStr != null) && (currentStr != "")) {
        if ((data1Str != null) && (data1Str != "")) {
            data1Str += ", ";
        }
        data1Str += currentStr;
        numData1 = 1;
    }
    currentStr = MedNote_GetCPOptionValue("BILLING_DATA_RENAL_LABS");
    if ((currentStr != null) && (currentStr != "")) {
        if ((data1Str != null) && (data1Str != "")) {
            data1Str += ", ";
        }
        data1Str += currentStr;
        numData1 = 1;
    }
    currentStr = MedNote_GetCPOptionValue("BILLING_DATA_LYTES_LABS");
    if ((currentStr != null) && (currentStr != "")) {
        if ((data1Str != null) && (data1Str != "")) {
            data1Str += ", ";
        }
        data1Str += currentStr;
        numData1 = 1;
    }
    currentStr = MedNote_GetCPOptionValue("BILLING_DATA_FAMILY");
    if ((currentStr != null) && (currentStr != "")) {
        if ((data1Str != null) && (data1Str != "")) {
            data1Str += ", ";
        }
        data1Str += currentStr;
        numData1 = 1;
    }  


    ///////////////////////
    // Data 2
    currentStr = MedNote_GetCPOptionValue("BILLING_DATA_PERSONAL_EKG");
    if ((currentStr != null) && (currentStr != "")) {
        if ((data2Str != null) && (data2Str != "")) {
            data2Str += ", ";
        }
        data2Str += currentStr;
        numData2 = 1;
    }
    currentStr = MedNote_GetCPOptionValue("BILLING_DATA_PERSONAL_CXR");
    if ((currentStr != null) && (currentStr != "")) {
        if ((data2Str != null) && (data2Str != "")) {
            data2Str += ", ";
        }
        data2Str += currentStr;
        numData2 = 1;
    }
    currentStr = MedNote_GetCPOptionValue("BILLING_DATA_PERSONAL_CT");
    if ((currentStr != null) && (currentStr != "")) {
        if ((data2Str != null) && (data2Str != "")) {
            data2Str += ", ";
        }
        data2Str += currentStr;
        numData2 = 1;
    }

    ///////////////////////
    // Data 3
    currentStr = MedNote_GetCPOptionValue("BILLING_DATA_DISCUSS");
    if ((currentStr != null) && (currentStr != "")) {
        if ((data3Str != null) && (data3Str != "")) {
            data3Str += ", ";
        }
        data3Str += currentStr;
        numData3 = 1;
    }


    ///////////////////////
    // Risk
    currentStr = MedNote_GetCPOptionValue("BILLING_RISK_TOXICITY");
    if ((currentStr != null) && (currentStr != "")) {
        if ((riskStr != null) && (riskStr != "")) {
            riskStr += ", ";
        }
        riskStr += currentStr;
        numRisk = 1;
    }
    currentStr = MedNote_GetCPOptionValue("BILLING_RISK_AKI");
    if ((currentStr != null) && (currentStr != "")) {
        if ((riskStr != null) && (riskStr != "")) {
            riskStr += ", ";
        }
        riskStr += currentStr;
        numRisk = 1;
    }
    currentStr = MedNote_GetCPOptionValue("BILLING_RISK_BLEEDING");
    if ((currentStr != null) && (currentStr != "")) {
        if ((riskStr != null) && (riskStr != "")) {
            riskStr += ", ";
        }
        riskStr += currentStr;
        numRisk = 1;
    }
    currentStr = MedNote_GetCPOptionValue("BILLING_RISK_IMMUNOSUPPRESSED");
    if ((currentStr != null) && (currentStr != "")) {
        if ((riskStr != null) && (riskStr != "")) {
            riskStr += ", ";
        }
        riskStr += currentStr;
        numRisk = 1;
    }

    currentStr = MedNote_GetCPOptionValue("BILLING_RISK_OPIOIDS");
    if ((currentStr != null) && (currentStr != "")) {
        if ((riskStr != null) && (riskStr != "")) {
            riskStr += ", ";
        }
        riskStr += currentStr;
        numRisk = 1;
    }
    currentStr = MedNote_GetCPOptionValue("BILLING_RISK_ESCALATION");
    if ((currentStr != null) && (currentStr != "")) {
        if ((riskStr != null) && (riskStr != "")) {
            riskStr += ", ";
        }
        riskStr += currentStr;
        numRisk = 1;
    }
    currentStr = MedNote_GetCPOptionValue("BILLING_RISK_DNR");
    if ((currentStr != null) && (currentStr != "")) {
        if ((riskStr != null) && (riskStr != "")) {
            riskStr += ", ";
        }
        riskStr += currentStr;
        numRisk = 1;
    }


    /////////////////////////
    // Print
    if (((complexityStr != null) && (complexityStr != ""))
            || ((data1Str != null) && (data1Str != ""))
            || ((data2Str != null) && (data2Str != ""))
            || ((data3Str != null) && (data3Str != ""))
            || ((riskStr != null) && (riskStr != ""))) {
        WriteComment("Patient care included the following components:");
    }
    if ((complexityStr != null) && (complexityStr != "")) {
        complexityStr = "Complexity: " + complexityStr;
        WriteIndentedTextLine(complexityStr);
    }
    if ((data1Str != null) && (data1Str != "")) {
        data1Str = "Data: Review of at least three lab results: " + data1Str;
        WriteIndentedTextLine(data1Str)
    }
    if ((data2Str != null) && (data2Str != "")) {
        data2Str = "Data: Personal interpretation of: " + data2Str;
        WriteIndentedTextLine(data2Str);
    }
    if ((data3Str != null) && (data3Str != "")) {
        data3Str = "Data: " + data3Str;
        WriteIndentedTextLine(data3Str);
    }
    if ((riskStr != null) && (riskStr != "")) {
        riskStr = "Risk: " + riskStr;
        WriteIndentedTextLine(riskStr);
    }


    numTotalData = numData1 + numData2 + numData3;
    if (numTotalData >= 2) {
        numTotalData = 1;
    } else {
        numTotalData = 0;
    }
    numTotalScore = numComplexity + numRisk + numTotalData;
    if (numTotalScore >= 2) {
        SetStrOutputForControlPanel(activeControlPanel, 'ResultBillingLevel_CP', null, 'This is a level 3 subsequent visit for hospital inpatient care');
    } else {
        SetStrOutputForControlPanel(activeControlPanel, 'ResultBillingLevel_CP', null, 'This is a level 2 subsequent visit for hospital inpatient care');
    }

    WriteCommentIfSelected(activeControlPanel, "BILLING_REFERENCES_AMA");



    //////////////////////////////////////////////////////////////
    // Critical Care
    var critCareStr = MedNote_GetCPOptionValue("BILLING_COMPLEXITY_CRITCARE_GENERAL");
    if ((null != critCareStr) && ("" != critCareStr)) {
        WriteComment("  ");
        WriteComment("Critical Care:");
        WriteComment(critCareStr);
    }

    var optionNameList = [ "BILLING_COMPLEXITY_CRITCARE_HISTORY", "BILLING_COMPLEXITY_CRITCARE_EXAM", "BILLING_COMPLEXITY_CRITCARE_PLAN", "BILLING_COMPLEXITY_CRITCARE_CONSULTANTS", "BILLING_COMPLEXITY_CRITCARE_RESPONSE", "BILLING_COMPLEXITY_CRITCARE_ORDERS", "BILLING_COMPLEXITY_CRITCARE_ORDER_LABS", "BILLING_COMPLEXITY_CRITCARE_CT", "BILLING_COMPLEXITY_CRITCARE_CXR", "BILLING_COMPLEXITY_CRITCARE_PULSEOX", "BILLING_COMPLEXITY_CRITCARE_ABG", "BILLING_COMPLEXITY_CRITCARE_IV" ];
        WriteComment("  ");
    WriteListOfSelectedValues(activeControlPanel, "Critical care was time spent personally by me on the following activities: ", false, "", optionNameList, ")")

    timeStr = MedNote_GetCPOptionValue("BILLING_COMPLEXITY_CRITCARE_TIME_SPENT");
    if ((null != timeStr) && ("" != timeStr)) {
        timeStr = "Total time spent by the provider providing critical care services was " + timeStr;
        WriteComment("  ");
        WriteComment(timeStr);
    }
} // WriteBillingPlan




    
