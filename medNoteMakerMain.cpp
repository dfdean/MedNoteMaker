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
// This is the top-level module. It initiates the entire UI and also does all
// the layout of HTML elements in the UI. This layout is done initially when the 
// UI opens, but also may change the UI elements dynamically in response to user 
// actions.
/////////////////////////////////////////////////////////////////////////////


/////////////////////////
// HTML Elements
// These are the main windows that we show/hide to expose different subgroups of funtions and outputs.
var g_PlanDivElement = null;
var g_PlanTableElement = null;
var g_DiagnosisButtonsDivElement = null;
var g_HelpDivElement = null;
var g_OptionWindowDivElement = null;
var g_ImportWindowDivElement = null;
var g_TextEditWindowDivElement = null;
var g_RecommendationsDivElement = null;
var g_InpatientTableElement = null;
var g_ToolBarElement = null;

// Runtime state for printing a plan. Each plan section is in a different row
// table, along with its control panel. So, we keep track of the current row.
var g_CurrentPlanSectionTextElement = null;
var g_WritingPlanSection = false;
var g_CurrentSectionHasAssessmentSubHeader = false;
var g_CurrentSectionHasPlanSubHeader = false;
var g_RedrawExistingPlanSection = false;

var PLAN_TEXT_BOX_WIDTH         = "550px";
var PLAN_CONTROL_PANEL_WIDTH    = "400px";

///////////////////
// Browser options for making html NON-selected in a copy-and-paste.
// I use this so the control panels are not included in a copy/paste.
//   -webkit-touch-callout: none; /* iOS Safari */
//   -webkit-user-select: none; /* Safari */
//   -khtml-user-select: none; /* Konqueror HTML */
//   -moz-user-select: none; /* Firefox */
//   -ms-user-select: none; /* Internet Explorer/Edge */
//   user-select: none; /* Non-prefixed version, currently supported by Chrome and Opera */
var NO_SELECT_STYLE = "-webkit-touch-callout: none; -webkit-user-select: none; -khtml-user-select: none; -moz-user-select: none; -ms-user-select: none;  user-select: none;";
var CONTROL_PANEL_BACKGROUND_STYLE = "background-color:#F0F0F0; border:4px outset; box-shadow:6px 6px #888888;";


////////////////////////////////////
// User Options
var g_IsPrimary = true;
var g_EmitBoilerplate = true;
var g_CollectedSystemInfo = false;

// PLAN FORMAT CONSTANTS
var PROBLEM_SECTION_HEADER_PREFIX = "#) ";
var PROBLEM_SECTION_HEADER_SUFFIX = " ";

var ASSESSMENT_SUBHEADER_STRING = "Assessment";
var ACTION_SUBHEADER_STRING = "Plan";

var SUBSECTION_SUBHEADER_OPEN_PREFIX = "/";
var SUBSECTION_SUBHEADER_CLOSE_SUFFIX = ":";

var PLAN_ACTION_TEXT_LINE_PREFIX = "- "
var PLAN_COMMENT_TEXT_LINE_PREFIX = ""

var PROBLEM_ASSESSMENT_PLAN_SUBSECTIONS = 0;
var PROBLEM_ONLY_PLAN_SUBSECTIONS       = 1;
var PROBLEM_NO_SUBSECTIONS              = 2;
var g_ProblemLayout = PROBLEM_ONLY_PLAN_SUBSECTIONS;

var g_TinyPlanStringList = []

var g_ImportCatalog;



////////////////////////////////////////////////////////////////////////////////
//
// [StartMedNoteMaker]
//
// This is called by the browser to initialize the entire UI.
////////////////////////////////////////////////////////////////////////////////
function 
StartMedNoteMaker() {
    //LogEvent("StartMedNoteMaker");

    // Load the catalog
    g_ImportCatalog = document.getElementById("ImportControlPanelCatalog");
    var newImportCatalog = document.getElementById("NewControlPanelCatalog");
    var importedBody = Util_GetChildNode(g_ImportCatalog, "body");
    var newCtlPanel = Util_GetDescendantNodeByID(g_ImportCatalog, "NewControlPanelCatalog");

    // These are the main windows that we show/hide to expose different subgroups of funtions and outputs.
    g_PlanDivElement = document.getElementById("NotePlanWindow");
    g_PlanTableElement = document.getElementById("PlanTable");
    g_DiagnosisButtonsDivElement = document.getElementById("DiagnosisButtons");
    g_HelpDivElement = document.getElementById("HelpWindow");
    g_OptionWindowDivElement = document.getElementById("OptionWindow");
    g_ImportWindowDivElement = document.getElementById("ImportWindow");
    g_TextEditWindowDivElement = document.getElementById("TextEditWindow");

    // Get some useful elements from the HTML; these will be used for input and output.
    g_InpatientTableElement = document.getElementById("InPatientTable");
    g_ToolBarElement = document.getElementById("ToolBar");
    //LogEvent("StartMedNoteMaker. Got html elements");

    if (g_InpatientTableElement) {
        g_InpatientTableElement.style.display = "inline";
    }    
    if (g_HelpDivElement) {
        g_HelpDivElement.style.display = "None";
    }    

    ShowSubWindow("HelpButtonID", "Loading pages...", false);

    // Initialize the global state.
    // This goes in ORDER of the order in which problems typically appear in the plan.
    // So, put the highest priority items first, and the lowest priority items last.

    ////////////////////////////////////
    // Header and Footer
    //LogEvent("StartMedNoteMaker. Initialized Plan states 3%");
    InitPlanState("PlanHeader", WritePlanHeader);
    InitPlanState("PlanFooter", WritePlanFooter);

    ////////////////////////////////////
    // Chief Complaints
    //LogEvent("StartMedNoteMaker. Initialized Plan states 4%");
    InitPlanState("NSTEMIPlan", WriteChestPainPlan);
    InitPlanState("DKAPlan", WriteDKAPlan);
    InitPlanState("GIBleedPlan", WriteGIBleedPlan);
    InitPlanState("SepsisPlan", WriteSepsisPlan);
    InitPlanState("StrokePlan", WriteStrokePlan);  
    InitPlanState("DICPlan", WriteDICPlan);
    InitPlanState("PEDVTPlan", WritePEDVTPlan);
    InitPlanState("CovidPlan", WriteCovidPlan);
    InitPlanState("EncephalopathyPlan", WriteEncephalopathyPlan);
    InitPlanState("SyncopePlan", WriteSyncopePlan);
    InitPlanState("OncologyPlan", WriteOncologyPlan);
    InitPlanState("HepatitisPlan", WriteHepatitisPlan);
    InitPlanState("PancPlan", WritePancreatitisPlan);
    InitPlanState("GISymptomsPlan", WriteGISymptomsPlan);
    InitPlanState("PneumoniaPlan", WritePneumoniaPlan);
    InitPlanState("CADPlan", WriteCADPlan);
    InitPlanState("CHFPlan", WriteCHFPlan);
    InitPlanState("COPDPlan", WriteCOPDPlan);  
    InitPlanState("PreopPlan", WritePreOpPlan);
    
    ////////////////////////////////////
    // Complex Comorbidities 
    InitPlanState("CirrhosisPlan", WriteCirrhosisPlan);
    InitPlanState("HemoDialysisPlan", WriteHemodialysisPlan);
    InitPlanState("RenalTransplantPlan", WriteRenalTransplantPlan);
        
    ////////////////////////////////////
    // Renal
    InitPlanState("AKIPlan", PrintAKIPlan);
    InitPlanState("CKDPlan", PrintCKDPlan);
    InitPlanState("NephroticPlan", WriteNephroticPlan);
    InitPlanState("IVContrastPlan", WriteIVContrastPlan);
    InitPlanState("DysphagiaPlan", WriteDysphagiaPlan);
    InitPlanState("MBDPlan", WriteMBDPlan);
    InitPlanState("HTNPlan", WriteHTNPlan);    
    InitPlanState("AcidBasePlan", WriteAcidBasePlan);
    InitPlanState("ParathyroidectomyPlan", WriteParathyroidectomyPlan);
            
    ////////////////////////////////////
    // Non-Complex Comorbidities
    InitPlanState("DiabetesPlan", PrintDiabetesPlan);
    InitPlanState("AsthmaPlan", WriteAsthmaPlan);
    InitPlanState("OSAPlan", WriteOSAPlan);
    InitPlanState("AFibPlan", WriteAFibPlan);  
    
    ////////////////////////////////////
    // PreExisting
    InitPlanState("PalliativePlan", WritePalliativePlan);  
    InitPlanState("HepCPlan", WriteHepatitisCPlan);
    InitPlanState("LegFracturePlan", WriteLegFracturePlan);
    InitPlanState("NephrolithiasisPlan", WriteNephrolithiasisPlan);
    
    ////////////////////////////////////
    // Single-Line Capable Plans
    InitPlanState("AnemiaPlan", WriteAnemiaPlan);
    InitPlanState("HypokalemiaPlan", WriteHypokalemiaPlan);

    InitPlanState("HyperkalemiaPlan", WriteHypERkalemiaPlan);
    InitPlanState("HyponatremiaPlan", WriteHyponatremiaPlan);
    InitPlanState("HypERnatremiaPlan", PrintHyperNatremiaPlan);
    InitPlanState("HypoPhosPlan", WriteHypoPhosPlan);
    InitPlanState("HypoCalcemiaPlan", WriteHypoCalcemiaPlan);
    InitPlanState("HypERCalcemiaPlan", WriteHypERCalcemiaPlan);
    InitPlanState("HypomagnesemiaPlan", WriteHypomagnesemiaPlan);
    InitPlanState("VitDPlan", WriteVitaminDPlan);

    InitPlanState("EtOHPlan", WriteEtOHPlan);
    InitPlanState("IllicitDrugsPlan", WriteIllicitDrugsPlan);
    InitPlanState("HypothyroidPlan", WriteHypothyroidPlan);
    InitPlanState("GoutPlan", WriteGoutPlan);
    InitPlanState("BPHPlan", WriteBPHPlan); 
    InitPlanState("DepressionPlan", WriteDepressionPlan);
    InitPlanState("GERDPlan", WriteGERDPlan);
    InitPlanState("PressureUlcersPlan", WritePressureUlcersPlan);
    InitPlanState("MalnutritionPlan", WriteMalnutritionPlan);
    InitPlanState("ObesityPlan", WriteObesityPlan);
    InitPlanState("WeaknessPlan", WriteWeaknessPlan);
    InitPlanState("TobaccoPlan", WriteTobaccoPlan);
    InitPlanState("MigrainesPlan", WriteMigrainePlan);

    ////////////////////////////////////
    // Footer Plans
    InitPlanState("PreventionPlan", WritePreventionPlan);
    InitPlanState("BillingPlan", WriteBillingPlan);
   
    MedNote_OnCloseChildWindow(null);

    //LogEvent("StartMedNoteMaker. Initialized plan states");
    WritePlanBody();
} // StartMedNoteMaker








////////////////////////////////////////////////////////////////////////////////
//
// [OnPlanButton]
//
// This is called when the user clicks a button in the GUI.
// button.id is the name of the plan state.
////////////////////////////////////////////////////////////////////////////////
function 
OnPlanButton(button) {
    //LogEvent("OnPlanButton. button.id=" + button.id);

    var valueEntry = g_AllPlansDeclaration[button.id];
    if (!valueEntry) {
        LogEvent("OnPlanButton. null valueEntry");
        return;
    }
    //LogEvent("OnPlanButton. valueEntry=" + valueEntry);
    if (!(valueEntry.planSelectStatusHTMLElement)) {
        LogEvent("OnPlanButton. null valueEntry.planSelectStatusHTMLElement");
        return;
    }

    // The HTML state is visible, so that is considered the final "truth".
    // There are cases where the runtime isSelectedFlag and the html can get out of sync, which are bugs and will be fixed.
    if (valueEntry.planSelectStatusHTMLElement.className.toUpperCase() == "PLANOFFSTYLE") {
        //LogEvent("OnPlanButton. Turn the option on. button.id=" + button.id);
        valueEntry.isSelected = 1;
        valueEntry.planSelectStatusHTMLElement.className = "planOnStyle";
    } else {
        //LogEvent("OnPlanButton. Turn the option off. button.id=" + button.id);
        valueEntry.isSelected = 0;
        valueEntry.planSelectStatusHTMLElement.className = "planOffStyle";
        // Hide any active control panels.
        valueEntry.activeControlPanel = null;
    }
    
    WritePlanBody();
    //LogEvent("OnPlanButton done");
} // OnPlanButton






