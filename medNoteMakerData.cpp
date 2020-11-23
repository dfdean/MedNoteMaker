////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2013-2017 Dawson Dean
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
// MedNote_InitQuantState()
// MedNote_InitOneQuantValueField(valueNameStr)
// MedNote_SetValueNumber(valueNameStr, intVal) 
// MedNote_SetValueString(valueNameStr, strVal)
//
// MedNote_CalculateAllValues()
//
// MedNote_ImportCPRSLabs(lineArray)
//
// ComputeRiskOfESRD()
// AddTermToESRDRiskScore(labelStr, coefficient, xBar, xVal)
// SaveValueFromOneString(lineArray, lineNum, valueNameStr, str, startIndex)
// ReadNumberFromStr(str, startIndex)
// ParseOneCPRSLine(lineArray, lineNum)
// GetLabValue(valueNameStr)
// GetLabValueStringForPlan(valueNameStr)
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////
// Private Temporary Globals
// Globals, these just allow ComputeRiskOfESRD() to return two separate values.
var g_2YearESRDRisk = -1;
var g_5YearESRDRisk = -1;
var g_SumofBetaXBar = 0;
var g_SumofBetaX = 0;
var g_TotalDelta = 0;

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





/////////////////////////
// Laboratory Values and Derived Scores
var g_AllLabValuesDeclaration = {
    //////////////////
    // BMP
    "Sodium" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputNa"},
    "Potassium" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputK"},
    "Chloride" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputCl"},
    "HCO3" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputHCO3"},
    "BUN" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputBUN"},
    "Creatinine" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputCr"},
    "Glucose" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputGlc"},
    "ReportedGFR" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputGFR"},
    "ReportedAfricanGFR" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputGFRAfrican"},

    //////////////////
    // LFT
    "ALT" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputALT"},
    "AST" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputAST"},
    "ALP" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputALP"},
    "TBili" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputTbili"},
    "TProtein" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputTProt"},
    "Albumin" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputAlbumin"},
    "INR" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputINR"},
    "PT" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputPT"},
    "UricAcid" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputUrate"},
                    
    //////////////////
    // Urine
    "UrineUrea" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputUUN"},
    "UrineSodium" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputUNa"},
    "UrineCreatinine" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputUrineCr"}, // mg/dL
    "UrinePotassium" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputUK"},
    "UrineChloride" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputUCl"},
    "UrineProtein" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputUProt"},
    "UrineAlbumin" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputUrineAlb"}, // mcg/dL
    "UrineOsm" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputUOsm"},
    "UrineVolume" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputUrineVolume"},
    "UrineCalcium" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputUCa"},
    "UrinePhos" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputUPhos"},
    "UrineUrate" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputUUrate"},
    "UrineMag" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputUMag"},
    
    //////////////////
    // Vitals
    "Age" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputAge"},
    "WeightInKg" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputWt"},
    "HeightInCm" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputHt"},
    "SystolicBP" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputSBP"},
    "DiastolicBP" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputDBP"},
    "HR" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputHR"},
                    
    //////////////////
    // MBD
    "Calcium" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputCa"},
    "Phos" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputPhos"},
    "Mag" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputMag"},
    "VitD" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputVitD"},
    "PTH" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputPTH"},

    //////////////////
    // Dialysis 
    "PreBUN" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputPreBUN"},
    "PostBUN" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputPostBUN"},
    "HDTimeInMin" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputHDTime"},
    "PreHDWeightInKg" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputPreWeight"},
    "PostHDWeightInKg" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputPostWeight"},
    "FilterSelect" :     { "inputType" : "enum", "intVal" : -1, "strVal" : "x", "htmlElementID" : "FilterSelect"},
    "BloodFlowSelect" :     { "inputType" : "enum", "intVal" : -1, "strVal" : "x", "htmlElementID" : "BloodFlowSelect"},
    "HDFreqSelect" :     { "inputType" : "enum", "intVal" : -1, "strVal" : "x", "htmlElementID" : "HDFrequencySelect"},

    //////////////////
    // ABG
    "pH" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputABGpH"},
    "PaCO2" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputABGPaCO2"},
    "PaO2" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputABGPaO2"},

    //////////////////
    // CBC
    "WBC" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputCBCWBC"},
    "CBCHgb" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputCBCHgb"},
    "Platelet" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputCBCPlt"}, 

    //////////////////
    // Markers
    "CystatinC" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputCystatinC"}, 
    "HgbA1c" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputA1c"},  
    "Osmolality" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputOsm"},  

    //////////////////
    // Lipids
    "LDL" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputLDL"},
    "HDL" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputHDL"},
    "TChol" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputTChol"},

    //////////////////
    // Patient Questionaire
    // 
    // Additionally, boolean outputs have these additional fields:
    // "boolResultHTMLElementID"
    // "boolResultHTMLElement"
    // "outputOnStr"
    // "outputOffStr"
    // "drawColorsInRedGreen"
    // 
    "IsMale" :     { "inputType" : "bool", "intVal" : -1, "strVal" : "x", "htmlElementID" : "sexOption", "boolResultHTMLElementID" : "SexBoolOutput", "boolResultHTMLElement" : null, "outputOnStr" : "Male", "outputOffStr" : "Female", "drawColorsInRedGreen" : "1" },
    "IsCaucasian" :     { "inputType" : "bool", "intVal" : -1, "strVal" : "x", "htmlElementID" : "RaceOption", "boolResultHTMLElementID" : "RaceBoolOutput", "boolResultHTMLElement" : null, "outputOnStr" : "Caucasian", "outputOffStr" : "Other", "drawColorsInRedGreen" : "1" },
    "OnHTNMeds" :     { "inputType" : "bool", "intVal" : -1, "strVal" : "x", "htmlElementID" : "HTNOption", "boolResultHTMLElementID" : "OnHTNMedsBoolOutput", "boolResultHTMLElement" : null, "outputOnStr" : "YES", "outputOffStr" : "NO", "drawColorsInRedGreen" : "1" },
    "IsDiabetic" :     { "inputType" : "bool", "intVal" : -1, "strVal" : "x", "htmlElementID" : "DMOption", "boolResultHTMLElementID" : "DiabeticBoolOutput", "boolResultHTMLElement" : null, "outputOnStr" : "YES", "outputOffStr" : "NO", "drawColorsInRedGreen" : "1" },
    "IsSmoker" :     { "inputType" : "bool", "intVal" : -1, "strVal" : "x", "htmlElementID" : "SmokerOption", "boolResultHTMLElementID" : "SmokingBoolOutput", "boolResultHTMLElement" : null, "outputOnStr" : "YES", "outputOffStr" : "NO", "drawColorsInRedGreen" : "1" },
    "IsOnDialysis" :     { "inputType" : "bool", "intVal" : -1, "strVal" : "x", "htmlElementID" : "OnDialysisOption", "boolResultHTMLElementID" : "OnDialysisOptionOutput", "boolResultHTMLElement" : null, "outputOnStr" : "YES", "outputOffStr" : "NO", "drawColorsInRedGreen" : "1" },
    "AscitesSelect" :     { "inputType" : "enum", "intVal" : -1, "strVal" : "x", "htmlElementID" : "AscitesSelect"},
    "EncephalopathySelect" :     { "inputType" : "enum", "intVal" : -1, "strVal" : "x", "htmlElementID" : "EncephalopathySelect"},
   
    ////////////////////////////////////
    // Output values 
    // These have ADDITIONAL values, which are only used for the output values.
    // "outputPrefixStr"
    // "outputSuffixStr"
    //
    "CreatinineClearance" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "ResultCrCl", "outputPrefixStr" : "CreatinineClearance: ", "outputSuffixStr" : null},
    "FENa" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "ResultFENa", "outputPrefixStr" : "FENa: ", "outputSuffixStr" : null},
    "FEUrea" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "ResultFEUrea", "outputPrefixStr" : "FEUrea: ", "outputSuffixStr" : null},   
    "FEPhos" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "ResultFEPhos", "outputPrefixStr" : "FE-Phos: ", "outputSuffixStr" : null},
    "FECalcium" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "ResultFECalcium", "outputPrefixStr" : "FE-Calcium: ", "outputSuffixStr" : null},
    "FEUrate" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "ResultFEUrate", "outputPrefixStr" : "FE-Urate: ", "outputSuffixStr" : null},
    "GFR" :     { "inputType" : "none",  "intVal" : -1, "strVal" : "x", "htmlElementID" : "ResultGFR", "outputPrefixStr" : "GFR: ", "outputSuffixStr" : null},
    "AnionGap" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "AnionGap", "outputPrefixStr" : "AnionGap: ", "outputSuffixStr" : null},
    "UrineAnionGap" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "UrineAnionGap", "outputPrefixStr" : "UrineAnionGap: ", "outputSuffixStr" : null},
    "AdjustedAnionGap" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "AdjustedAnionGap", "outputPrefixStr" : "Adjusted AnionGap: ", "outputSuffixStr" : null},
    "AdjustedNa" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "AdjustedNa", "outputPrefixStr" : "AdjustedNa: ", "outputSuffixStr" : null},
    "AdjustedCa" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "AdjustedCa", "outputPrefixStr" : "AdjustedCa: ", "outputSuffixStr" : null},
    "Est2YearESRDRisk" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "TwoYrESRDRisk", "outputPrefixStr" : "Risk of ESRD in 2 years: ", "outputSuffixStr" : "%"},
    "Est5YearESRDRisk" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "FiveYrESRDRisk", "outputPrefixStr" : "Risk of ESRD in 5 years: ", "outputSuffixStr" : "%"},
    "UreaReductionRatio" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "UreaReductionRatio", "outputPrefixStr" : "Urea Reduction Ratio: ", "outputSuffixStr" : "%"},
    "EstimatedKtV" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "EstimatedKtV", "outputPrefixStr" : "Estimated Kt/V: ", "outputSuffixStr" : null},
    "SingleCompartmentKtV" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "SingleCompartmentKtV", "outputPrefixStr" : "Single Compartment Kt/V: ", "outputSuffixStr" : null},
    "EquilibratedKtV" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "EquilibratedKtV", "outputPrefixStr" : "Equilibrated Kt/V: ", "outputSuffixStr" : null},
    "StandardKtV" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "StandardKtV", "outputPrefixStr" : "Standard Kt/V: ", "outputSuffixStr" : null},
    "ChildPugh" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "ChildPughOutput", "outputPrefixStr" : "Child-Pugh: ", "outputSuffixStr" : "(*)"},
    "DiscriminantFunction" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "DiscriminantFunctionOutput", "outputPrefixStr" : "Maddreys Discriminant: ", "outputSuffixStr" : ""},
    "MELD" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "MELDOutput", "outputPrefixStr" : "MELD: ", "outputSuffixStr" : null},
    "FreeWaterDeficit" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "FreeWaterDeficitStrOutput", "outputPrefixStr" : "Free Water Deficit: ", "outputSuffixStr" : " liters"},
    "ElectrolyteFreeWaterClearance" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "ElectrolyteFreeWaterClearanceStrOutput", "outputPrefixStr" : "Electrolyte-Free Water Clearance: ", "outputSuffixStr" : " liters"},
    "TransTubularKGradient" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "TransTubularKGradientOutput", "outputPrefixStr" : "TransTubular K Gradient: ", "outputSuffixStr" : null},
    "ComputedSerumOsm" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "ComputedSerumOsm", "outputPrefixStr" : "ComputedSerumOsm: ", "outputSuffixStr" : null},
    "FraminghamOutput" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "FraminghamOutput", "outputPrefixStr" : "Framingham risk: ", "outputSuffixStr" : "% (*)"},
    "AaGradientOutput" :     { "inputType" : "none", "intVal" : -1, "strVal" : "x", "htmlElementID" : "AaGradientOutput", "outputPrefixStr" : "AaGradient: ", "outputSuffixStr" : ""},


    ////////////////////////////////////
    // CONTROL PANEL INPUTS
    "BaselineCreatinine" :     { "inputType" : "text", "intVal" : -1, "strVal" : "x", "htmlElementID" : "InputBaselineCrxxxx"},
}; // g_AllLabValuesDeclaration