////////////////////////////////////////////////////////////////////////////////
//
// [ResetNotebuilderState]
//
////////////////////////////////////////////////////////////////////////////////
function 
ResetNotebuilderState() {
    var index;

    for (var planName in g_AllPlansDeclaration) {
        var valueEntry = g_AllPlansDeclaration[planName];

        if (valueEntry) {
            valueEntry.isSelected = 0;
            // Hide any active control panels.
            valueEntry.activeControlPanel = null;

            if (valueEntry.planSelectStatusHTMLElement) {
                valueEntry.planSelectStatusHTMLElement.className = "planOffStyle";
            }

            if (valueEntry.planTextHTMLElement) {
                Util_RemoveAllChildNodes(valueEntry.planTextHTMLElement);
            }
        } // if (valueEntry)
    } // for (var planName in g_AllPlansDeclaration)

    WritePlanBody();
} // ResetNotebuilderState






////////////////////////////////////////////////////////////////////////////////
//
// [OnPlanTypeButton]
//
////////////////////////////////////////////////////////////////////////////////
function 
OnPlanTypeButton(button) {
    //LogEvent("OnPlanTypeButton. button.id = " + button.id);
    
    ////////////////////////////////////
    if (button.id == "FullPlanOption") {
        if  (button.value == "Full-->Plan Only") {
            button.className="OptionBtnStyle";
            button.value="Plan Only-->Full";
            g_EmitBoilerplate = false;
        } else {
            button.className="optionOnStyle";
            button.value="Full-->Plan Only";
            g_EmitBoilerplate = true;
        }        
    }

    WritePlanBody();
} // OnPlanTypeButton






////////////////////////////////////////////////////////////////////////////////
//
// [WritePlanHeader]
//
////////////////////////////////////////////////////////////////////////////////
function 
WritePlanHeader() {
    //LogEvent("WritePlanHeader");
    var str;
    var optionNameList;
    var activeControlPanel = null;

    MedNote_StartNewPlanSection(null, "PlanHeader");

    WriteTextLine("Chief Complaint: ");
    WriteTextLine("History of Present Illness:");
    WriteTextLine("");
    WriteTextLine("");

    // Get the control panel. 
    // This was set up by the call to MedNote_StartNewPlanSection.
    planConfigState = g_AllPlansDeclaration['PlanHeader'];
    activeControlPanel = planConfigState.activeControlPanel;
    if (!activeControlPanel) {
        LogEvent("WritePlanHeader. activeControlPanel is null");
        return;
    }

    ///////////////////////////////////////
    // REVIEW OF SYSTEMS:
    //    
    //A problem pertinent ROS inquires about the system directly related to the problem(s) identified in the HPI.
    //An extended ROS requires two to nine systems should be documented.
    //A complete ROS inquires about at least ten organ systems must be reviewed.
    if (MedNote_GetCPOptionBool("RoSCannotAssessOption")) {
        str = "Review of Systems: " + MedNote_GetCPOptionValue("RoSCannotAssessOption");
        WriteTextLine(str);
    } else {
        WriteTextLine("Review of Systems:");
        WriteCommentIfSelected(activeControlPanel, 'RoS14PointOption');

        optionNameList = [ "RosFeverOption", "RosWeaknessOption", "RosWeightLossOption", "RosAppetiteOption"];
        WriteListOfSelectedValues(activeControlPanel, "Constitutional: ", false, "", optionNameList, "")

        optionNameList = [ "RosDryEyesOption", "RosBlurredVisionOption", "RosVisionChangesOption"];
        WriteListOfSelectedValues(activeControlPanel, "Eyes: ", false, "", optionNameList, "")

        optionNameList = [ "RosHearingOption", "RosMouthOption", "RosNoseOption"];
        WriteListOfSelectedValues(activeControlPanel, "HENT: ", false, "", optionNameList, "")

        optionNameList = [ "RosChestPainOption", "RosPalpitationsOption", "RosEdemaOption"];
        WriteListOfSelectedValues(activeControlPanel, "Cardiovascular: ", false, "", optionNameList, "")

        optionNameList = [ "RosDyspneaOption", "RosCoughOption", "RosDoEOption", "RosSputumOption"];
        WriteListOfSelectedValues(activeControlPanel, "Respiratory: ", false, "", optionNameList, "")

        optionNameList = [ "RosNauseaOption", "RosVomitingOption", "RosDiarrheaOption", "RosConstipationOption", "RosAbdomPainOption"];
        WriteListOfSelectedValues(activeControlPanel, "Gastrointestinal: ", false, "", optionNameList, "")

        optionNameList = [ "RosPartialVoidOption", "RosWeakStreamOption", "RosUrinaryHesitancyOption", "RosDysuriaOption"]; 
        WriteListOfSelectedValues(activeControlPanel, "Genitourinary: ", false, "", optionNameList, "")

        optionNameList = [ "RosBackPainOption", "RosShoulderPainOption", "RosHipPainOption", "RosKneePainOption"];
        WriteListOfSelectedValues(activeControlPanel, "Musculoskeletal: ", false, "", optionNameList, "")

        optionNameList = [ "RosRashOption", "RosLesionOption", "RosBruisingOption"];
        WriteListOfSelectedValues(activeControlPanel, "Integumentary: ", false, "", optionNameList, "")

        optionNameList = [ "RosHeadachesOption", "RosDizzinessOption", "RosNumbnessOption", "RosBurningOption"];
        WriteListOfSelectedValues(activeControlPanel, "Neurological: ", false, "", optionNameList, "")

        optionNameList = [ "RosDepressionOption", "RosAnxietyOption", "RosHallucinationOption"];
        WriteListOfSelectedValues(activeControlPanel, "Psychiatric: ", false, "", optionNameList, "")

        optionNameList = [ "RosMelenaOption", "RosHematocheziaOption", "RosHematemesisOption", "RosCoffeeGroundOption", "RosHematuriaOption"];
        WriteListOfSelectedValues(activeControlPanel, "Hematologic: ", false, "", optionNameList, "")

        optionNameList = [ "RosHeatOption", "RosColdOption", "RosThirstOption"];
        WriteListOfSelectedValues(activeControlPanel, "Endocrine: ", false, "", optionNameList, "")

        optionNameList = [ "RosAllergiesOption", "RosInfectionsOption"];
        WriteListOfSelectedValues(activeControlPanel, "Allergic: ", false, "", optionNameList, "")

        WriteTextLine("All other review of systems are negative.");
    } // (!(MedNote_GetCPOptionBool("RoSCannotAssessOption")))
    WriteTextLine("");


    //////////////////////////
    // HISTORIES:
    // Past Medical History
    optionNameList = ["PMHxHypertension", "PMHxDiabetes", "PMHxHeartFailure", "PMHxCOPD", "PMHxCirrhosis",
                        "PMHxCoronaryArteryDisease", "PMHxCKD", "PMHxStroke", "PMHxHypoThyroid", "PMHxAnxiety",
                        "PMHxAFib", "PMHxDepression", "PMHxTobacco", "PMHxEtOH"];
    WriteListOfSelectedMedHistoryItems(activeControlPanel, "Medical History:", optionNameList);
    WriteTextLine("");

    // Past Surgical History
    optionNameList = ["PSHxCholecystectomy", "PSHxArthroscopy", "PSHxAppendectomy", "PSHxHysterectomy", 
                        "PSHxTonsillectomy", "PSHxCABG", "PSHxCSection", "PSHxBTL"];
    WriteListOfSelectedMedHistoryItems(activeControlPanel, "Surgical History:", optionNameList);
    WriteTextLine("");

    // Past Social History
    WriteTextLine("Social History:");
    optionNameList = ["PHxTobacco"];
    WriteHistoryItem(activeControlPanel, "Tobacco: ", optionNameList, "None");
    optionNameList = ["PHxAlcohol"];
    WriteHistoryItem(activeControlPanel, "Alcohol: ", optionNameList, "None");
    optionNameList = ["PHxDrugs"];
    WriteHistoryItem(activeControlPanel, "Illicits: ", optionNameList, "None");
    WriteTextLine("");

    // Family Medical History
    WriteTextLine("Family History:");
    WriteTextLine("Reviewed and non-contributory");
    optionNameList = ["FHxMotherDM", "FHxMotherHTN", "FHxMotherCAD", "FHxMotherCancer", "FHxMotherCOPD", "FHxMotherNone"];
    WriteHistoryItem(activeControlPanel, "Mother: ", optionNameList, "");
    optionNameList = ["FHxFatherDM", "FHxFatherHTN", "FHxFatherCAD", "FHxFatherCancer", "FHxFatherCOPD", "FHxFatherNone"];
    WriteHistoryItem(activeControlPanel, "Father: ", optionNameList, "");
    optionNameList = ["FHxSiblingsDM", "FHxSiblingsHTN", "FHxSiblingsCAD", "FHxSiblingsCancer"];
    WriteHistoryItem(activeControlPanel, "Siblings: ", optionNameList, "");
    WriteTextLine("");

    // Home Medications
    optionNameList = ["PHxMedsMetoprolol", "PHxMedsLisinopril", "PHxMedsLosartan", "PHxMedsAmlodipine", "PHxMedsHCTZ", 
                        "PHxMedsPantoprazole", "PHxMedsOxycodone", "PHxMedsCoreg", "PHxMedsFurosemide", "PHxMedsAsa", 
                        "PHxMedsAtorvastatin", "PHxMedsApixaban", "PHxMedsClopidogrel", "PHxMedsAlbuterol", 
                        "PHxMedsFluticSalm", "PHxMedsTiotropium", "PHxMedsMontelukast", "PHxMedsTamsulosin", 
                        "PHxMedsMetformin"];
    WriteListOfSelectedMedHistoryItems(activeControlPanel, "Home Medications:", optionNameList);
    WriteTextLine("");

    // Allergies
    optionNameList = ["PHxAllergyPenicillins", "PHxAllergySulfa"];
    WriteHistoryItem(activeControlPanel, "Allergies: ", optionNameList, "No Known Drug Allergies");
    WriteTextLine("");

    ////////////////////////
    // PHYSICAL EXAM:
    WriteTextLine("OBJECTIVE");
    //WriteTextLine("Vitals: T=, HR=, BP=/, SpO2=100% on RA, Wt=");
    WriteTextLine("Physical Exam:");
    optionNameList = [ "AOx3Option", "NADOption", "NourishedOption", "GCSEyesOption", "GCSVerbalOption", "GCSMotorOption"];
    WriteListOfSelectedValues(activeControlPanel, "General: ", false, "", optionNameList, "")

    optionNameList = [ "OPCOption", "MucosaMoistOption", "IctericOption"];
    WriteListOfSelectedValues(activeControlPanel, "HEENT: ", false, "", optionNameList, "")

    optionNameList = [ "SuppleOption", "ThyromegalyOption", "TrachOption"];
    WriteListOfSelectedValues(activeControlPanel, "Neck: ", false, "", optionNameList, "")

    optionNameList = [ "HROption", "MurmurOption", "MurmurIncrease", "JVDOption", "EdemaOption", "PulsesOption"];
    WriteListOfSelectedValues(activeControlPanel, "Cardiovascular: ", false, "", optionNameList, "")

    optionNameList = [ "CBTAOption", "RalesOption", "WheezesOption", "LaboredOption"];
    WriteListOfSelectedValues(activeControlPanel, "Pulmonary: ", false, "", optionNameList, "")

    optionNameList = [ "BowelSoundsOption", "SoftOption", "NTOption", "NDOption", "ReboundOption", "GTubeOption"];
    WriteListOfSelectedValues(activeControlPanel, "Abdom: ", false, "", optionNameList, "")

    optionNameList = [ "RoMArmsOption", "RoMKneesOption", "RoMHipsOption", "AmputationOption", "WoundVacOption"];
    WriteListOfSelectedValues(activeControlPanel, "Muskuloskeletal: ", false, "", optionNameList, "")

    optionNameList = [ "AsterixisOption", "CNIntactOption", "5/5BUEOption", "5/5BLEOption", "BabinskiOption"];
    WriteListOfSelectedValues(activeControlPanel, "Neurologic: ", false, "", optionNameList, "")

    optionNameList = [ "RashesOption", "LesionsOption", "UlcersOption"];
    WriteListOfSelectedValues(activeControlPanel, "Dermatologic: ", false, "", optionNameList, "")

    optionNameList = [ "AccessTypeOption", "AccessBruitOption", "AccessThrillOption", "AccessAugmentationOption"];
    WriteListOfSelectedValues(activeControlPanel, "Access: ", false, "", optionNameList, "")

    WriteTextLine("");
    WriteTextLine("ASSESSMENT/PLAN");
    //LogEvent("FINISH WritePlanHeader");
} // WritePlanHeader






////////////////////////////////////////////////////////////////////////////////
//
// [WritePlanFooter]
//
////////////////////////////////////////////////////////////////////////////////
function 
WritePlanFooter() {
    var str;
    var modifierStr;
    var activeControlPanel = null;
    var verbosityLevel = "verbose";
    var reasonOptionStr;
    var reasonList;
    var optionNameList;

    MedNote_StartNewPlanSection(null, "PlanFooter");

    // Get the control panel. 
    // This was set up by the call to MedNote_StartNewPlanSection.
    planConfigState = g_AllPlansDeclaration['PlanFooter'];
    activeControlPanel = planConfigState.activeControlPanel;
    if (!activeControlPanel) {
        LogEvent("WritePlanFooter. activeControlPanel is null");
        return;
    }

    // Collect all of the 1-liner tiny plans. This will not print, instead
    // it will call PrintSingleLinePlanAtEnd, which will append the text to
    // the g_TinyPlanStringList.
    g_TinyPlanStringList = []
    for (var planName in g_AllPlansDeclaration) {
        var valueEntry = g_AllPlansDeclaration[planName];
        if ((valueEntry.isSelected) && (valueEntry.PrintFunction) && (valueEntry.PrintSingleLine >= 1)) {
            //LogEvent("WritePlanFooter write plan: " + planName);
            valueEntry.PrintFunction();
        }
        if ((valueEntry.isSelected) && (valueEntry.SingleLinePlans.length > 0)) {
            for (var index = 0; index < valueEntry.SingleLinePlans.length; index++) {
                g_TinyPlanStringList.push(valueEntry.SingleLinePlans[index])
            }
        }
    }

    // Now, write all single-line plans at the end
    for (var index = 0; index < g_TinyPlanStringList.length; index++) {
        WriteComment(g_TinyPlanStringList[index]);
    }


    if (g_IsPrimary) {
        str = MedNote_GetCPOptionValue("DietOption");
        if ("" != str) {
            WriteTextLine("");
            WriteTextLine(PROBLEM_SECTION_HEADER_PREFIX + "Fluids/Nutrition" + PROBLEM_SECTION_HEADER_SUFFIX);
            WriteComment(PLAN_ACTION_TEXT_LINE_PREFIX + str);
        }

        str = MedNote_GetCPOptionValue("DVTProphylaxisOption");
        if ("" != str) {
            WriteTextLine("");
            WriteTextLine(PROBLEM_SECTION_HEADER_PREFIX + "Prophylaxis" + PROBLEM_SECTION_HEADER_SUFFIX);
            WriteComment(PLAN_ACTION_TEXT_LINE_PREFIX + str);
        }

        if (MedNote_GetCPOptionBool("DispoDisplayDischargePlanning")) {
            WriteTextLine("");
            WriteTextLine(PROBLEM_SECTION_HEADER_PREFIX + "Discharge Planning" + PROBLEM_SECTION_HEADER_SUFFIX);
            /////////////////////////
            // PT Recommendations
            str = MedNote_GetCPOptionValue("DispoPTRecsOption");
            if ((str != null) && (str != "")) {
                modifierStr = MedNote_GetCPOptionValue("DispoPatientAgreeOption");
                if ((modifierStr != null) && (modifierStr != "")) {
                    str = str + " and " + modifierStr;
                }
                WriteComment("PT recommends: " + str);
            }
            /////////////////////////
            // Build up a list of reasons why the patient cannot be discharged.
            reasonList = "";
            reasonOptionStr = MedNote_GetCPOptionValue("DispoInsuranceOption");
            if ((reasonOptionStr != null) && (reasonOptionStr != "")) {
                if (reasonList != "") {
                    reasonList = reasonList + ", ";
                }
                reasonList = reasonList + reasonOptionStr;
            }
            reasonOptionStr = MedNote_GetCPOptionValue("DispoIVAbxOption");
            if ((reasonOptionStr != null) && (reasonOptionStr != "")) {
                if (reasonList != "") {
                    reasonList = reasonList + ", ";
                }
                reasonList = reasonList + reasonOptionStr;
            }
            reasonOptionStr = MedNote_GetCPOptionValue("DispoDysphagiaOption");
            if ((reasonOptionStr != null) && (reasonOptionStr != "")) {
                if (reasonList != "") {
                    reasonList = reasonList + ", ";
                }
                reasonList = reasonList + reasonOptionStr;
            }
            reasonOptionStr = MedNote_GetCPOptionValue("DispoAMSOption");
            if ((reasonOptionStr != null) && (reasonOptionStr != "")) {
                if (reasonList != "") {
                    reasonList = reasonList + ", ";
                }
                reasonList = reasonList + reasonOptionStr;
            }
            reasonOptionStr = MedNote_GetCPOptionValue("DispoMedicalOption");
            if ((reasonOptionStr != null) && (reasonOptionStr != "")) {
                if (reasonList != "") {
                    reasonList = reasonList + ", ";
                }
                reasonList = reasonList + reasonOptionStr;
            }
            if ("" != reasonList) {
                WriteComment("Barriers to discharge: " + reasonList);
            }
        
            /////////////////////////
            // PT actions
            WriteCommentIfSelected(activeControlPanel, 'DispoPTOption');

            /////////////////////////
            // Followup appointments
            var actionNameList = [ "DispoClinicPCPOption", "DischargeFollowUpID", "DischargeFollowUpGI",
                                    "DischargeFollowUpRenal", "DischargeFollowUpCards", "DischargeFollowUpOnc",
                                    "DischargeFollowUpNeuro", "DischargeFollowUpSurgery",
                                    "DischargeFollowUpEndocrine"];
            WriteListOfSubActions("Followup appointments after discharge:", actionNameList);

            /////////////////////////
            // Equipment
            WriteCommentIfSelected(activeControlPanel, 'WeaknessHospBed1Option');
            WriteCommentIfSelected(activeControlPanel, 'WeaknessHospBed2Option');
            WriteCommentIfSelected(activeControlPanel, 'WeaknessWheelchairOption');
    
            /////////////////////////
            // Discharge Meds
            WriteCommentIfSelected(activeControlPanel, 'DispoPneumovaxOption');
            WriteCommentIfSelected(activeControlPanel, 'DispoHAVVaccineOption');
            WriteCommentIfSelected(activeControlPanel, 'DispoHBVVaccineOption');
            WriteCommentIfSelected(activeControlPanel, 'DispoNarcanOption');
        } // Discharge Planning


        /////////////////////////
        // Code status Section
        str = MedNote_GetCPOptionValue("CodeStatusOption");
        if ("" != str) {
            WriteTextLine("");
            WriteTextLine(PROBLEM_SECTION_HEADER_PREFIX + "Code Status" + PROBLEM_SECTION_HEADER_SUFFIX);
            WriteTextLine(str);
        }
    } // if (g_IsPrimary)

    WriteTextLine("");
} // WritePlanFooter







////////////////////////////////////////////////////////////////////////////////
//
// [WritePlanBody]
//
////////////////////////////////////////////////////////////////////////////////
function 
WritePlanBody() {
    //LogEvent("WritePlanBody");
    //var oneLinerPlanList = [];
    var index;

    // Clear the output and prepare to write a new plan.
    if (g_PlanTableElement) {
        Util_RemoveAllChildNodes(g_PlanTableElement);
    }  
    if (g_RecommendationsDivElement) {
        Util_RemoveAllChildNodes(g_RecommendationsDivElement);
    }          
    g_CurrentPlanSectionTextElement = null;

    if (g_EmitBoilerplate) {
        WritePlanHeader();
    }  

    g_WritingPlanSection = true;
    for (var planName in g_AllPlansDeclaration) {
        var valueEntry = g_AllPlansDeclaration[planName];
        if ((valueEntry.isSelected) && (valueEntry.PrintFunction) && (planName != "BillingPlan")) {
            //LogEvent("Body write plan: " + planName);
            if (valueEntry.PrintSingleLine >= 1) {
                // If this is a tiny plan, then the control panel should show up in place, but
                // The plan body is empty - it will appear as a comment/action in the footer.
                // So, to just create the control panel, call startNewPlanSection.
                MedNote_StartNewPlanSection("", planName);
            } else {
                // Otherwise, call the print function, which will in turn call MedNote_StartNewPlanSection.
                // We let the print function make the call because it will pass the appropriate plan title.
                valueEntry.SingleLinePlans = [];
                valueEntry.PrintFunction();
            }
        }
    }
    g_WritingPlanSection = false;

    //if (g_EmitBoilerplate) {
    WritePlanFooter();
    WriteTextLine(" ");
    WriteTextLine(" ");
        
    var valueEntry = g_AllPlansDeclaration["BillingPlan"];
    if ((valueEntry.isSelected) && (valueEntry.PrintFunction)) {
        valueEntry.SingleLinePlans = [];
        valueEntry.PrintFunction();
    }

    for (var planName in g_AllPlansDeclaration) {
        var valueEntry = g_AllPlansDeclaration[planName];
        if ((valueEntry) && (valueEntry.isSelected == 2)) {
            valueEntry.isSelected = 0;
        }
    }
} // WritePlanBody