////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_InitQuantState]
//
// This is called by the browser to initialize the entire UI.
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_InitQuantState() {    
    //LogEvent("MedNote_InitQuantState");
    for (var valueNameStr in g_AllLabValuesDeclaration) {
        //LogEvent("Found key: " + valueNameStr);
        //LogEvent("MedNote_InitOneQuantValueField. valueNameStr= " + valueNameStr);
        var valueEntry = g_AllLabValuesDeclaration[valueNameStr];
    }
} // MedNote_InitQuantState




////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_CalculateAllValues]
//
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_CalculateAllValues() {
    //LogEvent("MedNote_CalculateAllValues");
    var fShowValues = false;
    var creatinine = GetLabValue("Creatinine");
    var sodium = GetLabValue("Sodium");
    var albumin = GetLabValue("Albumin");
    var patientAge = GetLabValue("Age");
    var systolicBP = GetLabValue("SystolicBP");
    var serumHDL = GetLabValue("HDL");
    var totalChol = GetLabValue("TChol");
    var fAddFootNote = false;
 
    g_2YearESRDRisk = -1;
    g_5YearESRDRisk = -1;
    g_ComputedResultsDivElement.style.display = "None";


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
    // Chertow GM, Lowrie EG, Lew NL, Lazarus JM. Development of a population-specific regression equation to estimate total body water in hemodialysis patients. Kid Int 51:1578-1582, 1997.
    //
    // I use a much simpler method, which scales mass. But, the scale can vary depending on sex and age
    // Children: 0.6 
    // Adult men: 0.6 
    // Adult women: 0.5 
    // Geriatric (?age) men: 0.5 
    // Geriatric (age?) women: 0.45
    var EstimatedTotalBodyWater = -1;
    if (GetLabValue("WeightInKg") > 0) {
        EstimatedTotalBodyWater = 0.6 * GetLabValue("WeightInKg");
    }

    ///////////////////////////////////////////
    // Adjust Na for Glucose - do this BEFORE computing the anion gap.
    if ((sodium > 0) && (GetLabValue("Glucose") > 0)) {
        var adjustedNa = sodium + (2.4 * ((GetLabValue("Glucose") - 100) / 100));
        // Round it to 2 decomal places. We add 0.00001 to work around a Javascript bug.
        adjustedNa = Math.round((adjustedNa + 0.00001) * 100) / 100;
        var deltaNa = adjustedNa - sodium;
        if ((deltaNa > 4) || (deltaNa < -4)) {
            MedNote_SetValueNumber("AdjustedNa", adjustedNa);            
            //?????<> This is technically correct, but nobody will believe me.
            //sodium = adjustedNa;
            fShowValues = true;
        }
    }
        
    ///////////////////////////////////////////
    // GFR
    var estimatedGFR = 175;

    // If there is a GFR from the EMR, then use that. 
    // It saves a lot of hassles with Pharmacy.
    if ((GetLabValue("ReportedGFR") > 0) && (GetLabValue("IsCaucasian"))) {
        estimatedGFR = GetLabValue("ReportedGFR");
        MedNote_SetValueNumber("GFR", estimatedGFR);
    } else if ((GetLabValue("ReportedAfricanGFR") > 0) && (!GetLabValue("IsCaucasian"))) {
        estimatedGFR = GetLabValue("ReportedAfricanGFR");
        MedNote_SetValueNumber("GFR", estimatedGFR);
    // Otherwise, see what is missing:
    } else if ((creatinine < 0) || (patientAge < 0)) {
        var missingDataStr = "GFR: missing ";
        var fAddedFields = 0;
        if (creatinine < 0) {
            missingDataStr = missingDataStr + "Creatinine";
            fAddedFields = 1;
        }
        if (patientAge < 0) {
            if (fAddedFields) {
                missingDataStr = missingDataStr + ", ";
            }
            missingDataStr = missingDataStr + "Age";
            fAddedFields = 1;
        }
        MedNote_SetValueString("GFR", missingDataStr);
    // Otherwise, compute the real value.
    } else {
        var scaler;
        estimatedGFR = 175;

        scaler = Math.pow(creatinine, -1.154);
        estimatedGFR = estimatedGFR * scaler;

        scaler = Math.pow(patientAge, -0.203);
        estimatedGFR = estimatedGFR * scaler;

        if (!GetLabValue("IsMale") ) {
            estimatedGFR = estimatedGFR * 0.742;
        }        
        if (!GetLabValue("IsCaucasian")) {
            estimatedGFR = estimatedGFR * 1.212;
        }
        estimatedGFR = Math.round((estimatedGFR + 0.00001) * 100) / 100;
        MedNote_SetValueNumber("GFR", estimatedGFR); 
    }
    fShowValues = true;
    

    ///////////////////////////////////////////
    // Creatinine Clearance
    // This may seem odd, but it's still used for a lot of drug dosing.
    if ((patientAge > 0) && (GetLabValue("WeightInKg") > 0) && (creatinine > 0)) {
        var creatinineClearance = ((140 - patientAge) * GetLabValue("WeightInKg")) / (72 * creatinine);
        if (!GetLabValue("IsMale") ) {
            creatinineClearance = creatinineClearance * 0.85;
        }
        creatinineClearance = Math.round((creatinineClearance + 0.00001) * 100) / 100;
        MedNote_SetValueNumber("CreatinineClearance", creatinineClearance);
        fShowValues = true;

        // If the Cr Clearance is below 60, then the patient may have CKD.
        if ((creatinineClearance > 0) && (creatinineClearance < 60)) {
            CKDPlanButtonState = 1;
        }
    } // Creatinine Clearance

    
    ///////////////////////////////////////////
    // Adjust Calcium for Albumin    
    if ((GetLabValue("Calcium") > 0) && (albumin > 0) && (albumin < 4)) {
        var adjustedCa = GetLabValue("Calcium") + (0.8 * (4.0 - albumin));
        // Round it to 2 decomal places. We add 0.00001 to work around a Javascript bug.
        adjustedCa = Math.round((adjustedCa + 0.00001) * 100) / 100;
        var deltaNCa = adjustedCa - GetLabValue("Calcium");
        if ((deltaNCa > 1) || (deltaNCa < -1)) {
            MedNote_SetValueNumber("AdjustedCa", adjustedCa);
            fShowValues = true;
        }
    }
    

    ///////////////////////////////////////////
    // Framingham    
    if ((patientAge > 0) && (serumHDL > 0) && (totalChol > 0) && (systolicBP > 0)) {
        var score = 0;
        var risk = 0;
        var resultStr = "";

        ////////////////// MALE
        if (GetLabValue("IsMale") ) {
            ////////////////////
            // Age
            if ((patientAge >= 35) && (patientAge <= 39)) {
                score += 2;
            } else if ((patientAge >= 40) && (patientAge <= 44)) {
                score += 5;
            } else if ((patientAge >= 45) && (patientAge <= 49)) {
                score += 6;
            } else if ((patientAge >= 50) && (patientAge <= 54)) {
                score += 8;
            } else if ((patientAge >= 55) && (patientAge <= 59)) {
                score += 10;
            } else if ((patientAge >= 60) && (patientAge <= 64)) {
                score += 11;
            } else if ((patientAge >= 65) && (patientAge <= 69)) {
                score += 12;
            } else if ((patientAge >= 70) && (patientAge <= 74)) {
                score += 14;
            } else if (patientAge >= 75) {
                score += 15;
            }

            ////////////////////
            // HDL
            if (serumHDL >= 60) {
                score = score - 2;
            } else if ((serumHDL >= 50) && (serumHDL <= 59)) {
                score = score - 1;
            } else if ((serumHDL >= 35) && (serumHDL <= 44)) {
                score += 1;
            } else if (serumHDL < 35) {
                score += 2;
            }

            ////////////////////
            // Total Cholesterol
            if ((totalChol >= 160) && (totalChol <= 199)) {
                score += 1;
            } else if ((totalChol >= 200) && (totalChol <= 239)) {
                score += 2;
            } else if ((totalChol >= 240) && (totalChol <= 279)) {
                score += 3;
            } else if (totalChol >= 280) {
                score += 4;
            }

            ////////////////////
            // SBP Untreated
            if (!GetLabValue("OnHTNMeds")) {
                if ((systolicBP <= 120)) {
                    score = score - 2;
                } else if ((systolicBP >= 130) && (systolicBP <= 139)) {
                    score += 1;
                } else if ((systolicBP >= 140) && (systolicBP <= 159)) {
                    score += 2;
                } else if (systolicBP >= 160) {
                    score += 3;
                }
            } // if (!GetLabValue("OnHTNMeds"))
            else {  // SBP Treated
                if ((systolicBP >= 120) && (systolicBP <= 129)) {
                    score += 2;
                } else if ((systolicBP >= 130) && (systolicBP <= 139)) {
                    score += 3;
                } else if ((systolicBP >= 140) && (systolicBP <= 159)) {
                    score += 4;
                } else if (systolicBP >= 160) {
                    score += 5;
                }
            } // if (GetLabValue("OnHTNMeds"))

            ////////////////////
            // Diabetic and Smoking
            if (GetLabValue("IsDiabetic")) {
                score += 3;
            }
            if (GetLabValue("IsSmoker")) {
                score += 4;
            }

            if (score <= -3) {
                risk = 0;
            } else if (score == -2) {
                risk = 1.1;
            } else if (score == -1) {
                risk = 1.4;
            } else if (score == 0) {
                risk = 1.6;
            } else if (score == 1) {
                risk = 1.9;
            } else if (score == 2) {
                risk = 2.3;
            } else if (score == 3) {
                risk = 2.8;
            } else if (score == 4) {
                risk = 3.3;
            } else if (score == 5) {
                risk = 3.9;
            } else if (score == 6) {
                risk = 4.7;
            } else if (score == 7) {
                risk = 5.6;
            } else if (score == 8) {
                risk = 6.7;
            } else if (score == 9) {
                risk = 7.9;
            } else if (score == 10) {
                risk = 9.4;
            } else if (score == 11) {
                risk = 11.2;
            } else if (score == 12) {
                risk = 13.2;
            } else if (score == 13) {
                risk = 15.6;
            } else if (score == 14) {
                risk = 18.4;
            } else if (score == 15) {
                risk = 21.6;
            } else if (score == 16) {
                risk = 25.3;
            } else if (score == 17) {
                risk = 29.4;
            } else if (score >= 18) {
                risk = 30;
            }

        ////////////////// FEMALE
        } else {
            ////////////////////
            // Age
            if ((patientAge >= 35) && (patientAge <= 39)) {
                score += 2;
            } else if ((patientAge >= 40) && (patientAge <= 44)) {
                score += 4;
            } else if ((patientAge >= 45) && (patientAge <= 49)) {
                score += 5;
            } else if ((patientAge >= 50) && (patientAge <= 54)) {
                score += 7;
            } else if ((patientAge >= 55) && (patientAge <= 59)) {
                score += 8;
            } else if ((patientAge >= 60) && (patientAge <= 64)) {
                score += 9;
            } else if ((patientAge >= 65) && (patientAge <= 69)) {
                score += 10;
            } else if ((patientAge >= 70) && (patientAge <= 74)) {
                score += 11;
            } else if (patientAge >= 75) {
                score += 12;
            }

            ////////////////////
            // HDL
            if (serumHDL >= 60) {
                score = score - 2;
            } else if ((serumHDL >= 50) && (serumHDL <= 59)) {
                score = score - 1;
            } else if ((serumHDL >= 35) && (serumHDL <= 44)) {
                score += 1;
            } else if (serumHDL < 35) {
                score += 2;
            }

            ////////////////////
            // Total Cholesterol
            if ((totalChol >= 160) && (totalChol <= 199)) {
                score += 1;
            } else if ((totalChol >= 200) && (totalChol <= 239)) {
                score += 3;
            } else if ((totalChol >= 240) && (totalChol <= 279)) {
                score += 4;
            } else if (totalChol >= 280) {
                score += 5;
            }

            ////////////////////
            // SBP Untreated
            if (!GetLabValue("OnHTNMeds")) {
                if ((systolicBP <= 120)) {
                    score = score - 3;
                } else if ((systolicBP >= 130) && (systolicBP <= 139)) {
                    score += 1;
                } else if ((systolicBP >= 140) && (systolicBP <= 149)) {
                    score += 2;
                } else if ((systolicBP >= 150) && (systolicBP <= 159)) {
                    score += 4;
                } else if (systolicBP >= 160) {
                    score += 5;
                }
            } // if (!GetLabValue("OnHTNMeds"))

            ////////////////////
            // SBP Treated
            if (GetLabValue("OnHTNMeds")) {
                if ((systolicBP <= 120)) {
                    score = score - 1;
                } else if ((systolicBP >= 120) && (systolicBP <= 129)) {
                    score += 2;
                } else if ((systolicBP >= 130) && (systolicBP <= 139)) {
                    score += 3;
                } else if ((systolicBP >= 140) && (systolicBP <= 149)) {
                    score += 5;
                } else if ((systolicBP >= 150) && (systolicBP <= 159)) {
                    score += 6;
                } else if (systolicBP >= 160) {
                    score += 7;
                }
            } // if (GetLabValue("OnHTNMeds"))

            ////////////////////
            // Diabetic and Smoking
            if (GetLabValue("IsDiabetic")) {
                score += 4;
            }
            if (GetLabValue("IsSmoker")) {
                score += 3;
            }

            if (score <= -2) {
                risk = 0;
            } else if (score == -1) {
                risk = 1.0;
            } else if (score == 0) {
                risk = 1.2;
            } else if (score == 1) {
                risk = 1.5;
            } else if (score == 2) {
                risk = 1.7;
            } else if (score == 3) {
                risk = 2.0;
            } else if (score == 4) {
                risk = 2.4;
            } else if (score == 5) {
                risk = 2.8;
            } else if (score == 6) {
                risk = 3.3;
            } else if (score == 7) {
                risk = 3.9;
            } else if (score == 8) {
                risk = 4.5;
            } else if (score == 9) {
                risk = 5.3;
            } else if (score == 10) {
                risk = 6.3;
            } else if (score == 11) {
                risk = 7.3;
            } else if (score == 12) {
                risk = 8.6;
            } else if (score == 13) {
                risk = 10.0;
            } else if (score == 14) {
                risk = 11.7;
            } else if (score == 15) {
                risk = 13.7;
            } else if (score == 16) {
                risk = 15.9;
            } else if (score == 17) {
                risk = 18.5;
            } else if (score == 18) {
                risk = 21.5;
            } else if (score == 19) {
                risk = 24.8;
            } else if (score == 20) {
                risk = 28.5;
            } else if (score >= 21) {
                risk = 30;
            }
        }
        
        MedNote_SetValueNumber("FraminghamOutput", risk);
        fShowValues = true;
        fAddFootNote = true;
    }
    

    ///////////////////////////////////////////
    // ESRD Risk
    if ((GetLabValue("GFR") > 0) || (GetLabValue("ReportedGFR") > 0) || (GetLabValue("ReportedAfricanGFR"))) {
        // This seems to use the reported Calcium, not the value corrected by albumin.
        if ((GetLabValue("UrineCreatinine") > 0) && (GetLabValue("UrineAlbumin") > 0) && (patientAge > 0) && (GetLabValue("Calcium") > 0) && (GetLabValue("Phos") > 0) && (albumin > 0) && (GetLabValue("HCO3") > 0)) {
            //<><><>ComputeRiskOfESRD();
            MedNote_SetValueNumber("Est2YearESRDRisk", g_2YearESRDRisk);
            MedNote_SetValueNumber("Est5YearESRDRisk", g_5YearESRDRisk);
            fShowValues = true;
        }
    }

    ///////////////////////////////////////////
    // Urea Reduction Ratio
    if ((GetLabValue("PreBUN") > 0) && (GetLabValue("PostBUN") > 0)) {
        // URR is usually measured only once every 12 to 14 treatments, which is once a month
        // Target *average* URR over 65%
        var ureaReductionRatio = ((GetLabValue("PreBUN") - GetLabValue("PostBUN")) / GetLabValue("PreBUN")) * 100;
       
        // Round it to 1 decomal places. We add 0.00001 to work around a Javascript bug.
        ureaReductionRatio = Math.round((ureaReductionRatio + 0.00001) * 10) / 10;
        MedNote_SetValueNumber("UreaReductionRatio", ureaReductionRatio);
    }
    
    ///////////////////////////////////////////
    // Kt/v
    if ((GetLabValue("PreBUN") > 0) 
            && (GetLabValue("PostBUN") > 0) 
            && (GetLabValue("PostHDWeightInKg") > 0) 
            && (GetLabValue("PreHDWeightInKg") > 0)
            && (GetLabValue("HDTimeInMin") > 0)) {
        var MinutesInWeek = 10080;
        var UFInKg = GetLabValue("PreHDWeightInKg") - GetLabValue("PostHDWeightInKg");
        var treatmentsPerWeek = 3;
        var theoreticalKtV = -1;
        var singleCompartmentKtV = -1;
        var equilibratedKtV;
        var standardKtV;

        // Single Pool Kt/V
        // See Daugirdas JT, "Second generation logarithmic estimates of single-pool variable volume Kt/V: an analysis of error", J Am Soc Nephrol. 1993 Nov;4(5):1205-13.
        // http://www.ncbi.nlm.nih.gov/pubmed/8305648
        singleCompartmentKtV =  - Math.log((GetLabValue("PostBUN") / GetLabValue("PreBUN")) - (0.008 * (GetLabValue("HDTimeInMin") / 60))) 
                                    + ((4 - (3.5 * (GetLabValue("PostBUN") / GetLabValue("PreBUN")))) * (UFInKg / GetLabValue("PostHDWeightInKg")));

        // Equilibrated Kt/V
        // See Leypoldt equation for Equilibrated Double Pool
        // http://onlinelibrary.wiley.com/doi/10.1111/j.1525-139X.2006.00132.x/full
        var equilibratedKtV = (0.924 * singleCompartmentKtV) 
                                - (0.395 * (singleCompartmentKtV / (GetLabValue("HDTimeInMin") / 60))) 
                                + 0.056;

        if (equilibratedKtV > singleCompartmentKtV) {
            equilibratedKtV = singleCompartmentKtV;
        }
        
        // Standard Kt/V
        // See Leypoldt equation for Standard (stdKt/V)					
        //var standardKtV = (MinutesInWeek * (1 - Math.exp(-equilibratedKtV)) / GetLabValue("HDTimeInMin")) / (((1 - Math.exp(-equilibratedKtV)) /singleCompartmentKtV) + (MinutesInWeek / (treatmentsPerWeek * GetLabValue("HDTimeInMin")) -1));
        var standardKtV = (MinutesInWeek * (1-Math.exp(- equilibratedKtV)) / GetLabValue("HDTimeInMin")) 
                        / (((1 - Math.exp(- equilibratedKtV)) / singleCompartmentKtV) + (MinutesInWeek / (treatmentsPerWeek * GetLabValue("HDTimeInMin")) - 1));

        // Theoretical Kt/v, assuming a perfect filter that does not get clogged as the session goes on, and
        // also no urea rebound from extravascular space
        if ((GetLabValue('FilterSelect') > -1) && (GetLabValue('BloodFlowSelect') > -1)) {
            var bloodFlowIndex = GetLabValue('BloodFlowSelect');
            var bloodFlowStr = g_BloodFlowList[bloodFlowIndex];
            var bloodFlow = parseInt(bloodFlowStr);

            var clearance = 0;
            var filterName = GetLabValueStringForPlan('FilterSelect');
            if (filterName == "F-160") {
                var clearanceArray = g_F160Info.UreaCl;
                clearance = g_F160Info.UreaCl[bloodFlowIndex];
            } else if (filterName == "F-180") {   
                clearance = g_F180Info.UreaCl[bloodFlowIndex];
            } else if (filterName == "F-200") {   
                clearance = g_F200Info.UreaCl[bloodFlowIndex];
            } else if (filterName == "Exceltra-170") {
                clearance = g_Exceltra170Info.UreaCl[bloodFlowIndex];
            } else if (filterName == "Exceltra-190") {
                clearance = g_Exceltra190Info.UreaCl[bloodFlowIndex]; 
            } else if (filterName == "Exceltra-210") {
                clearance = g_Exceltra210Info.UreaCl[bloodFlowIndex];
            } else if (filterName == "Revaclear") {
                clearance = g_RevaclearInfo.UreaCl[bloodFlowIndex]; 
            } else if (filterName == "Revaclear-MAX") {
                clearance = g_RevaclearMaxInfo.UreaCl[bloodFlowIndex];
            }

            theoreticalKtV = (clearance * GetLabValue("HDTimeInMin")) / EstimatedTotalBodyWater;
        } 

        // Round it to 2 decomal places. We add 0.00001 to work around a Javascript bug.
        standardKtV = Math.round((standardKtV + 0.00001) * 100) / 100;
        equilibratedKtV = Math.round((equilibratedKtV + 0.00001) * 100) / 100;
        singleCompartmentKtV = Math.round((singleCompartmentKtV + 0.00001) * 100) / 100;
        theoreticalKtV = Math.round((theoreticalKtV + 0.00001) * 100) / 100;
                
        MedNote_SetValueNumber("StandardKtV", standardKtV);
        MedNote_SetValueNumber("EquilibratedKtV", equilibratedKtV);
        MedNote_SetValueNumber("SingleCompartmentKtV", singleCompartmentKtV);
        MedNote_SetValueNumber("EstimatedKtV", theoreticalKtV);
        fShowValues = true;
    }

    ///////////////////////////////////////////
    if ((sodium > 0) && (GetLabValue("Glucose") > 0) && (GetLabValue("BUN") > 0)) {
        var serumOsm = (2 * sodium) + (GetLabValue("Glucose") / 18) + (GetLabValue("BUN") / 2.8);        
        
        serumOsm = Math.round((serumOsm + 0.00001) * 10) / 10;
        MedNote_SetValueNumber("ComputedSerumOsm", serumOsm);
        fShowValues = true;
    } 


    ///////////////////////////////////////////
    //
    // Maddrey Discriminant Function
    //
    // Maddrey WC, Boitnott JK, Bedine MS, Weber FL, Mezey E, White RI (1978). 
    // "Corticosteroid therapy of alcoholic hepatitis"
    // Gastroenterology 75 (2): 193–9. PMID 352788
    //
    // Soultati AS, et. al. 
    // Predicting utility of a model for end stage liver disease in alcoholic liver disease
    // World J Gastroenterol 2006 July 07;12(25):4020-4025
    if ((GetLabValue("PT") > 0) && (creatinine > 0) && (GetLabValue("TBili") > 0)) {
        // The reference range for prothrombin time is 9.5-13.5 seconds.
        var ReferencePT = 11.5;
        
        var discriminantFunction = (4.6 * (GetLabValue("PT") - ReferencePT)) + GetLabValue("TBili");
        discriminantFunction = Math.round(discriminantFunction);

        MedNote_SetValueNumber("DiscriminantFunction", discriminantFunction);
        fShowValues = true;
    }

    ///////////////////////////////////////////
    // Child-Pugh
    //
    // François Durand, Dominique Valla
    // Assessment of the prognosis of cirrhosis: Child–Pugh versus MELD
    // Journal of hepatology April 2005 Volume 42, Issue 1, Supplement, Pages S100–S107
    if ((albumin > 0) && (GetLabValue("TBili") > 0) && (GetLabValue("INR") > 0)) {
        var score = 0;
        
        var tBili = GetLabValue("TBili");
        if (tBili < 2) {
            score += 1;
        } else if (tBili <= 3) {
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
        
        var INR = GetLabValue("INR");
        if (INR < 1.7) {
            score += 1;
        } else if (INR <= 2.2) {
            score += 2;
        } else {
            score += 3;
        }

        var ascites = GetLabValue("AscitesSelect");
        if (ascites == 0) { // absent
            score += 1;
        } else if (ascites == 2) { // Slight
            score += 2;
        } else {
            score += 3;
        }

        var encephalopathy = GetLabValue("EncephalopathySelect");
        if (encephalopathy == 1) { // None
            score += 1;
        } else if (encephalopathy == 2) { // Grade 1-2
            score += 2;
        } else {
            score += 3;
        }

        score = Math.round(score);

        var className = "(Class A)";
        if ((score >= 7) && (score <= 9)) {
            className = "(Class B)";
        } else if ((score >= 10)) {
            className = "(Class C)";
        }

        MedNote_SetValueNumber("ChildPugh", score);
        fAddFootNote = true;
        fShowValues = true;
    }

        
    ///////////////////////////////////////////
    // Aa Gradient
    // 
    // Normal gradient is < 10. A high Aa gradient means impaired diffusion or VQ mismatch due to shunting. 
    // This assumes 100% humidity at sea level and a respiratory quotient of 0.8
    if ((GetLabValue("PaO2") > 0) && (GetLabValue("PaCO2") > 0)) {
        var FiO2 = 0.21;
        var PAO2 = (FiO2 * (760 - 47)) - (GetLabValue("PaCO2") / 0.8);
        var AaGradient = PAO2 - GetLabValue("PaO2");        
        
        AaGradient = Math.round(AaGradient);
        MedNote_SetValueNumber("AaGradientOutput", AaGradient);
        fShowValues = true;
    }
    
    ///////////////////////////////////////////
    // Free Water Deficit
    if (sodium > 0) {        
        var freeWaterDeficit = EstimatedTotalBodyWater * ((sodium / 140) - 1);
        // This is in liters, so round to the nearest 10th
        freeWaterDeficit = Math.round((freeWaterDeficit + 0.00001) * 10) / 10;

        MedNote_SetValueNumber("FreeWaterDeficit", freeWaterDeficit);
        fShowValues = true;
    }

    ///////////////////////////////////////////
    // Electrolyte-Free Water Clearance
    //
    // See Minhtri K. Nguyen and Ira Kurtz, 
    // "Derivation of a new formula for calculating urinary electrolyte-free water clearance based on the Edelman equation"
    // Am J Physiol Renal Physiol 288: F1–F7, 2005;
    // http://ajprenal.physiology.org/content/ajprenal/288/1/F1.full.pdf
    if ((sodium > 0) 
            && (GetLabValue("UrineSodium") > 0) 
            && (GetLabValue("UrinePotassium") > 0) 
            && (GetLabValue("UrineVolume") > 0)) {
        var urineLyteConcentration = GetLabValue("UrineSodium") + GetLabValue("UrinePotassium");
        var fractionOfUrineThatIsIsoOsmolar = urineLyteConcentration / sodium;
        var fractionOfUrineThatIsIsPureWater = 1 - fractionOfUrineThatIsIsoOsmolar;
        var volumeOfUrineThatIsIsPureWater = fractionOfUrineThatIsIsPureWater * GetLabValue("UrineVolume");

        // This is in liters, so round to the nearest 10th
        volumeOfUrineThatIsIsPureWater = Math.round((volumeOfUrineThatIsIsPureWater + 0.00001) * 10) / 10;
        MedNote_SetValueNumber("ElectrolyteFreeWaterClearance", volumeOfUrineThatIsIsPureWater);
    }
    
    ///////////////////////////////////////////
    // Trans-Tubular Potassium Gradient
    if ((sodium > 0) 
            && (GetLabValue("Glucose") > 0) 
            && (GetLabValue("BUN") > 0) 
            && (GetLabValue("Potassium") > 0) 
            && (GetLabValue("UrinePotassium") > 0) 
            && (GetLabValue("UrineOsm") > 0)) {
        var serumOsm = GetLabValue("Osmolality");
        if (serumOsm < 0) {
            serumOsm = (2 * sodium) + (GetLabValue("Glucose") / 18) + (GetLabValue("BUN") / 2.8);
        }
  
        var transTubularKGradient = ((GetLabValue("UrinePotassium") / (GetLabValue("Potassium")))
                / (GetLabValue("UrineOsm") / serumOsm));
        transTubularKGradient = Math.round((transTubularKGradient + 0.00001) * 10) / 10;
        
        MedNote_SetValueNumber("TransTubularKGradient", transTubularKGradient);
        fShowValues = true;
    } 

    ///////////////////////////////////////////
    // FENa - Fractional Excretion Sodium
    if ((GetLabValue("UrineSodium") > 0) && (sodium > 0) && (GetLabValue("UrineCreatinine") > 0) && (creatinine > 0)) {
        var FENa = (GetLabValue("UrineSodium") / sodium) / (GetLabValue("UrineCreatinine") / creatinine);
        // Convert to a percentage
        FENa = FENa * 100;
        // Round it to 2 decomal places. We add 0.00001 to work around a Javascript bug.
        FENa = Math.round((FENa + 0.00001) * 100) / 100;
        MedNote_SetValueNumber("FENa", FENa);
        fShowValues = true;
    }
    
    ///////////////////////////////////////////
    // FEUrea - Fractional Excretion Urea
    if ((GetLabValue("UrineUrea")  > 0) && (GetLabValue("BUN") > 0) && (GetLabValue("UrineCreatinine") > 0) && (creatinine > 0)) {
        var FEUrea = (GetLabValue("UrineUrea") / GetLabValue("BUN")) / (GetLabValue("UrineCreatinine") / creatinine);
        // Convert to a percentage
        FEUrea = FEUrea * 100;
        // Round it to 2 decomal places. We add 0.00001 to work around a Javascript bug.
        FEUrea = Math.round((FEUrea + 0.00001) * 100) / 100;
        MedNote_SetValueNumber("FEUrea", FEUrea);
    }
         

    ///////////////////////////////////////////
    // Fractional Excretion Phos
    if ((GetLabValue("UrinePhos")  > 0) 
            && (GetLabValue("Phos") > 0) 
            && (GetLabValue("UrineCreatinine") > 0)
            && (creatinine > 0)) {
        var FEPhos = (GetLabValue("UrinePhos") / GetLabValue("Phos")) / (GetLabValue("UrineCreatinine") / creatinine);
        // Convert to a percentage
        FEPhos = FEPhos * 100;
        // Round it to 2 decomal places. We add 0.00001 to work around a Javascript bug.
        FEPhos = Math.round((FEPhos + 0.00001) * 100) / 100;
        MedNote_SetValueNumber("FEPhos", FEPhos);
    }


    ///////////////////////////////////////////
    // Fractional Excretion Calcium
    if ((GetLabValue("UrineCalcium")  > 0) 
            && (GetLabValue("Calcium") > 0) 
            && (GetLabValue("UrineCreatinine") > 0)
            && (creatinine > 0)) {
        var FECalcium = (GetLabValue("UrineCalcium") / GetLabValue("Calcium")) / (GetLabValue("UrineCreatinine") / creatinine);
        // Convert to a percentage
        FECalcium = FECalcium * 100;
        // Round it to 2 decomal places. We add 0.00001 to work around a Javascript bug.
        FECalcium = Math.round((FECalcium + 0.00001) * 100) / 100;
        MedNote_SetValueNumber("FECalcium", FECalcium);
    }

    ///////////////////////////////////////////
    // Fractional Excretion Urate
    if ((GetLabValue("UrineUrate")  > 0) 
            && (GetLabValue("UricAcid") > 0) 
            && (GetLabValue("UrineCreatinine") > 0)
            && (creatinine > 0)) {
        var FEUrate = (GetLabValue("UrineUrate") / GetLabValue("UricAcid")) / (GetLabValue("UrineCreatinine") / creatinine);
        // Convert to a percentage
        FEUrate = FEUrate * 100;
        // Round it to 2 decomal places. We add 0.00001 to work around a Javascript bug.
        FEUrate = Math.round((FEUrate + 0.00001) * 100) / 100;
        MedNote_SetValueNumber("FEUrate", FEUrate);
    }   



    //LogEvent("Got to end of MedNote_CalculateAllValues. fShowValues=" + fShowValues);
    if (fShowValues) {
        //LogEvent("Got to end of MedNote_CalculateAllValues. g_ComputedResultsDivElement=" + g_ComputedResultsDivElement);
        g_ComputedResultsDivElement.style.display = "inline";
    }


    if (GetLabValue("IsMale")) {
        g_hisHer = "his";
        g_CapHisHer = "His";
        g_himHer = "him";
        g_CapHimHer = "His";
        g_heShe = "he";
        g_CapHeShe = "He";
    } else {
        g_hisHer = "her";
        g_CapHisHer = "Her";
        g_himHer = "her";
        g_CapHimHer = "Her";
        g_heShe = "she";
        g_CapHeShe = "She";
    }
} // MedNote_CalculateAllValues






////////////////////////////////////////////////////////////////////////////////
//
// [SaveValueFromOneString]
//
// This is used by the import functions, so it reads a value from a text string
// that was imported from another EMR system.
////////////////////////////////////////////////////////////////////////////////
function 
SaveValueFromOneString(lineArray, lineNum, valueNameStr, str, startIndex) {
    //LogEvent("SaveValueFromOneString. lineNum=" + lineNum + ", str=" + str);
    var totalNumberStr = "";
    var startLineNum = lineNum;

    while (true) {
        totalNumberStr = ReadNumberFromStr(str, startIndex);
        if (totalNumberStr != "") {
            //LogEvent("SaveValueFromOneString. totalNumberStr=" + totalNumberStr);
            MedNote_SetValueNumber(valueNameStr, intVal);
            return(lineNum);
        } // if (totalNumberStr != "")

        lineNum += 1;
        if (lineNum >= lineArray.length) {
            return(lineNum);
        }
        str = lineArray[lineNum];
    } // while (true)
} // SaveValueFromOneString





////////////////////////////////////////////////////////////////////////////////
//
// [ReadNumberFromStr]
//
// This is used by the import functions, so it reads a value from a text string
// that was imported from another EMR system.
////////////////////////////////////////////////////////////////////////////////
function
ReadNumberFromStr(str, startIndex) {
    //LogEvent("ReadNumberFromStr. startIndex=" + startIndex + ", Str=" + str);
    var index;
    var currentChar;
    var charArray;
    var tempCharStr;
    var currentCharAsNumber;
    var totalNumberStr = "";
    var charCode;

    // Remove the prefix. This saves time, but it also avoids confusion over names that contain
    // numbers, like "CO2"
    str = str.substring(startIndex, 200);
    //LogEvent("ReadNumberFromStr. modified split Str=" + str);
    charArray = str.split('');
    
    // Skip ahead to the first number character.
    for (index = 0; index < charArray.length; index++) {
        currentChar = charArray[index];
        //LogEvent("ReadNumberFromStr. currentChar=" + currentChar);
        tempCharStr = "" + currentChar;
        //LogEvent("ReadNumberFromStr. tempCharStr=" + tempCharStr);
        currentCharAsNumber = parseInt(tempCharStr);
        //LogEvent("ReadNumberFromStr. currentCharAsNumber=" + currentCharAsNumber);
        if (!isNaN(currentCharAsNumber)) {
            //LogEvent("ReadNumberFromStr. Found a Number! currentCharAsNumber=" + currentCharAsNumber);
            break;
        }
    }

    // Read all of the number chars
    for (index = index; index < charArray.length; index++) {
        currentChar = charArray[index];
        //LogEvent("ReadNumberFromStr. currentChar=" + currentChar);
        tempCharStr = "" + currentChar;
        charCode = tempCharStr.charCodeAt(0);
        //LogEvent("ReadNumberFromStr. charCode=" + charCode);
        if (((charCode >= 48) && (charCode <= 57)) || (charCode == 46)) {
            //LogEvent("ReadNumberFromStr. Add one number to the str. tempCharStr=" + tempCharStr);
            totalNumberStr = totalNumberStr + tempCharStr;
        } else {
            break;
        }
    }

    //LogEvent("ReadNumberFromStr. totalNumberStr=" + totalNumberStr);
    return(totalNumberStr);
} // ReadNumberFromStr




////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_ImportCPRSLabs]
//
////////////////////////////////////////////////////////////////////////////////
function
MedNote_ImportCPRSLabs(lineArray) {
    //LogEvent("MedNote_ImportCPRSLabs");
    var index = 0;
    while (index < lineArray.length) {
        index = ParseOneCPRSLine(lineArray, index);
        //LogEvent("MedNote_ImportCPRSLabs. Line " + index);
    }
} // MedNote_ImportCPRSLabs




////////////////////////////////////////////////////////////////////////////////
//
// [ParseOneCPRSLine]
//
////////////////////////////////////////////////////////////////////////////////
function 
ParseOneCPRSLine(lineArray, lineNum) {
    //LogEvent("ParseOneCPRSLine. lineNum=" + lineNum);
    var index;
    var index2;
    var index3;
    var str = lineArray[lineNum];
    //LogEvent("ParseOneCPRSLine. str=" + str);
       

    //////////////////
    // Urine
    // Do this FIRST, because other names are prefixes of these names, so we could accidentally
    // mistake "PROTEIN URINE" for "PROTEIN"
    index = str.indexOf("SODIUM URINE"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "UrineSodium", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("POTASSIUM URINE"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "UrinePotassium", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("CHLORIDE URINE"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "UrineChloride", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("Urea Nit Ur Qn"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "UrineUrea", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("URINE CREATININE"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "UrineCreatinine", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("MICROALBUMIN"); 
    if (index == 0) {
        // This is mg/L
        lineNum = SaveValueFromOneString(lineArray, lineNum, "UrineAlbumin", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("PROTEIN URINE"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "UrineProtein", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("OSMOLALITY URINE"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "UrineOsm", str, index);
        return(lineNum + 1);
    }

    
    /////////////////////////
    // BMP
    index = str.indexOf("SODIUM"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "Sodium", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("POTASSIUM"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "Potassium", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("CHLORIDE"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "Chloride", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("CO2"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "HCO3", str, index + 4);
        return(lineNum + 1);
    }
    index = str.indexOf("UREA NITROGEN"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "BUN", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("CREATININE"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "Creatinine", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("GLUCOSE"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "Glucose", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("eGFR"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "ReportedGFR", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("xxxx"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "ReportedAfricanGFR", str, index);
        return(lineNum + 1);
    }

    // We can also get values from a blood gas.
    //HCO3-(c)                       28.1 H   mmol/L     22 - 26          [583]
    //HEMOGLOBIN, TOTAL (B-GAS)       8.8 L   G/DL       14 - 18          [583]
    //SODIUM (B-GAS)                  133 L   mmol/L     135 - 145        [583]
    //POTASSIUM (B-GAS)               5.4     mmol/L     3.5 - 5.5        [583]
    //CHLORIDE (B-GAS)                109 H   mmol/L     98 - 107         [583]
    //GLUCOSE (B-GAS)                 158 H   mg/dL      65 - 110         [583]
    //IONIZED CALCIUM                4.13 L   mg/dL      4.50 - 5.30      [583]

        
    /////////////////////////
    // LFT
    index = str.indexOf("SGPT"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "ALT", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("SGOT"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "AST", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("ALKALINE PHOSPHATASE"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "ALP", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("TOT. BILIRUBIN"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "TBili", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("PROTEIN,TOTAL"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "TProtein", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("ALBUMIN"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "Albumin", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("INR"); 
    if (index >= 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "INR", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("PT"); 
    if (index >= 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "PT", str, index);
        return(lineNum + 1);
    }


    //////////////////
    // MBD
    index = str.indexOf("CALCIUM"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "Calcium", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("PO4"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "Phos", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("VITAMIN D, TOTAL"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "VitD", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("PTH (INTACT)"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "PTH", str, index);
        return(lineNum + 1);
    }
    
    //////////////////
    // CBC
    index = str.indexOf("PLT"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "Platelet", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("WBC "); 
    index2 = str.indexOf("WBC:UA"); 
    index3 = str.indexOf("WBC Esterase"); 
    if ((index2 >= 0) || (index3 >= 0)) {
    } else if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "WBC", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("HEMOGLOBIN A1C"); 
    index2 = str.indexOf("HGB UA"); 
    index3 = str.indexOf("HGB"); 
    if (index == 0) {
        //LogEvent("Try to read A1c. str=" + str);
        lineNum = SaveValueFromOneString(lineArray, lineNum, "HgbA1c", str, index + 7);
        return(lineNum + 1);
    } else if (index2 >= 0) {
        //LogEvent("Try to read Hgb UA. str=" + str);
    } else if (index3 >= 0) {
        //LogEvent("Try to read Hgb. str=" + str);
        lineNum = SaveValueFromOneString(lineArray, lineNum, "CBCHgb", str, index3);
        return(lineNum + 1);
    }

    //////////////////
    // ABG
    index = str.indexOf("PH (B-GAS)"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "pH", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("PCO2"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "PaCO2", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("PO2"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "PaO2", str, index);
        return(lineNum + 1);
    }
    

    //////////////////
    // Vitals
    index = str.indexOf("Weight Lbs"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "WeightInKg", str, index);
        // Convert lbs to kg
        var valueEntry = g_AllLabValuesDeclaration['WeightInKg'];    
        if (valueEntry) {
            valueEntry.intVal = valueEntry.intVal / 2.20462;
        }
        return(lineNum + 1);
    }
    index = str.indexOf("Weight Metric"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "WeightInKg", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("BP Sys"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "SystolicBP", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("BP Dias"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "DiastolicBP", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("Pulse"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "HR", str, index);
        return(lineNum + 1);
    }
    // <> Need These
    // "Age" "HeightInCm" 
    // "PreBUN"  "PostBUN"  "HDTimeInMin"  "PreHDWeightInKg"  "PostHDWeightInKg" "FilterSelect" "BloodFlowSelect" "HDFreqSelect" "CystatinC"  "IsMale" "IsCaucasian" "OnHTNMeds" "IsDiabetic" "IsSmoker" 


    //////////////////
    // Lipids
    index = str.indexOf("LDL CHOLESTEROL"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "LDL", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("QUANTITATIVE LDL"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "LDL", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("HDL CHOLESTEROL"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "HDL", str, index);
        return(lineNum + 1);
    }
    index = str.indexOf("CHOLESTEROL,TOTAL"); 
    if (index == 0) {
        lineNum = SaveValueFromOneString(lineArray, lineNum, "TChol", str, index);
        return(lineNum + 1);
    }


    // Resume parsing on the next line.
    //LogEvent("ParseOneCPRSLine. Didnt recognize the line. lineNum=" + lineNum);
    return(lineNum + 1);
} // ParseOneCPRSLine






////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_SetValueNumber]
//
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_SetValueNumber(valueNameStr, intVal) {    
    var outputStr = "";
    var textNode;

    //LogEvent("MedNote_SetValueNumber. valueNameStr= " + valueNameStr);
    var valueEntry = g_AllLabValuesDeclaration[valueNameStr];    
    if (!valueEntry) {
        LogEvent("!!!!BUG!!!!!! MedNote_SetValueNumber. NULL valueEntry. valueNameStr= " + valueNameStr);
        return;
    }
    
    valueEntry.intVal = Math.round(intVal * 10) / 10;
    // If we are initializing, then set the input or output to an empty string.
    if (intVal == -1) {
        valueEntry.strVal = "";
    // Otherwise, we are settiung it to a valid value.
    } else {
        valueEntry.strVal = valueEntry.strVal + valueEntry.intVal.toString();
        outputStr = "";
        if (valueEntry.outputPrefixStr) {
            outputStr = outputStr + valueEntry.outputPrefixStr;
        }
        outputStr = outputStr + valueEntry.strVal;
        if (valueEntry.outputSuffixStr) {
            outputStr = outputStr + valueEntry.outputSuffixStr;
        }
    }
} // MedNote_SetValueNumber






////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_SetValueString]
//
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_SetValueString(valueNameStr, strVal) {    
    var outputStr = "";
    var textNode;

    //LogEvent("MedNote_SetValueString. valueNameStr= " + valueNameStr);
    var valueEntry = g_AllLabValuesDeclaration[valueNameStr];    
    if (!valueEntry) {
        LogEvent("!!!!BUG!!!!!! MedNote_SetValueString. NULL valueEntry. valueNameStr= " + valueNameStr);
        return;
    }    

    valueEntry.intVal = -1;
    valueEntry.strVal = strVal;
} // MedNote_SetValueString








////////////////////////////////////////////////////////////////////////////////
//
// [GetLabValueStringForPlan]
//
// This returns a string that can be used in the text of a plan. If the lab value
// is not defined, then it returns some placeholder (like 'x') for a human
// to edit later.
////////////////////////////////////////////////////////////////////////////////
function 
GetLabValueStringForPlan(valueNameStr) {    
    //LogEvent("GetLabValue. valueNameStr= " + valueNameStr);
    var valueEntry = g_AllLabValuesDeclaration[valueNameStr];
    if (!valueEntry) {
        return("x");
    }

    if (valueEntry.intVal < 0) {
        return("x");
    } else {
        return(valueEntry.strVal);
    }
} // GetLabValueStringForPlan







////////////////////////////////////////////////////////////////////////////////
//
// [ComputeRiskOfESRD]
//
// Based on retrospective studies. See:
//    Tangri N, Stevens LA, Griffith J, et al. "A predictive model for progression of chronic kidney disease to kidney failure" JAMA. 2011;305(15)
//    Tangri N, Grams ME, Levey AS et al, "Multinational Assessment of Accuracy of Equations for Predicting Risk of Kidney Failure: A Meta-analysis", JAMA. 2016;315(2):1-11
//
// Some handy websites for checking my implementation.
// https://qxmd.com/calculate/calculator_125/kidney-failure-risk-equation-8-variable
// http://kidneyfailurerisk.com/
// http://kidneyfailurerisk.com/assets/js/kidney-app.js
////////////////////////////////////////////////////////////////////////////////
function
ComputeRiskOfESRD(patientAge, isMale, estimatedGFR, urineAlbumin, urineCr, serumAlbumin, serumCa, serumBicarb, serumPhos) {
    //LogEvent("ComputeRiskOfESRD");
    var maleValue;
    var baselineChanceOfHealthy;
    var riskExponent;
    var chanceHealthy;
    
    g_2YearESRDRisk = -1;
    g_5YearESRDRisk = -1;

    var urineAlbCrRatio = urineAlbumin / urineCr; // mg/g
    //LogEvent("urineAlbCrRatio=" + urineAlbCrRatio);    
    var lnUrineAlbCrRatio = Math.log(urineAlbCrRatio);
        
    if (isMale) {
        maleValue = 1;
    } else {
        maleValue = 0; 
    }

    ////////////////////////////////////////////
    // Calculate the Two-year risk. There are several formulae:
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
    // 4-Variable - North America - Two-year Risk.
    // 1 – 0.9751 ^ exp (-0.2201 × (age/10 – 7.036) + 0.2467 × (male – 0.5642) – 0.5567 × (eGFR/5 – 7.222) + 0.4510 × (logACR – 5.137))
    //
    // 4-Variable - Global - Two-year Risk
    // 1 – 0.9676 ^ exp (-0.2245 × (age/10 – 7.036) + 0.3212 × (male – 0.5642) – 0.4553 × (eGFR/5 – 7.222) + 0.4469 × (logACR – 5.137))
    g_SumofBetaXBar = 0;
    g_SumofBetaX = 0;
    g_TotalDelta = 0;
    
    // If we have values for albumin, phosphorous, bicarbonate, and calcium then we can compute the 8-variable form.
    if ((serumAlbumin > 0) && (serumPhos > 0) && (serumBicarb > 0) && (serumCa > 0)) {
        AddTermToESRDRiskScore("GFR", -0.4919, 7.222, estimatedGFR / 5);
        AddTermToESRDRiskScore("Sex", 0.1602, 0.5642, maleValue);
        AddTermToESRDRiskScore("Urine Albumin/Cr Ratio", 0.3364, 5.137, lnUrineAlbCrRatio);
        AddTermToESRDRiskScore("Age", -0.1992, 7.036, patientAge / 10);
        AddTermToESRDRiskScore("Albumin", -0.3441, 3.997, serumAlbumin);
        AddTermToESRDRiskScore("Phos", 0.2604, 3.916, serumPhos);
        AddTermToESRDRiskScore("Bicarb", -0.07354, 25.57, serumBicarb);
        AddTermToESRDRiskScore("Calcium", -0.2228, 9.355, serumCa);    
        // Thie is the empirically observed baseline survival rate in the data sets.
        // Note, that in these patients, there is a baseline chance of needing ESRD (around 2.5%) since this survival rate is less than 1.0.
        baselineChanceOfHealthy = 0.9757;
    } // Compute the Eight-variable form.
    else {
        AddTermToESRDRiskScore("Age", -0.2201, 7.036, patientAge / 10);
        AddTermToESRDRiskScore("Sex", 0.2467, 0.5642, maleValue);
        AddTermToESRDRiskScore("GFR", -0.5567, 7.222, estimatedGFR / 5);
        AddTermToESRDRiskScore("Urine Albumin/Cr Ratio", 0.4510, 5.137, lnUrineAlbCrRatio);

        // Thie is the empirically observed baseline survival rate in the data sets.
        // Note, that in these patients, there is a baseline chance of needing ESRD (around 2.5%) since this survival rate is less than 1.0.
        baselineChanceOfHealthy = 0.9751;
    } // Compute the Two-variable form

    // First get e**sum, which is the exponent we will use to compute the the chance of survival. 
    riskExponent = Math.exp(g_TotalDelta);
    // Now, compute the survival probability. This is the chance of NOT being ESRD. 
    chanceHealthy = Math.pow(baselineChanceOfHealthy, riskExponent);
    //LogEvent("chanceHealthy=" + chanceHealthy);
    // The risk of ESRD is 100% - chance of avoiding ESRD
    g_2YearESRDRisk = (1.0 - chanceHealthy);
    g_2YearESRDRisk = parseInt(g_2YearESRDRisk * 1000);
    g_2YearESRDRisk = parseFloat(g_2YearESRDRisk / 10);
    //LogEvent("2 year risk of ESRD=" + g_2YearESRDRisk);

    
    ////////////////////////////////////////////
    // Calculate the Five-year risk. There are several formulae:
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
    // Four-Variable - North America - Five-year Risk.
    // 1 – 0.8996 ^ exp (-0.2201 × (age/10 – 7.036) + 0.2467 × (male – 0.5642) – 0.5567 × (eGFR/5 – 7.222) + 0.4510 × (logACR – 5.137))
    //
    // Four-Variable - Global - Five-year Risk
    // 1 – 0.8762 ^ exp (-0.2245 × (age/10 – 7.036) + 0.3212 × (male – 0.5642) – 0.4553 × (eGFR/5 – 7.222) + 0.4469 × (logACR – 5.137))
    g_SumofBetaXBar = 0;
    g_SumofBetaX = 0;
    g_TotalDelta = 0;    
    // If we have values for albumin, phosphorous, bicarbonate, and calcium then we can compute the 8-variable form.
    if ((serumAlbumin > 0) && (serumPhos > 0) && (serumBicarb > 0) && (serumCa > 0)) {
        AddTermToESRDRiskScore("GFR", -0.4919, 7.222, estimatedGFR / 5);
        AddTermToESRDRiskScore("Sex", 0.1602, 0.5642, maleValue);
        AddTermToESRDRiskScore("Urine Albumin/Cr Ratio", 0.3364, 5.137, lnUrineAlbCrRatio);
        AddTermToESRDRiskScore("Age", -0.1992, 7.036, patientAge / 10);
        AddTermToESRDRiskScore("Albumin", -0.3441, 3.997, serumAlbumin);
        AddTermToESRDRiskScore("Phos", 0.2604, 3.916, serumPhos);
        AddTermToESRDRiskScore("Bicarb", -0.07354, 25.57, serumBicarb);
        AddTermToESRDRiskScore("Calcium", -0.2228, 9.355, serumCa);    
        // Thie is the empirically observed baseline survival rate in the data sets.
        // Note, that in these patients, there is a baseline chance of needing ESRD (around 9%) since this survival rate is less than 1.0.
        baselineChanceOfHealthy = 0.9096;
    } // Compute the Eight-variable form.
    else {
        AddTermToESRDRiskScore("GFR", -0.5567, 7.222, estimatedGFR / 5);
        AddTermToESRDRiskScore("Sex", 0.2467, 0.5642, maleValue);
        AddTermToESRDRiskScore("Urine Albumin/Cr Ratio", 0.4510, 5.137, lnUrineAlbCrRatio);
        AddTermToESRDRiskScore("Age", -0.2201, 7.036, patientAge / 10);   
        // Thie is the empirically observed baseline survival rate in the data sets.
        // Note, that in these patients, there is a baseline chance of needing ESRD (around 9%) since this survival rate is less than 1.0.
        baselineChanceOfHealthy = 0.8996;
    } // Compute the Two-variable form



    // First get e**sum, which is the exponent we will use to compute the the chance of survival. 
    riskExponent = Math.exp(g_TotalDelta);
    // Now, compute the survival probability. This is the chance of NOT being ESRD. 
    chanceHealthy = Math.pow(baselineChanceOfHealthy, riskExponent);
    //LogEvent("chanceHealthy=" + chanceHealthy);
    // The risk of ESRD is 100% - chance of avoiding ESRD
    g_5YearESRDRisk = (1.0 - chanceHealthy);
    g_5YearESRDRisk = parseInt(g_5YearESRDRisk * 1000);
    g_5YearESRDRisk = parseFloat(g_5YearESRDRisk / 10);
    //LogEvent("5 year risk of ESRD =" + g_5YearESRDRisk);
} // ComputeRiskOfESRD





////////////////////////////////////////////////////////////////////////////////
//
// [AddTermToESRDRiskScore]
// Called by ComputeRiskOfESRD for computing ESRD risk.
////////////////////////////////////////////////////////////////////////////////
function
AddTermToESRDRiskScore(labelStr, coefficient, xBar, xVal) {
    var betaXbar;
    var betaX;

    betaXbar = coefficient * xBar;
    betaX = coefficient * xVal;    
    //LogEvent(labelStr + ": xVal=" + xVal + ", coefficient=" + coefficient + ", xBar=" + xBar);
    //LogEvent("________________betaXbar=" + betaXbar + ", betaX=" + betaX);

    g_SumofBetaX = g_SumofBetaX + betaX;
    g_SumofBetaXBar = g_SumofBetaXBar + betaXbar;

    var currentDelta = coefficient * (xVal - xBar);
    g_TotalDelta = g_TotalDelta + currentDelta;
} // AddTermToESRDRiskScore






////////////////////////////////////////////////////////////////////////////////
//
// [GetLabValue]
//
////////////////////////////////////////////////////////////////////////////////
function 
GetLabValue(valueNameStr) {    
    //LogEvent("GetLabValue. valueNameStr= " + valueNameStr);
    //var valueEntry = g_AllLabValuesDeclaration[valueNameStr];
    //if (!valueEntry) {
    //    return(-1);
    //}
    //return(valueEntry.intVal);

    return(0);
} // GetLabValue






////////////////////////////////////////////////////////////////////////////////
//
// [NBQuant_ComputeMaddrey]
//
//
// Maddrey Discriminant Function
//
// Maddrey WC, Boitnott JK, Bedine MS, Weber FL, Mezey E, White RI (1978). 
// "Corticosteroid therapy of alcoholic hepatitis"
// Gastroenterology 75 (2): 193–9. PMID 352788
//
// Soultati AS, et. al. 
// Predicting utility of a model for end stage liver disease in alcoholic liver disease
// World J Gastroenterol 2006 July 07;12(25):4020-4025
////////////////////////////////////////////////////////////////////////////////
function 
NBQuant_ComputeMaddrey(PT, creatinine, Tbili) {
    if ((PT > 0) && (creatinine > 0) && (Tbili > 0)) {
        // The reference range for prothrombin time is 9.5-13.5 seconds.
        var ReferencePT = 11.5;
        
        var discriminantFunction = (4.6 * (PT - ReferencePT)) + Tbili;
        discriminantFunction = Math.round(discriminantFunction);
        return(discriminantFunction);
    }

    return(-1);
} // NBQuant_ComputeMaddrey






////////////////////////////////////////////////////////////////////////////////
//
// [NBQuant_ComputeChildPugh]
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
NBQuant_ComputeChildPugh(albumin, INR, Tbili, ascitesScore, encephalopathyScore) {
    if ((albumin > 0) && (Tbili > 0) && (INR > 0)) {
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

        var className = " (Class A)";
        if ((score >= 7) && (score <= 9)) {
            className = " (Class B)";
        } else if ((score >= 10)) {
            className = " (Class C)";
        }

        return(score + className);
    }

    return(null);
} // NBQuant_ComputeChildPugh






////////////////////////////////////////////////////////////////////////////////
//
// [WriteVancomycinPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteVancomycinPlan(allowPharmacy, seriousInfection) { 
    var dose;
    var minDose;
    var maxDose;
    var targetDoseRoundDown;
    var targetDoseRoundUp;
    var pStr = "Vancomycin (cover gram positives including MRSA";
    var explanationStr = "";
    //LogEvent("WriteVancomycinPlan. allowPharmacy=" + allowPharmacy);
    var weightInKg = GetLabValue("WeightInKg");    
    var patientAge = GetLabValue("Age");

    if ((weightInKg < 0) || (GetLabValue('CreatinineClearance') < 0) || (patientAge < 0)) {
        if (allowPharmacy) {
            pStr = pStr + ") - Pharmacy to dose";
        }
        WriteComment(pStr);
        return;
    }

    // Special case ESRD
    if (GetLabValue('CreatinineClearance') <= 30) {
        pStr = pStr + ", dose adjusted for CKD-V or ESRD since CrCl=" + GetLabValue('CreatinineClearance') + ") ";
         
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
    if (GetLabValue('CreatinineClearance') >= 100) {
        if ((patientAge < 50) && (seriousInfection)) {
            pStr = pStr + " Q8h";
            explanationStr = explanationStr + ", age=" + patientAge + "yo";
        } else {
            pStr = pStr + " Q12h";
        }
    } else if ((GetLabValue('CreatinineClearance') >= 50) && (GetLabValue('CreatinineClearance') < 100)) {
        pStr = pStr + " Q12h";
    } else if ((GetLabValue('CreatinineClearance') >= 30) && (GetLabValue('CreatinineClearance') < 50)) {
        pStr = pStr + " Q24h";
    }


    explanationStr = explanationStr + ", CrCl=" + GetLabValue('CreatinineClearance');  
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
WritePipTazoPlan(allowPharmacy) { 
    var pStr = "Pip/Tazo (cover gram negatives and anaerobes)";
        
    if ((GetLabValue('CreatinineClearance') > 0) && (GetLabValue('CreatinineClearance') <= 15)) {
        pStr = pStr + " 2.25g IV  Q8h (dose adjusted for CrCl=" + GetLabValue('CreatinineClearance') + ")";
    } else if ((GetLabValue('CreatinineClearance') > 15) && (GetLabValue('CreatinineClearance') <= 50)) {
        pStr = pStr + " 3.375g IV Q8h (dose adjusted for CrCl=" + GetLabValue('CreatinineClearance') + ")";
    } else {
        pStr = pStr + " 3.375g IV Q6h";
    }

    WriteAction(pStr);
} // WritePipTazoPlan







////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_ImportLabs]
//
////////////////////////////////////////////////////////////////////////////////
function
MedNote_ImportLabs(sourceEMRName) {
    for (var valueNameStr in g_AllLabValuesDeclaration) {
        //LogEvent("Found key: " + valueNameStr);
        //LogEvent("MedNote_InitOneQuantValueField. valueNameStr= " + valueNameStr);
        var valueEntry = g_AllLabValuesDeclaration[valueNameStr];
        if (!valueEntry) {
            continue;
        }
        valueEntry.intVal = -1;
        valueEntry.strVal = "";
    }

    //LogEvent("MedNote_ImportLabs");
    var scraperTextBox = document.getElementById("ScraperInput");
    var lineArray = scraperTextBox.value.split('\n');

    //LogEvent("MedNote_ImportLabs. sourceEMRName=" + sourceEMRName);
    if (sourceEMRName == "Epic") {
    } else if (sourceEMRName == "CPRS") {
        MedNote_ImportCPRSLabs(lineArray);
    } else if (sourceEMRName == "Cerner") {
    }
} // MedNote_ImportLabs