////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_StartNewPlanSection]
//
// Add a new section to the plan. This does several things:
//   - Make a new row in the plan table
//   - Make 2 new cells in this row, for (i) the text of the plan, (ii) the section control panel
//   - Populate the initial plan text
//   - TO DO: Add generic control buttons to show or hide the control panel.
//   - Find the control panel tamplate HTML
//   - Populate the control panel html
// 
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_StartNewPlanSection(problemName, configStateID) {
    //LogEvent("MedNote_StartNewPlanSection. problemName=" + problemName + ", g_RedrawExistingPlanSection=" + g_RedrawExistingPlanSection);
    //LogEvent("MedNote_StartNewPlanSection. configStateID=" + configStateID);
    var textNode;
    var planConfigState = null;
    var controlPanelTableCell = null;

    // Reset the global state for this plan section.
    g_CurrentSectionHasAssessmentSubHeader = false;
    g_CurrentSectionHasPlanSubHeader = false;
    if (configStateID) {
        planConfigState = g_AllPlansDeclaration[configStateID];
    }
    if (planConfigState) {
        g_CurrentPlanSectionTextElement = planConfigState.planTextHTMLElement;
        // Don't write the "Assessment" and "Plan" subsections for the header or footer.
        // These are normally initialized to false in the MedNote_StartNewPlanSection()
        // function which is called from planSectionEntry.PrintFunction();
        if (("PlanHeader" == planConfigState.planSelectStatusHTMLElementID)
                || ("PlanFooter" == planConfigState.planSelectStatusHTMLElementID)) {
            g_CurrentSectionHasAssessmentSubHeader = true;
            g_CurrentSectionHasPlanSubHeader = true;
        }
    } else {
        LogEvent("MedNote_StartNewPlanSection. NULL planConfigState. configStateID=" + configStateID);
    }
    //LogEvent("MedNote_StartNewPlanSection. configStateID = " + configStateID + ", planConfigState.activeControlPanel = " + planConfigState.activeControlPanel);


    ////////////////////////////////////////
    // Make a new table row for this section. This allows items in the left and right
    // columns to scroll up and down together and always be vertically aligned.
    //
    // We do NOT do this if we are just regenerating a single plan section. In that
    // case, the row already exists, because it is used to hold our place in the plan
    // body between when we remove the old text and insert the newly regenerated text.
    if (!g_RedrawExistingPlanSection) {   
        var newRow = document.createElement("TR");
        g_PlanTableElement.appendChild(newRow);

        // Make an entry for the plan text.
        g_CurrentPlanSectionTextElement = document.createElement("TD");
        if (configStateID == "PlanFooter") {
            g_CurrentPlanSectionTextElement.style="width:" + PLAN_TEXT_BOX_WIDTH + "; vertical-align:bottom;"
        } else {
            g_CurrentPlanSectionTextElement.style="width:" + PLAN_TEXT_BOX_WIDTH + "; vertical-align:top;"
        }
        newRow.appendChild(g_CurrentPlanSectionTextElement);

        // Make an entry for the control panel
        // These are the rest of the common control panel attributes.
        controlPanelTableCell = document.createElement("TD");
        var controlPanelStyle = NO_SELECT_STYLE + "width:" + PLAN_CONTROL_PANEL_WIDTH;
        //<div id="CirrhosisControls" style="border:2px outset; width:625px; box-shadow:4px 4px #888888; padding: 10px 10px 10px 10px; ">
        // Aligning the control panel at the top may be difficult for a long plan section
        // because the control panel does not line up with the text it is affecting.
        // BUT, you don't want the buttons to move up and down as you change options and so change the output text.
        // Aligning it at the top makes the button stay in the same place no matter what text is in the plan.
        if (configStateID == "PlanFooter") {
            controlPanelTableCell.style = controlPanelStyle + "; vertical-align:bottom;"
        } else {
            controlPanelTableCell.style = controlPanelStyle + "; vertical-align:top;"
        }
        newRow.appendChild(controlPanelTableCell);

        //LogEvent("MedNote_StartNewPlanSection. Make a new row");
        //LogEvent("MedNote_StartNewPlanSection. newRow = " + newRow);
        //LogEvent("MedNote_StartNewPlanSection. g_CurrentPlanSectionTextElement = " + g_CurrentPlanSectionTextElement);
        //LogEvent("MedNote_StartNewPlanSection. controlPanelTableCell = " + controlPanelTableCell);

        // Save the table row in the plan state. This will let us just regenerate the plan text
        // later without recreating the control panel.
        if (planConfigState) {
            planConfigState.planTableRowElement = newRow;
            planConfigState.planTextHTMLElement = g_CurrentPlanSectionTextElement;
            planConfigState.activeControlPanel = null;

            //LogEvent("MedNote_StartNewPlanSection. planConfigState.controlPanelID = " + planConfigState.controlPanelID);
            // If there is a control panel, then make sure we have one cached.
            if (planConfigState.controlPanelID) {
                var calatogEntry = document.getElementById(planConfigState.controlPanelID);
                //LogEvent("Look for control panel. calatogEntry: " + calatogEntry);
                //LogEvent("Look for control panel. controlPanelTableCell: " + controlPanelTableCell);
                if ((calatogEntry) && (controlPanelTableCell)) {
                    //LogEvent("Adding control panel");
                    // Make a copy of the node. This lets us delete and rebuild the state without
                    // damaging the original catalog.
                    planConfigState.activeControlPanel = calatogEntry.cloneNode(true);
                    //LogEvent("Adding control panel. planConfigState.activeControlPanel = " + planConfigState.activeControlPanel);
                    planConfigState.activeControlPanel.style = CONTROL_PANEL_BACKGROUND_STYLE + NO_SELECT_STYLE;
                    controlPanelTableCell.appendChild(planConfigState.activeControlPanel);
                } // if (planConfigState.activeControlPanel) {
            } // Cache the control panel.
        } // if (planConfigState)
    } // if (!g_RedrawExistingPlanSection)

    ////////////////////////////////////////
    // Print the section header for the plan.
    // There will not be a section header for "special" sections like the note header or footer.
    if ((problemName) && (problemName != "")) {
        var brNode = document.createElement("br");
        g_CurrentPlanSectionTextElement.appendChild(brNode);

        textStr = PROBLEM_SECTION_HEADER_PREFIX + problemName + PROBLEM_SECTION_HEADER_SUFFIX;
        textNode = document.createTextNode(textStr);
        g_CurrentPlanSectionTextElement.appendChild(textNode);
    } // if (problemName)

    // Return the control panel
    if (planConfigState) {
        //LogEvent("MedNote_StartNewPlanSection. finished. planConfigState.activeControlPanel=" + planConfigState.activeControlPanel);
        return(planConfigState.activeControlPanel);
    } else {
        LogEvent("MedNote_StartNewPlanSection. finished but planConfigState is NULL");
        return(null);
    }
} // MedNote_StartNewPlanSection





////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_AddRelatedProblem]
// 
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_AddRelatedProblem(problemName) {
    //LogEvent("MedNote_AddRelatedProblem. problemName=" + problemName);

    // Print the section header for the plan.
    if (problemName) {
        var brNode = document.createElement("br");
        g_CurrentPlanSectionTextElement.appendChild(brNode); 
       
        var textNode = document.createTextNode(PROBLEM_SECTION_HEADER_PREFIX + problemName + PROBLEM_SECTION_HEADER_SUFFIX);
        g_CurrentPlanSectionTextElement.appendChild(textNode);
    } // if (problemName)
} // MedNote_AddRelatedProblem






////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_AddRelatedProblemIfSelected]
// 
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_AddRelatedProblemIfSelected(activeControlPanel, optionName) {
    //LogEvent("MedNote_AddRelatedProblemIfSelected");
    var problemName;

    problemName = MedNote_GetCPOptionValue(optionName);
    //LogEvent("MedNote_AddRelatedProblemIfSelected. problemName=" + problemName);
    if ((problemName != null) && (problemName != "")) {
        var brNode = document.createElement("br");
        g_CurrentPlanSectionTextElement.appendChild(brNode); 
       
        var textNode = document.createTextNode(PROBLEM_SECTION_HEADER_PREFIX + problemName + PROBLEM_SECTION_HEADER_SUFFIX);
        g_CurrentPlanSectionTextElement.appendChild(textNode);
    } // if (problemName)
} // MedNote_AddRelatedProblemIfSelected




    
////////////////////////////////////////////////////////////////////////////////
//
// [MedNode_WriteSubPlan]
//
// This creates a section of a plan, with one or more actions below it.
// For example:
//
// /Ascites:
//     Last LVP was 1/1/1900
//     - Furosemide
//     - Spironolactone
//     - Ciprofloxacin
//
////////////////////////////////////////////////////////////////////////////////
function 
MedNode_WriteSubPlan(subSectionName, actionNameList) { 
    var qualifiedName;
    var index;

    subPlanActionList = [];
    for (index = 0; index < actionNameList.length; index++) {
        currentActionName = actionNameList[index];
        planStr = MedNote_GetCPOptionValue(currentActionName);
        if ((planStr != null) && (planStr != "")) {
            subPlanActionList.push(planStr);
        }
    } // for (index = 0; index < optionNameList.length; index++)

    if (subPlanActionList.length <= 0) {
        return;
    }

    g_CurrentSectionHasPlanSubHeader = true;

    //qualifiedName = sectionName + " - " + subSectionName + ":";
    qualifiedName = SUBSECTION_SUBHEADER_OPEN_PREFIX + subSectionName + SUBSECTION_SUBHEADER_CLOSE_SUFFIX;
    WriteTextLine(qualifiedName);

    for (index = 0; index < subPlanActionList.length; index++) {
        var actionStr = subPlanActionList[index];
        WriteAction(actionStr);
    } // for (index = 0; index < subPlanActionList.length; index++)
} // MedNode_WriteSubPlan




////////////////////////////////////////////////////////////////////////////////
//
// [WriteListOfSubActions]
//
// This is slightly different than a subplan. Instead, it is a single action,
// that may have one or more instances.
//
// - Insulin
//    Glargine xxx units QHS
//    Lispro xxx units TID with meals
//    Sliding scale Insulin
//
// You call it like this:
// var optionNameList = [ 'p0', 'p1', 'p2' ]; 
// WriteListOfSubActions("Preface", optionNameList)
////////////////////////////////////////////////////////////////////////////////
function 
WriteListOfSubActions(prefaceStr, actionNameList) {
    var planStr;
    var currentActionName;
    var currentActionValue;
    var index = 0;
    var indentNum;
    var writeAtLeastOneAction = false;

    for (index = 0; index < actionNameList.length; index++) {
        currentActionName = actionNameList[index];
        if (MedNote_GetCPOptionBool(currentActionName)) {
            writeAtLeastOneAction = true;
            break;
        }
    } // for (index = 0; index < optionNameList.length; index++)

    if (!writeAtLeastOneAction) {
        return;
    }

    WriteAction(prefaceStr);
    for (index = 0; index < actionNameList.length; index++) {
        currentActionName = actionNameList[index];
        if (MedNote_GetCPOptionBool(currentActionName)) {
            planStr = MedNote_GetCPOptionValue(currentActionName);
            WriteIndentedTextLine(planStr);
        }
    } // for (index = 0; index < optionNameList.length; index++)
} // WriteListOfSubActions





////////////////////////////////////////////////////////////////////////////////
//
// [WriteListOfSelectedActions]
//
// This writes a list of actions:
// - Check lab1, lab2, lab3
//
// You call it like this:
// var optionNameList = [ 'p0', 'p1', 'p2' ]; 
// WriteListOfSelectedActions(activeControlPanel, "Check ", optionNameList)
////////////////////////////////////////////////////////////////////////////////
function 
WriteListOfSelectedActions(activeControlPanel, prefaceStr, optionNameList) {
    var planStr;
    var currentOptionName;
    var currentOptionValue;
    var count = 0;
    var wordListStr = "";

    for (index = 0; index < optionNameList.length; index++) {
        currentOptionName = optionNameList[index];
        currentOptionValue = MedNote_GetCPOptionValue(currentOptionName);
        if (currentOptionValue) {
            //LogEvent("WriteListOfSelectedValues. currentOptionValue=" + currentOptionValue);
            wordListStr = wordListStr + currentOptionValue + ", ";
            count += 1;
        }
    } // for (index = 0; index < optionNameList.length; index++)

    if (count > 0) {
        // Remove the last ", "
        wordListStr = wordListStr.substring(0, wordListStr.length - 2);
        WriteAction(prefaceStr + wordListStr);
    }
} // WriteListOfSelectedActions





////////////////////////////////////////////////////////////////////////////////
//
// [AddTextToHTML]
//
// This is just used for the help screen. It puts text in a non-standard html 
// element.
////////////////////////////////////////////////////////////////////////////////
function 
AddTextToHTML(parentNode, str) {
    var brNode;
    var textNode;   

    brNode = document.createElement("br");
    parentNode.appendChild(brNode);
    
    textNode = document.createTextNode(str);
    parentNode.appendChild(textNode);
} // AddTextToHTML





////////////////////////////////////////////////////////////////////////////////
//
// [WriteTextLine]
//
// This is the main function for printing. It adds text to the current plan.
////////////////////////////////////////////////////////////////////////////////
function 
WriteTextLine(str) {
    var brNode;
    var textNode;   

    brNode = document.createElement("br");
    g_CurrentPlanSectionTextElement.appendChild(brNode);
    
    textNode = document.createTextNode(str);
    g_CurrentPlanSectionTextElement.appendChild(textNode);
} // WriteTextLine






////////////////////////////////////////////////////////////////////////////////
//
// [WriteIndentedTextLine]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteIndentedTextLine(str) {
    var brNode;
    var textNode;   
    var spanNode;   

    brNode = document.createElement("br");
    g_CurrentPlanSectionTextElement.appendChild(brNode);

    spanNode = document.createElement("span");
    spanNode.setAttribute("style", "display:inline-block; width: 8mm;");
    spanNode.innerHTML = "&nbsp;    ";
    g_CurrentPlanSectionTextElement.appendChild(spanNode);
    
    textNode = document.createTextNode(str);
    g_CurrentPlanSectionTextElement.appendChild(textNode);
} // WriteIndentedTextLine




////////////////////////////////////////////////////////////////////////////////
//
// [WriteComment]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteComment(str) {
    var brNode;
    var textNode;   
    var IncludeAssessmentSubsection = 0;

    if (g_ProblemLayout == PROBLEM_ASSESSMENT_PLAN_SUBSECTIONS) {
        IncludeAssessmentSubsection = 1;
    }

    if ((g_WritingPlanSection) 
            && (IncludeAssessmentSubsection)
            && (!g_CurrentSectionHasAssessmentSubHeader) 
            && (!g_CurrentSectionHasPlanSubHeader)) {
        brNode = document.createElement("br");
        g_CurrentPlanSectionTextElement.appendChild(brNode);
        textNode = document.createTextNode(SUBSECTION_SUBHEADER_OPEN_PREFIX 
                                    + ASSESSMENT_SUBHEADER_STRING + SUBSECTION_SUBHEADER_CLOSE_SUFFIX);
        g_CurrentPlanSectionTextElement.appendChild(textNode);

        g_CurrentSectionHasAssessmentSubHeader = true;
    }

    WriteTextLine(PLAN_COMMENT_TEXT_LINE_PREFIX + str);
} // WriteComment






    
////////////////////////////////////////////////////////////////////////////////
//
// [WriteAction]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteAction(str) {    
    //LogEvent("WriteAction. str=" + str);
    var IncludePlanSubsection = 0;

    if ((g_ProblemLayout == PROBLEM_ASSESSMENT_PLAN_SUBSECTIONS) 
            || (g_ProblemLayout == PROBLEM_ONLY_PLAN_SUBSECTIONS)) {
        IncludePlanSubsection = 1;
    }

    if ((g_WritingPlanSection) 
            && (IncludePlanSubsection)
            && (!g_CurrentSectionHasPlanSubHeader)) {
        g_CurrentSectionHasPlanSubHeader = true;

        brNode = document.createElement("br");
        g_CurrentPlanSectionTextElement.appendChild(brNode);
        textNode = document.createTextNode(SUBSECTION_SUBHEADER_OPEN_PREFIX 
                                        + ACTION_SUBHEADER_STRING 
                                        + SUBSECTION_SUBHEADER_CLOSE_SUFFIX);
        g_CurrentPlanSectionTextElement.appendChild(textNode);
    }

    str = PLAN_ACTION_TEXT_LINE_PREFIX + str
    WriteTextLine(str);
} // WriteAction






////////////////////////////////////////////////////////////////////////////////
//
// [OnShowWindowButton]
//
////////////////////////////////////////////////////////////////////////////////
function
OnShowWindowButton(button) {
    //LogEvent("OnShowWindowButton");
    //LogEvent("button.id = " + button.id);
    ShowSubWindow(button.id, "", true);
    return(false);
} // OnShowWindowButton




////////////////////////////////////////////////////////////////////////////////
//
// [ShowSubWindow]
//
////////////////////////////////////////////////////////////////////////////////
function
ShowSubWindow(windowName, statusTextStr, showHelpClose) {
    ////////////////////////////////////
    // First, turn everything off.
    // We will selectively turn fields on depending on what was selected.    
    if (g_ToolBarElement) {
        g_ToolBarElement.style.display = "None";
    }
    if (g_PlanDivElement) {
        g_PlanDivElement.style.display = "None";
    }
    if (g_DiagnosisButtonsDivElement) {
        g_DiagnosisButtonsDivElement.style.display = "None";        
    }
    if (g_HelpDivElement) {
        g_HelpDivElement.style.display = "None";
    }
    if (g_OptionWindowDivElement) {
        g_OptionWindowDivElement.style.display = "None";
    }
    if (g_TextEditWindowDivElement) {
        g_TextEditWindowDivElement.style.display = "None";
    }
    if (g_ImportWindowDivElement) {
        g_ImportWindowDivElement.style.display = "None";
    }

    ////////////////////////////////////
    if ((windowName == "HelpButtonID") && (g_HelpDivElement)) {
        ////////////////////////////////////////
        // If there is a help window, then update it to show the latest browser information.
        if ((g_HelpDivElement) && (!g_CollectedSystemInfo)) {
            var infoDiv = Util_GetDescendantNodeByXID(g_HelpDivElement, "PlatformInfo");
            if (infoDiv) {
                AddTextToHTML(infoDiv, "App Name: " + window.navigator.appName);
                AddTextToHTML(infoDiv, "App Version: " + window.navigator.appVersion);
                //AddTextToHTML(infoDiv, "App Codename: " + window.navigator.appCodeName);
                //AddTextToHTML(infoDiv, "userAgent: " + window.navigator.userAgent);
                AddTextToHTML(infoDiv, "Platform: " + navigator.platform);
                AddTextToHTML(infoDiv, "Product: " + navigator.product);
                AddTextToHTML(infoDiv, "Language: " + navigator.language);
                AddTextToHTML(infoDiv, "Cookies Enabled: " + navigator.cookieEnabled);
                AddTextToHTML(infoDiv, "Java Enabled: " + navigator.javaEnabled());
                AddTextToHTML(infoDiv, "Requested URL: " + document.referrer);
                //AddTextToHTML(infoDiv, "Product: " + window.navigator.product);
            } // if (infoDiv)
            g_CollectedSystemInfo = true;
        } // if (g_HelpDivElement)

        statusTextControl = document.getElementById("HelpStatusTextID");
        Util_SetTextContents(statusTextControl, statusTextStr);

        closeButton = document.getElementById("CloseHelpButtonID");
        if (showHelpClose) {
            closeButton.style.display = "inline";
        } else {
            closeButton.style.display = "None";
        }

        g_HelpDivElement.style.display = "inline";

    ////////////////////////////////////
    } else if ((windowName == "TextEditButtonID") && (g_TextEditWindowDivElement)) {
        g_TextEditWindowDivElement.style.display = "inline";
    ////////////////////////////////////
    } else if ((windowName == "ImportButtonID") && (g_ImportWindowDivElement)) {
        g_ImportWindowDivElement.style.display = "inline";
        var scraperTextBox = document.getElementById("ScraperInput");
        if (scraperTextBox) {
            scraperTextBox.focus();
        }
    }
} // OnShowWindowButton




////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_OnCloseChildWindow]
//
////////////////////////////////////////////////////////////////////////////////
function
MedNote_OnCloseChildWindow(button) {
    if (g_ToolBarElement) {
        g_ToolBarElement.style.display = "inline";
    }
    if (g_DiagnosisButtonsDivElement) {
        g_DiagnosisButtonsDivElement.style.display = "inline";        
    }
    if (g_PlanDivElement) {
        g_PlanDivElement.style.display = "inline";
    }


    if (g_HelpDivElement) {
        g_HelpDivElement.style.display = "None";
    }
    if (g_OptionWindowDivElement) {
        g_OptionWindowDivElement.style.display = "None";
    }
    if (g_TextEditWindowDivElement) {
        g_TextEditWindowDivElement.style.display = "None";
    }
    if (g_ImportWindowDivElement) {
        g_ImportWindowDivElement.style.display = "None";
    }
} // MedNote_OnCloseChildWindow










////////////////////////////////////////////////////////////////////////////////
//
// [InitPlanState]
//
////////////////////////////////////////////////////////////////////////////////
function 
InitPlanState(planNameStr, printFunctionArg) {
    //LogEvent("InitPlanState. planNameStr= " + planNameStr); 
    var valueEntry = g_AllPlansDeclaration[planNameStr];
    
    valueEntry.isSelected = 0;
    valueEntry.PrintFunction = printFunctionArg;
    valueEntry.planSelectStatusHTMLElement = document.getElementById(valueEntry.planSelectStatusHTMLElementID);   
    //LogEvent("InitPlanState. valueEntry.planSelectStatusHTMLElement= " + valueEntry.planSelectStatusHTMLElement); 

    if (valueEntry.planSelectStatusHTMLElement) {
        valueEntry.planSelectStatusHTMLElement.className = "planOffStyle";
    } // if (valueEntry.planSelectStatusHTMLElement)
    valueEntry.SingleLinePlans = [];
} // InitPlanState






////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_OnCPOptionButton]
//
// This is the main worker procedure for all control panel buttons.
//  button.id is the name of the option state
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_OnCPOptionButton(button) {
    var optionEntry;
    var planSectionEntry;
    var currentButtonState;
    var toggleBehavior;
    var trNode;
    var tdNode;
    var groupButton;
    //LogEvent("MedNote_OnCPOptionButton");

    optionEntry = g_AllOptionsDeclaration[button.id];
    if (!optionEntry) {
        LogEvent("MedNote_OnCPOptionButton. null optionEntry. ButtonID=[" + button.id + "]");
        return;
    }

    //LogEvent("MedNote_OnCPOptionButton. optionEntry.PlanSectionID=" + optionEntry.PlanSectionID);
    planSectionEntry = g_AllPlansDeclaration[optionEntry.PlanSectionID];
    //LogEvent("MedNote_OnCPOptionButton. planSectionEntry=" + planSectionEntry);
    if (!planSectionEntry) {
        LogEvent("MedNote_OnCPOptionButton. null planSectionEntry. PlanSectionID=" + optionEntry.PlanSectionID);
        return;
    }

    currentButtonState = optionEntry.toggleState;
    toggleBehavior = optionEntry.toggleBehavior;

    //LogEvent("MedNote_OnCPOptionButton. currentButtonState=" + currentButtonState);
    //LogEvent("MedNote_OnCPOptionButton. optionEntry.ButtonLabelList.length=" + optionEntry.ButtonLabelList.length);
    if (currentButtonState < 0) {
        //LogEvent("MedNote_OnCPOptionButton. Turn the option on. button.id=" + button.id);
        currentButtonState = 0;
        button.value = optionEntry.ButtonLabelList[0];
        if ((toggleBehavior != null) && (toggleBehavior == "OK/Bad/NA")) {
            button.className = "CPGBNaGoodStyle";
        } else {
            button.className = "CPOptionOnStyle";
        }
    } else if (currentButtonState == (optionEntry.ButtonLabelList.length - 1)) {
        //LogEvent("MedNote_OnCPOptionButton. Turn the option off. button.id=" + button.id);
        currentButtonState = -1;
        button.value = optionEntry.ButtonLabelList[0];
        button.className = "CPOptionDisabledStyle";
    } else {
        currentButtonState = currentButtonState + 1;
        //LogEvent("MedNote_OnCPOptionButton. Increment the option.");
        //LogEvent("MedNote_OnCPOptionButton. currentButtonState=" + currentButtonState);
        //LogEvent("MedNote_OnCPOptionButton. Increment the option. New Button=" + optionEntry.ButtonLabelList[currentButtonState]);
        button.value = optionEntry.ButtonLabelList[currentButtonState];
        if ((toggleBehavior != null) && (toggleBehavior == "OK/Bad/NA")) {
            button.className = "CPGBNaBadStyle";
        } else if ((toggleBehavior != null) && (toggleBehavior == "On/Disabled")) {
            button.className = "CPOptionOnStyle";
        } else if ((toggleBehavior != null) && (toggleBehavior == "OK/Other/NA")) {
            button.className = "CPOptionOtherStyle";
        } else {
            button.className = "CPOptionOffStyle";
        }
    }

    // If this button is part of a group, and if we are turning it on, then enable the whole group.
    if (currentButtonState >= 0) {
        //LogEvent("MedNote_OnCPOptionButton. Enable the group button");

        trNode = Util_GetAncestorNode(button, "TR");
        if (trNode) {
            tdNode = Util_GetChildNode(trNode, "TD");
            if (tdNode) {
                groupButton = Util_GetChildNode(tdNode, "input");
                if (groupButton) {
                    if (groupButton.className == "CPGroupOffStyle") {
                        groupButton.className = "CPGroupOnStyle";
                    }
                } // if (groupButton)
            } // if (tdNode)
        } // if (trNode)
    } // if (currentButtonState >= 0)

    optionEntry.toggleState = currentButtonState;

    MedNote_RedrawPlanEntry(planSectionEntry);
} // MedNote_OnCPOptionButton






////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_RedrawPlanEntry]
//
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_RedrawPlanEntry(planSectionEntry) {
    //LogEvent("MedNote_RedrawPlanEntry");
    var planSectionEntry;

    if (!planSectionEntry) {
        LogEvent("MedNote_RedrawPlanEntry. null planSectionEntry");
        return;
    }
    //LogEvent("MedNote_RedrawPlanEntry. SectionID=" + planSectionEntry.planSelectStatusHTMLElementID);

    g_CurrentPlanSectionTextElement = planSectionEntry.planTextHTMLElement;
    Util_RemoveAllChildNodes(planSectionEntry.planTextHTMLElement);

    g_RedrawExistingPlanSection = true;
    g_WritingPlanSection = true;

    planSectionEntry.SingleLinePlans = [];
    planSectionEntry.PrintFunction();

    g_RedrawExistingPlanSection = false;
    g_WritingPlanSection = false;
} // MedNote_RedrawPlanEntry






////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_GetCPOptionToggleState]
//
// button.id is the name of the option state.
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_GetCPOptionToggleState(optionName) {
    var optionEntry;

    optionEntry = g_AllOptionsDeclaration[optionName];
    if (!optionEntry) {
        LogEvent("MedNote_GetCPOptionValueIndex. null optionEntry. optionName=" + optionName);
        return(-1);
    }

    return(optionEntry.toggleState);
} // MedNote_GetCPOptionToggleState




////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_GetCPOptionValue]
//
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_GetCPOptionValue(optionName) {
    var optionEntry;
    var value;

    optionEntry = g_AllOptionsDeclaration[optionName];
    if (!optionEntry) {
        LogEvent("MedNote_GetCPOptionValue. null optionEntry. optionName=" + optionName);
        return("");
    }

    if (optionEntry.toggleState < 0) {
        return("");
    }

    value = optionEntry.ValueList[optionEntry.toggleState];
    return(value);
} // MedNote_GetCPOptionValue





////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_GetCPOptionValueForIndex]
//
// button.id is the name of the option state.
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_GetCPOptionValueForIndex(optionName, index) {
    var optionEntry;
    var value;

    optionEntry = g_AllOptionsDeclaration[optionName];
    if (!optionEntry) {
        LogEvent("MedNote_GetCPOptionValueForIndex. null optionEntry. optionName=" + optionName);
        return("");
    }

    value = optionEntry.ValueList[index];
    //LogEvent("MedNote_GetCPOptionValueForIndex. Value=" + value);
    return(value);
} // MedNote_GetCPOptionValueForIndex





////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_GetCPOptionBool]
//
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_GetCPOptionBool(optionName) {
    var optionEntry = g_AllOptionsDeclaration[optionName];
    if (!optionEntry) {
        LogEvent("MedNote_GetCPOptionBool. null optionEntry. optionName=" + optionName);
        return(false);
    }

    if (optionEntry.toggleState < 0) {
        return(false);
    }
    return(true);
} // MedNote_GetCPOptionBool






////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_OnCPGroupButton]
//
// button.id is the name of the group button.
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_OnCPGroupButton(button) {
    var planSectionEntry;
    var groupEnabledState;
    var tdNode;
    var trNode;
    var nextTRNode = null;

    // Get the old state of the button, before we change it.
    if (button.className == "CPGroupOnStyle") {
        groupEnabledState = 1;
    } else {
        groupEnabledState = 0;
    }

    // Now, toggle the state of the button.
    if (groupEnabledState <= 0) {
        groupEnabledState = 1;
        button.className = "CPGroupOnStyle";
    } else {
        groupEnabledState = 0;
        button.className = "CPGroupOffStyle";
    }

    // Use this new button state to toggle the state of all buttons in
    // the group. First, get the first table element in the group, which is the
    // group button.
    tdNode = Util_GetAncestorNode(button, "TD");
    if (!tdNode) {
        LogEvent("MedNote_OnCPGroupButton. null tdNode");
        return;
    }
    trNode = Util_GetAncestorNode(tdNode, "TR");
    if (trNode) {
        nextTRNode = Util_GetPeerNode(trNode, "TR");
    }

    // Now, toggle every button in the group.
    tdNode = Util_GetPeerNode(tdNode, "TD");
    planSectionEntry = MedNote_ToggleButtonList(tdNode, groupEnabledState);

    // If there is a next row, check to see if it is a continuation of this row.
    while (nextTRNode) {
        tdNode = Util_GetChildNode(nextTRNode, "TD");
        if (tdNode) {
            var hasChildNodes = Util_NodeHasChildNodes(tdNode);
            //LogEvent("MedNote_OnCPGroupButton. hasChildNodes=[" + hasChildNodes + "]");
            // Look for a row-toggle button.
            // If the first entry in a row is empty, then it is under the control of
            // the same row-toggle button.
            // If the first entry in a row has some non-empty content, then it is under
            // the control of a different row-toggle button.
            if (hasChildNodes) {
                break;
            }

            // Now, toggle every button in the group.
            tdNode = Util_GetPeerNode(tdNode, "TD");
            planSectionEntry = MedNote_ToggleButtonList(tdNode, groupEnabledState);
        } // if (tdNode)

        nextTRNode = Util_GetPeerNode(nextTRNode, "TR");
    } // while (nextTRNode)

    MedNote_RedrawPlanEntry(planSectionEntry);
} // MedNote_OnCPGroupButton







////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_ToggleButtonList]
//
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_ToggleButtonList(tdNode, groupEnabledState) {
    var optionEntry;
    var planSectionEntry;
    var peerButton = null;

    // Now, toggle every button in the group.
    while (tdNode) {
        peerButton = Util_GetChildNode(tdNode, "input");
        if (peerButton) {
            optionEntry = g_AllOptionsDeclaration[peerButton.id];
            if (optionEntry) {
                // For a group button, 1 means "on" and 0 means "off".
                // For an individual button, -1 means "off" and 0,1,2,3.... mean on
                if (groupEnabledState >= 1) {
                    optionEntry.toggleState = optionEntry.savedToggleState;
                    if (optionEntry.toggleState < 0) {
                        peerButton.value = optionEntry.ButtonLabelList[0];
                    } else {
                        peerButton.value = optionEntry.ButtonLabelList[optionEntry.toggleState];
                    }
                    peerButton.className = "CPOptionOnStyle";
                } else {
                    optionEntry.savedToggleState = optionEntry.toggleState;
                    optionEntry.toggleState = -2;
                    peerButton.value = optionEntry.ButtonLabelList[0];
                    peerButton.className = "CPOptionDisabledStyle";
                }
            } else {
                //LogEvent("MedNote_ToggleButtonList. null optionEntry");
            }

            planSectionEntry = g_AllPlansDeclaration[optionEntry.PlanSectionID];
        } // if (peerButton)

        tdNode = Util_GetPeerNode(tdNode, "TD");
    } // while (tdNode)

    return(planSectionEntry);
} // MedNote_ToggleButtonList





////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_CPReload]
//
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_CPReload(button, planSectionName) {
    //LogEvent("MedNote_CPReload. planSectionName=" + planSectionName);
    var planSectionEntry;

    planSectionEntry = g_AllPlansDeclaration[planSectionName];
    //LogEvent("MedNote_CPReload. planSectionEntry=" + planSectionEntry);
    if (!planSectionEntry) {
        LogEvent("MedNote_CPReload. null planSectionEntry");
        return;
    }

    //LogEvent("MedNote_CPReload. call MedNote_RedrawPlanEntry");
    MedNote_RedrawPlanEntry(planSectionEntry);
    //LogEvent("MedNote_CPReload. MedNote_RedrawPlanEntry returned");
} // MedNote_CPReload





////////////////////////////////////////////////////////////////////////////////
//
// [GetIntInputForControlPanel]
//
////////////////////////////////////////////////////////////////////////////////
function 
GetIntInputForControlPanel(activeControlPanel, inputName) {
    var inputHTMLElement = null;
    var resultInt = -1;

    inputHTMLElement = Util_GetDescendantNodeByID(activeControlPanel, inputName);
    if (inputHTMLElement) {
        var inputText = inputHTMLElement.value;
        resultInt = parseInt(inputText);
        if (isNaN(resultInt)) {
            resultInt = -1;
        }
    }

    return(resultInt);
} // GetIntInputForControlPanel




////////////////////////////////////////////////////////////////////////////////
//
// [GetFloatInputForControlPanel]
//
////////////////////////////////////////////////////////////////////////////////
function 
GetFloatInputForControlPanel(activeControlPanel, inputName) {
    var inputHTMLElement = null;
    var resultFloat = -1;

    inputHTMLElement = Util_GetDescendantNodeByID(activeControlPanel, inputName);
    if (inputHTMLElement) {
        var inputText = inputHTMLElement.value;
        resultFloat = parseFloat(inputText);
        if (isNaN(resultFloat)) {
            resultFloat = -1;
        }
    }

    return(resultFloat);
} // GetFloatInputForControlPanel




////////////////////////////////////////////////////////////////////////////////
//
// [GetBoolInputForControlPanel]
//
////////////////////////////////////////////////////////////////////////////////
function 
GetBoolInputForControlPanel(activeControlPanel, inputName) {
    var resultBool = false;

    var inputHTMLElement = Util_GetDescendantNodeByID(activeControlPanel, inputName);
    if (inputHTMLElement) {
        if (inputHTMLElement.className == "CPOptionOnStyle") {
            resultBool = true;
        }
    }

    return(resultBool);
} // GetBoolInputForControlPanel



////////////////////////////////////////////////////////////////////////////////
//
// [GetStrInputForControlPanel]
//
// This returns a string, which allows you to get a complex numeric expression 
// string like "5 - 10"
////////////////////////////////////////////////////////////////////////////////
function 
GetStrInputForControlPanel(activeControlPanel, inputName) {
    var inputHTMLElement = null;
    var resultStr = null;

    inputHTMLElement = Util_GetDescendantNodeByID(activeControlPanel, inputName);
    if (inputHTMLElement) {
        resultStr = inputHTMLElement.value;
    }

    return(resultStr);
} // GetStrInputForControlPanel





////////////////////////////////////////////////////////////////////////////////
//
// [SetStrOutputForControlPanel]
//
////////////////////////////////////////////////////////////////////////////////
function 
SetStrOutputForControlPanel(activeControlPanel, outputName, globalInputInfoName, resultStr) {
    var outputHTMLElement = null;

    outputHTMLElement = Util_GetDescendantNodeByID(activeControlPanel, outputName);
    if (outputHTMLElement) {
        Util_RemoveAllChildNodes(outputHTMLElement);    
        var textNode = document.createTextNode(resultStr);
        outputHTMLElement.appendChild(textNode);
    }
} // SetStrOutputForControlPanel






////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_CPToggleControls]
//
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_CPToggleControls(button) { 
    var cpHeader;
    var cpBody;
    
    if (!button) {
        return;
    }
    cpHeader = Util_GetAncestorNodeByxID(button, "CPHeader");
    if (!cpHeader) {
        return;
    }
    cpBody = Util_GetPeerNodeByxID(cpHeader, "CPBody");
    if (!cpBody) {
        return;
    }

    // Toggle based on the button state.
    if  (button.value == "Show") {
        button.value="Hide";
        cpBody.style.display = "inline";
    } else {
        //button.className="Hide ";
        button.value="Show";
        cpBody.style.display = "None";
    }
} // MedNote_CPToggleControls






////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_CPToggleHints]
//
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_CPToggleHints(button) { 
    var cpBody;
    var cpHeader;
    var hintsDiv;

    if (!button) {
        LogEvent("MedNote_CPToggleHints. null button");
        return;
    }
    
    // The Hints button may be under the body.
    cpBody = Util_GetAncestorNodeByxID(button, "CPBody");
    if (!cpBody) {
        // If it is not inside the body, then it may be inside the header,
        // which is a peer of the body.
        cpHeader = Util_GetAncestorNodeByxID(button, "CPHeader");
        if (cpHeader) {
            cpBody = Util_GetPeerNodeByxID(cpHeader, "CPBody");
        }
    }
    // If we cannot find the body with either method, then quit.
    // The HTML is not what we expect.
    if (!cpBody) {
        LogEvent("MedNote_CPToggleHints. null cpBody");
        return;
    }

    hintsDiv = Util_GetDescendantNodeByXID(cpBody, "CPHintText");
    if (!hintsDiv) {
        LogEvent("MedNote_CPToggleHints. null CPHintText");
        return;
    }

    // Toggle based on the button state.
    //LogEvent("MedNote_CPToggleHints. hintsDiv=" + hintsDiv);
    if  (button.value == "Show Hints") {
        button.value="Hide Hints";
        hintsDiv.style.display = "inline";
    } else {
        button.value="Show Hints";
        hintsDiv.style.display = "None";
    }
} // MedNote_CPToggleHints




    
////////////////////////////////////////////////////////////////////////////////
//
// [WriteActionIfSelected]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteActionIfSelected(activeControlPanel, optionName) {
    //LogEvent("WriteActionIfSelected. optionName=" + optionName);
    var planStr;

    planStr = MedNote_GetCPOptionValue(optionName);
    if ((planStr != null) && (planStr != "")) {
        //LogEvent("WriteActionIfSelected. optionName=" + optionName);
        WriteAction(planStr);
    }
} // WriteActionIfSelected




////////////////////////////////////////////////////////////////////////////////
//
// [WriteCommentIfSelected]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteCommentIfSelected(activeControlPanel, optionName) {
    var planStr;

    planStr = MedNote_GetCPOptionValue(optionName);
    if ((planStr != null) && (planStr != "")) {
        WriteComment(planStr);
    }
} // WriteCommentIfSelected




////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_WriteScoreFromSelectedValues]
//
// var optionNameList = [ 'p0', 'p1', 'p2' ]; 
// WriteScoreFromSelectedValues(activeControlPanel, "Preface", false, "", optionNameList, "Suffix")
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_WriteScoreFromSelectedValues(activeControlPanel, prefaceStr, countSuffixStr, optionNameList, suffixStr) {
    //LogEvent("WriteScoreFromSelectedValues. prefaceStr=" + prefaceStr);
    var planStr;
    var currentOptionName;
    var currentSelectedState = 0;
    var wordListStr = "";
    var score = 0;
    var numSelected = 0;

    //LogEvent("WriteScoreFromSelectedValues. optionNameList.length=" + optionNameList.length);
    for (index = 0; index < optionNameList.length; index++) {
        currentOptionName = optionNameList[index];
        currentSelectedState = MedNote_GetCPOptionToggleState(currentOptionName);
        if (currentSelectedState >= 0) {
            wordListStr = wordListStr + MedNote_GetCPOptionValue(currentOptionName) + ", ";
            score += currentSelectedState;
            numSelected += 1
        }
    } // for (index = 0; index < optionNameList.length; index++)

    // Print the comment if anything is selected, even if the score is 0.
    // It is useful to show what criteria are normal and so add 0 to the score.
    if (numSelected > 0) {
        // Remove the last ", "
        wordListStr = wordListStr.substring(0, wordListStr.length - 2);
        planStr = prefaceStr + score + countSuffixStr + wordListStr + suffixStr;
        WriteComment(planStr);
    }
} // MedNote_WriteScoreFromSelectedValues






////////////////////////////////////////////////////////////////////////////////
//
// [WriteListOfSelectedValues]
//
// var optionNameList = [ 'p0', 'p1', 'p2' ]; 
// WriteListOfSelectedValues(activeControlPanel, "Preface", false, "", optionNameList, "Suffix")
////////////////////////////////////////////////////////////////////////////////
function 
WriteListOfSelectedValues(activeControlPanel, prefaceStr, printCount, countSuffixStr, optionNameList, suffixStr) {
    //LogEvent("WriteListOfSelectedValues. prefaceStr=" + prefaceStr);
    var planStr;
    var currentOptionName;
    var currentOptionValue;
    var count = 0;
    var wordListStr = "";

    //LogEvent("WriteListOfSelectedValues. optionNameList.length=" + optionNameList.length);
    for (index = 0; index < optionNameList.length; index++) {
        currentOptionName = optionNameList[index];
        currentOptionValue = MedNote_GetCPOptionValue(currentOptionName);
        if (currentOptionValue) {
            //LogEvent("WriteListOfSelectedValues. currentOptionValue=" + currentOptionValue);
            wordListStr = wordListStr + currentOptionValue + ", ";
            count += 1;
        }
    } // for (index = 0; index < optionNameList.length; index++)

    if (count > 0) {
        // Remove the last ", "
        wordListStr = wordListStr.substring(0, wordListStr.length - 2);

        planStr = prefaceStr;
        if (printCount) {
            planStr = planStr + count + countSuffixStr;
        }
        planStr = planStr + wordListStr + suffixStr;

        WriteComment(planStr);
    }
} // WriteListOfSelectedValues





////////////////////////////////////////////////////////////////////////////////
//
// [WriteListOfSelectedValuesWithDescriptions]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteListOfSelectedValuesWithDescriptions(activeControlPanel, optionNameList, valueList, valueNameList) {
    var planStr = "";

    for (index = 0; index < optionNameList.length; index++) {
        var currentOptionName = optionNameList[index];
        //LogEvent("currentOptionName = " + currentOptionName);

        var currentOptionStr = MedNote_GetCPOptionValue(currentOptionName);
        if ((currentOptionStr != null) && (currentOptionStr != "")) {
            planStr = planStr + currentOptionStr;

            var currentValue = valueList[index];
            var currentValueName = valueNameList[index];
            //LogEvent("currentValue = " + currentValue + "currentValueName = " + currentValueName);
            if (currentValue != "") {
                planStr = planStr + currentValue;
            } else if (currentValueName != "") {
                currentValue = GetStrInputForControlPanel(activeControlPanel, currentValueName);
                if ((currentValue != null) && (currentValue != "")) {
                    planStr = planStr + currentValue;
                }
            }
            planStr = planStr + ", ";
        }
    } // for (index = 0; index < optionNameList.length; index++)

    if (planStr != "") {
        // Remove the last ", "
        planStr = planStr.substring(0, planStr.length - 2);
        WriteComment(planStr);
    }
} // WriteListOfSelectedValuesWithDescriptions





////////////////////////////////////////////////////////////////////////////////
//
// [WriteListOfSelectedMedHistoryItem
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteListOfSelectedMedHistoryItems(activeControlPanel, prefaceStr, optionNameList) {
    //LogEvent("WriteListOfSelectedMedHistoryItems. prefaceStr=" + prefaceStr);
    var currentOptionValue;
    var index;

    WriteTextLine(prefaceStr);
    //LogEvent("WriteListOfSelectedMedHistoryItems. optionNameList.length=" + optionNameList.length);
    for (index = 0; index < optionNameList.length; index++) {
        currentOptionValue = MedNote_GetCPOptionValue(optionNameList[index]);
        if (currentOptionValue) {
            WriteTextLine("- " + currentOptionValue);
        }
    } // for (index = 0; index < optionNameList.length; index++)
} // WriteListOfSelectedMedHistoryItems





////////////////////////////////////////////////////////////////////////////////
//
// [WriteHistoryItem]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteHistoryItem(activeControlPanel, prefaceStr, optionNameList, defaultStr) {
    var planStr;
    var currentOptionValue;
    var count = 0;
    var wordListStr = "";

    for (index = 0; index < optionNameList.length; index++) {
        currentOptionValue = MedNote_GetCPOptionValue(optionNameList[index]);
        if (currentOptionValue) {
            wordListStr = wordListStr + currentOptionValue + ", ";
            count += 1;
        }
    } // for (index = 0; index < optionNameList.length; index++)

    if (count <= 0) {
        wordListStr = defaultStr;
    } else {
        wordListStr = wordListStr.substring(0, wordListStr.length - 2);
    }

    planStr = prefaceStr + wordListStr;
    WriteTextLine(planStr);
} // WriteHistoryItem






////////////////////////////////////////////////////////////////////////////////
//
// [CountSelectedValues]
//
////////////////////////////////////////////////////////////////////////////////
function 
CountSelectedValues(activeControlPanel, optionNameList) {
    //LogEvent("CountSelectedValues");
    var planStr;
    var currentOptionName;
    var currentOptionValue;
    var count = 0;
    var wordListStr = "";

    for (index = 0; index < optionNameList.length; index++) {
        currentOptionName = optionNameList[index];
        currentOptionValue = MedNote_GetCPOptionValue(currentOptionName);
        if (currentOptionValue) {
            wordListStr = wordListStr + currentOptionValue + ", ";
            count += 1;
        }
    } // for (index = 0; index < optionNameList.length; index++)

    return(count);
} // CountSelectedValues




////////////////////////////////////////////////////////////////////////////////
//
// [WriteListOfSelectedFormatStrings]
//
// var optionNameList = [ 'p0', 'p1', 'p2' ]; 
// WriteListOfSelectedFormatStrings(activeControlPanel, "Preface", optionNameList, "Suffix")
////////////////////////////////////////////////////////////////////////////////
function 
WriteListOfSelectedFormatStrings(activeControlPanel, optionNameList) {
    //LogEvent("WriteListOfSelectedFormatStrings");
    var planStr = "";
    var count = 0;
    var formatTypeStr;
    var formattingOptionEntry;
    var currentOptionName;
    var intValueName;
    var intValue;
    var strValue;
    var numeratorValueName;
    var denominatorValueName;
    var numeratorValue;
    var denominatorValue;
    var ratioValue;
    var formatType;
    var formatStr = "";

    planStr = "";
    for (index = 0; index < optionNameList.length; index++) {
        currentOptionName = optionNameList[index];
        if (MedNote_GetCPOptionBool(currentOptionName)) {
            //LogEvent("WriteListOfSelectedFormatStrings. currentOptionName=" + currentOptionName + " is selected");
            formattingOptionEntry = g_FormatStringsDeclaration[currentOptionName];

            if (formattingOptionEntry) {
                //LogEvent("WriteListOfSelectedFormatStrings. currentOptionName=" + currentOptionName + " is selected");

                if (count >= 1) {
                    planStr = planStr + ", ";
                }

                formatType = formattingOptionEntry.FormatType;
                ///////////////////////////
                if ((formatType != null) && (formatType == "Text")) {
                    formatStr = formattingOptionEntry.FormatString;
                ///////////////////////////
                } else if ((formatType != null) && (formatType == "Simple")) {
                    formatStr = formattingOptionEntry.FormatString;
                    intValueName = formattingOptionEntry.CPInputValueName;
                    if ((intValueName != null) && (intValueName != "")) {
                        strValue = GetStrInputForControlPanel(activeControlPanel, intValueName);
                        formatStr = formatStr.replace(/{VAL}/gi, strValue);
                    } // if ((intValueName != null) && (intValueName != "")) {
                ///////////////////////////
                } else if ((formatType != null) && (formatType == "Ratio")) {
                    formatStr = formattingOptionEntry.FormatString;
                    numeratorValueName = formattingOptionEntry.CPInputValueName;
                    denominatorValueName = formattingOptionEntry.CPInputRatioDenominatorValueName;

                    if ((numeratorValueName != null) && (numeratorValueName != "") 
                            && (denominatorValueName != null) && (denominatorValueName != "")) {
                        numeratorValue = GetIntInputForControlPanel(activeControlPanel, numeratorValueName);
                        denominatorValue = GetIntInputForControlPanel(activeControlPanel, denominatorValueName);
                        ratioValue = numeratorValue / denominatorValue;
                        ratioValue = Math.round( ratioValue * 100 ) / 100;

                        formatStr = formatStr.replace(/{RATIO}/gi, ratioValue.toString());
                    } // if ((numeratorValueName != null) && (numeratorValueName != "") && ...
                }

                planStr += formatStr;
                count += 1;
            } // if (formattingOptionEntry)
        } // if (MedNote_GetCPOptionBool(currentActionName))
    } // for (index = 0; index < optionNameList.length; index++)


    if (count > 0) {
        WriteComment(planStr);
    }
} // WriteListOfSelectedFormatStrings






////////////////////////////////////////////////////////////////////////////////
//
// [NB_ProblemMarkerSelect]
//
// This is called when the user selects a different prefix for problems.
////////////////////////////////////////////////////////////////////////////////
function 
NB_OnProblemMarkerSelect(menuControl) {
    var selectedItem = menuControl.options[menuControl.selectedIndex].value;
    if (selectedItem == "MEDNOTEMAKER_PROBLEM_MARKER_POUND_PAREN") {
        PROBLEM_SECTION_HEADER_PREFIX = "#) ";
        PROBLEM_SECTION_HEADER_SUFFIX = " ";
    } else if (selectedItem == "MEDNOTEMAKER_PROBLEM_MARKER_POUND_SPACE") {
        PROBLEM_SECTION_HEADER_PREFIX = "# ";
        PROBLEM_SECTION_HEADER_SUFFIX = " ";
    } else if (selectedItem == "MEDNOTEMAKER_PROBLEM_MARKER_POUND_NOSPACE") {
        PROBLEM_SECTION_HEADER_PREFIX = "#";
        PROBLEM_SECTION_HEADER_SUFFIX = " ";
    } else if (selectedItem == "MEDNOTEMAKER_PROBLEM_MARKER_DASH") {
        PROBLEM_SECTION_HEADER_PREFIX = "-";
        PROBLEM_SECTION_HEADER_SUFFIX = ":";
    } else if (selectedItem == "MEDNOTEMAKER_PROBLEM_MARKER_NOTHING") {
        PROBLEM_SECTION_HEADER_PREFIX = "";
        PROBLEM_SECTION_HEADER_SUFFIX = "";
    }

    WritePlanBody();
} // NB_ProblemMarkerSelect






////////////////////////////////////////////////////////////////////////////////
//
// [NB_OnProblemSectionSelect]
//
// This is called when the user selects a different prefix for major plan sections.
////////////////////////////////////////////////////////////////////////////////
function 
NB_OnProblemSectionSelect(menuControl) {
    var selectedItem = menuControl.options[menuControl.selectedIndex].value;
    //LogEvent("selectedItem=" + selectedItem);
    if (selectedItem == "MEDNOTEMAKER_PROBLEM_SECTIONS_ASSESSMENT_PLAN") {
        g_ProblemLayout = PROBLEM_ASSESSMENT_PLAN_SUBSECTIONS;
    } else if (selectedItem == "MEDNOTEMAKER_PROBLEM_SECTIONS_PLAN") {
        g_ProblemLayout = PROBLEM_ONLY_PLAN_SUBSECTIONS;
    } else if (selectedItem == "MEDNOTEMAKER_PROBLEM_SECTIONS_NONE") {
        g_ProblemLayout = PROBLEM_NO_SUBSECTIONS;
    }

    WritePlanBody();
} // NB_OnProblemSectionSelect






////////////////////////////////////////////////////////////////////////////////
//
// [NB_OnProblemSectionLabelSelect]
//
// This is called when the user selects a different prefix for labels.
// Options tried:  foo:   [foo]  {foo}   //foo    /foo    [foo]  =Foo=
////////////////////////////////////////////////////////////////////////////////
function 
NB_OnProblemSectionLabelSelect(menuControl) {
    var selectedItem = menuControl.options[menuControl.selectedIndex].value;
    if (selectedItem == "MEDNOTEMAKER_PROBLEM_SECTIONS_LABEL_SLASH_COLON") {
        SUBSECTION_SUBHEADER_OPEN_PREFIX = "/";
        SUBSECTION_SUBHEADER_CLOSE_SUFFIX = ":";
    } else if (selectedItem == "MEDNOTEMAKER_PROBLEM_SECTIONS_LABEL_DOUBLESLASH_COLON") {
        SUBSECTION_SUBHEADER_OPEN_PREFIX = "//";
        SUBSECTION_SUBHEADER_CLOSE_SUFFIX = ":";
    } else if (selectedItem == "MEDNOTEMAKER_PROBLEM_SECTIONS_LABEL_COLON") {
        SUBSECTION_SUBHEADER_OPEN_PREFIX = "";
        SUBSECTION_SUBHEADER_CLOSE_SUFFIX = ":";
    } else if (selectedItem == "MEDNOTEMAKER_PROBLEM_SECTIONS_LABEL_NONE") {
        SUBSECTION_SUBHEADER_OPEN_PREFIX = "";
        SUBSECTION_SUBHEADER_CLOSE_SUFFIX = "";
    }

    WritePlanBody();
} // NB_OnProblemSectionLabelSelect





////////////////////////////////////////////////////////////////////////////////
//
// [NB_OnActionPrefixSelect]
//
// This is called when the user selects a different prefix for actions.
////////////////////////////////////////////////////////////////////////////////
function 
NB_OnActionPrefixSelect(menuControl) {
    var selectedItem = menuControl.options[menuControl.selectedIndex].value;
    if (selectedItem == "MEDNOTEMAKER_ACTION_PREFIX_DASH_SPACE") {
        PLAN_ACTION_TEXT_LINE_PREFIX = "- ";
    } else if (selectedItem == "MEDNOTEMAKER_ACTION_PREFIX_DASH") {
        PLAN_ACTION_TEXT_LINE_PREFIX = "-";
    } else if (selectedItem == "MEDNOTEMAKER_ACTION_PREFIX_NONE") {
        PLAN_ACTION_TEXT_LINE_PREFIX = "";
    }

    WritePlanBody();
} // NB_OnActionPrefixSelect




////////////////////////////////////////////////////////////////////////////////
//
// [NB_OnCommentPrefixSelect]
//
// This is called when the user selects a different prefix for comments.
////////////////////////////////////////////////////////////////////////////////
function 
NB_OnCommentPrefixSelect(menuControl) {
    var selectedItem = menuControl.options[menuControl.selectedIndex].value;
    if (selectedItem == "MEDNOTEMAKER_ACTION_PREFIX_DASH_SPACE") {
        PLAN_COMMENT_TEXT_LINE_PREFIX = "- ";
    } else if (selectedItem == "MEDNOTEMAKER_ACTION_PREFIX_DASH") {
        PLAN_COMMENT_TEXT_LINE_PREFIX = "-";
    } else if (selectedItem == "MEDNOTEMAKER_ACTION_PREFIX_NONE") {
        PLAN_COMMENT_TEXT_LINE_PREFIX = "";
    }

    WritePlanBody();
} // NB_OnCommentPrefixSelect






////////////////////////////////////////////////////////////////////////////////
//
// [MedNote_ToggleTinyPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
MedNote_ToggleTinyPlan(button, planSectionName) {
    var planSectionEntry;
    //LogEvent("MedNote_ToggleTinyPlan. planSectionName=" + planSectionName);
    //LogEvent("button.id = " + button.id);

    planSectionEntry = g_AllPlansDeclaration[planSectionName];
    if (!planSectionEntry) {
        LogEvent("MedNote_ToggleTinyPlan. null planSectionEntry");
        return;
    }

    if  (planSectionEntry.PrintSingleLine == 1) {
        button.className="CPOptionDisabledStyle";
        planSectionEntry.PrintSingleLine = 0;
    } else if (planSectionEntry.PrintSingleLine == 0) {
        button.className="CPOptionOnStyle";
        planSectionEntry.PrintSingleLine = 1;
    }        

    //LogEvent("MedNote_ToggleTinyPlan. call MedNote_RedrawPlanEntry");
    MedNote_RedrawPlanEntry(planSectionEntry);
    //LogEvent("MedNote_ToggleTinyPlan. MedNote_RedrawPlanEntry returned");

    // Redraw the footer so we can include the plan as a tinyplan.
    var footerConfigState = g_AllPlansDeclaration['PlanFooter'];
    MedNote_RedrawPlanEntry(footerConfigState);
} // MedNote_ToggleTinyPlan






////////////////////////////////////////////////////////////////////////////////
//
// [PrintSingleLinePlanAtEnd]
//
////////////////////////////////////////////////////////////////////////////////
function 
PrintSingleLinePlanAtEnd(planName, planTitleStr, planActionStr) {
    //LogEvent("PrintSingleLinePlanAtEnd for plan: " + planName);
    //LogEvent("planTitleStr=" + planTitleStr);
    //LogEvent("planActionStr=" + planActionStr);

    planConfigState = g_AllPlansDeclaration[planName];
    if (planConfigState.PrintSingleLine <= 0) {
        return(false);
    }

    textStr = PROBLEM_SECTION_HEADER_PREFIX + planTitleStr + PROBLEM_SECTION_HEADER_SUFFIX + " - " + planActionStr;
    g_TinyPlanStringList.push(textStr)

    return(true);
} // PrintSingleLinePlanAtEnd




////////////////////////////////////////////////////////////////////////////////
//
// [AddSingleLinePlanAtEnd]
//
////////////////////////////////////////////////////////////////////////////////
function 
AddSingleLinePlanAtEnd(planSectionName, planTitleStr, planActionStr) {
    //LogEvent("AddSingleLinePlanAtEnd. planTitleStr=" + planTitleStr);
    //LogEvent("AddSingleLinePlanAtEnd. planActionStr=" + planActionStr);
    var planSectionEntry;

    planSectionEntry = g_AllPlansDeclaration[planSectionName];
    //LogEvent("MedNote_CPReload. planSectionEntry=" + planSectionEntry);
    if (!planSectionEntry) {
        LogEvent("AddSingleLinePlanAtEnd. null planSectionEntry");
        return;
    }

    textStr = PROBLEM_SECTION_HEADER_PREFIX + planTitleStr + PROBLEM_SECTION_HEADER_SUFFIX + " - " + planActionStr;
    planSectionEntry.SingleLinePlans.push(textStr)
} // AddSingleLinePlanAtEnd


