////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2013-2020 Dawson Dean
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
// This file contains the plans for each problem.
/////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
// [WriteDyspneaPlan]
// NOT USED
////////////////////////////////////////////////////////////////////////////////
function 
WriteDyspneaPlan() {
    MedNote_StartNewPlanSection("Acute on chronic Hypoxic Respiratory Failure", null);
} // WriteDyspneaPlan



////////////////////////////////////////////////////////////////////////////////
// [WriteMenorrhagiaPlan]
// NOT USED
////////////////////////////////////////////////////////////////////////////////
function 
WriteMenorrhagiaPlan() {
    MedNote_StartNewPlanSection("Metromenorrhagia", null);
    WriteAction("Check beta-hCG");
    WriteAction("Check TSH (to rule out elevated TRH which causes prolactin release)");
    WriteAction("Check Prolactin level");
} // WriteMenorrhagiaPlan




////////////////////////////////////////////////////////////////////////////////
//
// [WriteCirrhosisPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteCirrhosisPlan() {
    //LogEvent("Inside WriteCirrhosisPlan");
    var planNameStr = "Cirrhosis";
    var planConfigState = null;
    var activeControlPanel = null;
    var causeStr = "";
    var planStr = "";
    var subPlanActionList = [];
    var subsectionName = "";

    // <> May use "Hepatic Steatosis with Hepatic Fibrosis"
    causeStr = MedNote_GetCPOptionValue("CirrhosisCompensatedOption");
    if ((causeStr != null) && (causeStr != "")) {
        planNameStr = planNameStr + " (" + causeStr + ")";
    }
    MedNote_StartNewPlanSection(planNameStr, "CirrhosisPlan");
    var causeStr = MedNote_GetCPOptionValue("CirrhosisCauseOption");
    if (causeStr != "") {
        WriteComment("The suspected cause is " + causeStr);
    }
    if (MedNote_GetCPOptionBool("CirrhosisCoagulopathyOption")) {
        MedNote_AddRelatedProblem("Coagulopathy - Due to liver disease");
    }
    if (MedNote_GetCPOptionBool("CirrhosisThrombocytopeniaOption")) {
        MedNote_AddRelatedProblem("Thrombocytopenia - Due to liver disease");
    }


    planConfigState = g_AllPlansDeclaration['CirrhosisPlan'];
    //LogEvent("WriteCirrhosisPlan. planConfigState=" + planConfigState);
    if (!planConfigState) {
        return;
    }
    activeControlPanel = planConfigState.activeControlPanel;
    //LogEvent("WriteCirrhosisPlan. activeControlPanel=" + activeControlPanel);
    if (!activeControlPanel) {
        return;
    }


    var currentPT = GetIntInputForControlPanel(activeControlPanel, 'InputPT_CP', null);
    var currentINR = GetIntInputForControlPanel(activeControlPanel, 'InputINR_CP', null);
    var currentNa = GetIntInputForControlPanel(activeControlPanel, 'InputSodium_CP', null);
    var currentCr = GetIntInputForControlPanel(activeControlPanel, 'InputCreatinine_CP', null);
    var currentTbili = GetIntInputForControlPanel(activeControlPanel, 'InputTBili_CP', null);
    var currentAlbumin= GetIntInputForControlPanel(activeControlPanel, 'InputAlbumin_CP', null);


    // Always compute these so they at least show up in the control panel.
    var MELDScore = NBQuant_ComputeMELD(currentINR, currentNa, currentCr, currentTbili);
    if (MELDScore > 0) {
        SetStrOutputForControlPanel(activeControlPanel, 'MELD_CP', null, 'MELD = ' + MELDScore);
    }

    // ascitesScore = "none", "slight", "large"
    // encephalopathy = "none", "grade 1", "grade 2"
    var ChildPughStr = NBQuant_ComputeChildPugh(currentAlbumin, currentINR, currentTbili, "slight", "none");
    if (ChildPughStr) {
        SetStrOutputForControlPanel(activeControlPanel, 'ChildPugh_CP', null, 'Child-Pugh = ' + ChildPughStr);
    }


    //////////////////////////////
    // Scores
    if (MedNote_GetCPOptionBool("CirrhosisMELDOption")) {
        //    ascitesScore = "none", "slight", "large"
        //    encephalopathy = "none", "grade 1", "grade 2"
        if (MELDScore > 0) {
            WriteComment("MELD Score = " + MELDScore);
        } else {
            WriteComment("MELD Score = xxx");
        }
    }
    if (MedNote_GetCPOptionBool("CirrhosisChildPughOption")) {
        if (ChildPughStr) {
            WriteComment("Child-Pugh Class score = " + ChildPughStr);
        } else {
            WriteComment("Child-Pugh Class score= xxxx");
        }
    }
    WriteActionIfSelected(activeControlPanel, "CirrhosisElastographyOption");


    //////////////////////////////
    // Etiology
    subPlanActionList = [];
    if (MedNote_GetCPOptionBool("CirrhosisViralHepOption")) {
        subPlanActionList.push("Check Hepatitis A IgM, B surface antigen, B core antibody, C antibody");
    }
    if (MedNote_GetCPOptionBool("CirrhosisANAOption")) {
        //subPlanActionList.push("Check ANA");
    }
    if (MedNote_GetCPOptionBool("CirrhosisSmoothMuscleOption")) {
        subPlanActionList.push("Check anti smooth muscle ab");
    }
    if (MedNote_GetCPOptionBool("CirrhosisMitoOption")) {
        subPlanActionList.push("Check anti mitochondrial ab");
    }
    if (MedNote_GetCPOptionBool("CirrhosisFerritinOption")) {
        subPlanActionList.push("Check ferritin");
    }
    if (MedNote_GetCPOptionBool("CirrhosisCeruloplasmOption")) {
        subPlanActionList.push("Check Ceruloplasm");
    }
    if (MedNote_GetCPOptionBool("CirrhosisAntiTyypsinOption")) {
        subPlanActionList.push("Check alpha-1 antitrypsin level and phenotype");
    }
    //WriteAction("Check quantitative immunoglobulins");
    if (subPlanActionList.length > 0) {
        MedNode_WritePlanSubPlan("Cirrhosis", "Etiology", subPlanActionList)
    }


    //////////////////////////////
    // Varices
    subPlanActionList = [];
    if (MedNote_GetCPOptionBool("CirrhosisEGDResultOption")) {
        subPlanActionList.push("Latest endoscopy on xxxxx");
    }
    if (MedNote_GetCPOptionBool("CirrhosisGIBleedOption")) {
        subPlanActionList.push("Manage as discussed under GI bleed");
        subPlanActionList.push("Ceftriaxone 1g IV daily x7days");
    }
    planStr = MedNote_GetCPOptionValue("CirrhosisPropranololOption");
    if ((planStr != null) && (planStr != "")) {
        subPlanActionList.push(planStr);
    }
    if (subPlanActionList.length > 0) {
        MedNode_WritePlanSubPlan("Cirrhosis", "Varices", subPlanActionList)
    }


    //////////////////////////////
    // Ascites
    subPlanActionList = [];
    if (MedNote_GetCPOptionBool("CirrhosisParaResultOption")) {
        subPlanActionList.push("Paracentesis (if any ascites) with labs on the ascitic fluid for albumin, total protein, LDH, cell count and gram-stain/culture to identify source and also rule out SBP");
    }
    if (MedNote_GetCPOptionBool("CirrhosisDopplersOption")) {
        subPlanActionList.push("Abdominal Dopplers to rule out Portal Vein Thrombosis");
    }
    if (MedNote_GetCPOptionBool("CirrhosisExplainDiureticsOption")) {
        subPlanActionList.push("Diuretics (doses in 100:40 ratio up to 400:160). But, do not give diuretics if there is GI bleeding or hepatic encephalopathy or renal dysfunction (avoid hepatorenal)");
    }
    if (MedNote_GetCPOptionBool("CirrhosisLasixOption")) {
        subPlanActionList.push("Furosemide 40mg");
    }
    if (MedNote_GetCPOptionBool("CirrhosisSpironolactoneOption")) {
        subPlanActionList.push("Spironolactone 100mg");
    }

    planStr = MedNote_GetCPOptionValue("CirrhosisSBPAntibioticsOption");
    if ((planStr != null) && (planStr != "")) {
        subPlanActionList.push(planStr);
        //WriteAction("If possible SBP, 3rd generation cephalosporin, preferably Cefotaxime 2g IV Q8h. One study showed Ceftriaxone (1g IV BID x5d)");
        //WriteAction("If no SBP, then prophylaxis with Ceftriaxone 1g IV daily x7days");
        //WriteAction("If Cr over 1.5 and fluid Protein below 1.5, then prophylaxis for life, with Fluoroquinolone");
    }
    if (MedNote_GetCPOptionBool("Cirrhosis2gNaDietOption")) {
        subPlanActionList.push("2g Sodium diet");
    }
    //WriteAction("Albumin 25g weekly");
    if (subPlanActionList.length > 0) {
        MedNode_WritePlanSubPlan("Cirrhosis", "Ascites", subPlanActionList)
    }


    //////////////////////////////
    // Encephalopathy
    subPlanActionList = [];
    subsectionName = "Encephalopathy";
    // The West-Haven Classification Table
    planStr = MedNote_GetCPOptionValue("CirrhosisHEGradeOption");
    if ((planStr != null) && (planStr != "")) {
        subsectionName = subsectionName + " " + planStr;
    }
    planStr = MedNote_GetCPOptionValue("CirrhosisNH3ResultOption");
    if ((planStr != null) && (planStr != "")) {
        subPlanActionList.push(planStr);
    }
    if (MedNote_GetCPOptionBool("CirrhosisLactuloseOption")) {
        subPlanActionList.push("Lactulose 30mL PO TID, titrate for 2-3 stools daily");
    }
    if (MedNote_GetCPOptionBool("CirrhosisRifaximinOption")) {
        subPlanActionList.push("Rifaximin 550mg PO BID");
    }
    if (subPlanActionList.length > 0) {
        MedNode_WritePlanSubPlan("Cirrhosis", subsectionName, subPlanActionList)
    }


    //////////////////////////////
    // Coagulopathy
    subPlanActionList = [];
    subsectionName = "Coaguloatphy";
    if (MedNote_GetCPOptionBool("CirrhosisNoBleedOption")) {
        subsectionName = subsectionName + " - No active signs of bleeding";
    }
    planStr = MedNote_GetCPOptionValue("CirrhosisCheckINROption");
    if ((planStr != null) && (planStr != "")) {
        subPlanActionList.push(planStr);
    }
    if (subPlanActionList.length > 0) {
        MedNode_WritePlanSubPlan("Cirrhosis", subsectionName, subPlanActionList)
    }


    //////////////////////////////
    // Immunity
    subPlanActionList = [];
    planStr = MedNote_GetCPOptionValue("CirrhosisHAVVaccineOption");
    if ((planStr != null) && (planStr != "")) {
        subPlanActionList.push(planStr);
        MedNode_WritePlanSubPlan("Cirrhosis", "Immune Status", subPlanActionList);
    }

    //////////////////////////////
    // HCC Screen
    subPlanActionList = [];
    if (MedNote_GetCPOptionBool("CirrhosisShowHCCResultOption")) {
        subPlanActionList.push("Last abdominal US was xxx");
    }
    planStr = MedNote_GetCPOptionValue("CirrhosisHCCShowAFPOption");
    if ((planStr != null) && (planStr != "")) {
        subPlanActionList.push(planStr);
    }
    planStr = MedNote_GetCPOptionValue("CirrhosisHCCCheckAFPOption");
    if ((planStr != null) && (planStr != "")) {
        subPlanActionList.push(planStr);
    }
    if (subPlanActionList.length > 0) {
        MedNode_WritePlanSubPlan("Cirrhosis", "HCC/PVT screening", subPlanActionList);
    }


    //////////////////////////////
    // NASH
    subPlanActionList = [];
    if (MedNote_GetCPOptionBool("CirrhosisStatinOption")) {
        subPlanActionList.push("Statin - Atorvastatin 40mg");
    }
    if (MedNote_GetCPOptionBool("CirrhosisVitEOption")) {
        subPlanActionList.push("Vitamin E (800 IU/day) but do not give if patient is diabetic");
    }
    if (subPlanActionList.length > 0) {
        MedNode_WritePlanSubPlan("Cirrhosis", "NASH", subPlanActionList)
    }

    //////////////////////////////
    // Nutrition
    subPlanActionList = [];
    if (MedNote_GetCPOptionBool("CirrhosisZincOption")) {
        subPlanActionList.push("Zinc sulfate 220mg BID");
    }
    if (MedNote_GetCPOptionBool("CirrhosisThiamineOption")) {
        subPlanActionList.push("Thiamine");
    }
    if (MedNote_GetCPOptionBool("CirrhosisVitaminOption")) {
        subPlanActionList.push("Multivitamin");    
    }
    if (subPlanActionList.length > 0) {
        MedNode_WritePlanSubPlan("Cirrhosis", "Nutrition", subPlanActionList)
    }



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
// [WriteRespFailurePlan]
//
// NOT USED
////////////////////////////////////////////////////////////////////////////////
function 
WriteRespFailurePlan() {
    MedNote_StartNewPlanSection("Acute Hypoxic and Hypercapnic Respiratory Failure", null);

    WriteComment("The possible causes include: cardiac (CHF, NSTEMI, arrhythmia), pulmonary (COPD, PE, pneumonia), and more");
    WriteComment("Wells score=");

    WriteAction("Check chest XRay");
    WriteAction("Check BNP (Cutoffs are 450 for <50yo, 900 for ages 50-75, 1800 for over 75yo)");
    WriteAction("Doppler U/S bilateral lower extrem");
} // WriteRespFailurePlan






////////////////////////////////////////////////////////////////////////////////
//
// [WriteMigrainePlan]
//
// NOT USED
////////////////////////////////////////////////////////////////////////////////
function
WriteMigrainePlan() {
    MedNote_StartNewPlanSection("Migraines", null);

    WriteComment("Averaging xxx headaches per month");
    WriteComment("The headaches last xxx hours, are unilateral, associated with photophobia and phonophobia.");
    WriteComment("Headaches are often preceeded by an aura.");
    WriteComment("Counseled keeping a headache diary to identify frequency and possible triggers");
    WriteComment("Counseled avoiding common triggers, including cafeine, nicotine, lack of sleep");
    WriteAction("Start headache abortive: sumatriptan");
    WriteAction("Start headache prophylactic: propranolol (current BP is xxx/xxx)");
    WriteAction("Start headache prophylactic: amitriptyline, divalproex, sodium valproate, topiramate");
    WriteAction("Consider headache prophylactics with limited evidence but few adverse effects: magnesium, vitaminB2 (riboflavin), coenzyme Q10");
} // WriteMigrainePlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteApapPlan]
//
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
// [WriteBackPainPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteBackPainPlan() { 
    MedNote_StartNewPlanSection("Back Pain", null);

    WriteComment("Rule out malignancy, abscess, cauda equina (incontinence, saddle paresthesis, fever/chills, weight loss, anticoagulant)");
    WriteComment("Straight leg raise (Herniated disc), more specific when contralateral");
    WriteComment("Is/Isnt relieved by bending (suggesting spinal stenosis)");
    WriteComment("FABER (Flexion,ABduction,External Rotate) - OA causes groin pain, sacroililiatis causes SI pain");
    WriteComment("NSAIDs (Cr=xxx)");
    WriteComment("Gabapentin if neurogenic signs");
    WriteComment("Physical therapy");
    WriteComment("Screen for depression");
    WriteComment("Continue opioids (under narcotic contract, last urine drug screen)");
} // WriteBackPainPlan




////////////////////////////////////////////////////////////////////////////////
//
// [WriteJointPainPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteJointPainPlan() {
    MedNote_StartNewPlanSection("Joint Pain", null);

    // KNEE
    WriteComment("The differential includes trauma: Cruciate ligament tear (ACL,PCL), Meniscal tear (Medial/Lateral), Collateral ligament tear (Medial/Lateral)");
    WriteComment("    Overuse and degeneration: Osteoarthritis, Anserine Bursitis (medial, pain at tibial tuberosity, helps to sleep with pilliw between knees), Iliotibial Band (lateral, worse with walking), Patellofemoral (anterior, worse with bending knee/sitting), Prepatellar bursitis (anterior)");
    WriteComment("    Infection, and autoimmune inflammation");

    WriteComment("Signs of meniscal tear (locking)");
    WriteComment("Signs of anserine bursitis (tender to palpation on proximal medial tibia, sleep with pillow between knees)");
    WriteComment("Lachman and Drawer tests: ");
    WriteComment("McMurray test: ");
    WriteComment("Varus and Valgus stress test tests: ");
    WriteAction("Analgesics: Apap, Capsaicin, Naproxen (Current Cr=), Tramadol");
    WriteAction("Limit aggravating exercises");
    WriteAction("Physical therapy");
    WriteAction("Intraarticular joint injection");
    WriteAction("MRI");
    WriteAction("Refer to ortho (possible");
    WriteAction("Check labs - ESR, CRP, ANA, ant-CCP");

    // Shoulder
    WriteComment("The differential includes overuse and degeneration (Osteoarthritis, Bursitis, Tendonitis), Infection, and autoimmune inflammation");

    // Elbow
    WriteComment("The differential includes overuse and degeneration (Osteoarthritis, Bursitis, Tendonitis), Infection, and autoimmune inflammation");

    // Hip
    WriteComment("The differential includes overuse and degeneration (Osteoarthritis, Bursitis, Tendonitis), Infection, and autoimmune inflammation");

    // General
    WriteComment("The pain has been present for xxx");
    WriteComment(" ");
    WriteComment("This is less likely to be inflammatory. There are no signs of synovitis (erythema, edema, calor, tenderness to palpation)");
    WriteComment("There are no symptoms of inflammation (morning stiffness over 1 hour), and no signs of systemic inflammation - no leukocytosis, normal ESR and normal CRP, no anemia of chronic disease");
    WriteComment("The pain is not significantly reproduced by passive motion, suggesting an extra-articular source such as tendonitis or bursitis.");
} // WriteJointPainPlan




////////////////////////////////////////////////////////////////////////////////
//
// [WritePolyarthropathyPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WritePolyarthropathyPlan() {
    MedNote_StartNewPlanSection("Polyarthropathy", null);

    WriteComment("This involves joints in the hand, wrist, elbow, shoulder, neck, hip, knee, ankle");
    WriteComment("The differential includes Fibromyalgia, autoimmune inflammation, infection");
    WriteComment("The pain is unilateral/bilateral and affects large/small/both large and small joints");

    WriteComment(" ");
    WriteComment("The patient meets American College of Rheumatology criteria for Fibromyalgia with consistent pain for over 3 months and Widespread Pain Index (WPI) over 6 and Symptom Severity (SS) score over 4 or the WPI is 3 to 6 and the SS over 8");
    WriteComment("The WPI and SS questionnaires are found at: http://www.sdhct.nhs.uk/patientcare/proformas/pain/questionnaire%20-%20widespread%20pain%20index%20and%20symptom%20severity%20score.pdf");
    WriteComment("");
    WriteComment("Rule out depression");
    WriteComment("Rule out metabolic and endocrine causes by checking TSH, Vitamin D, Hgb, Magnesium");
    WriteComment("Rule out inflammation by checking ESR, CRP");
    WriteComment("Rule out inflammation by checking ESR, CRP");
} // WritePolyarthropathyPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteChronicPainPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteChronicPainPlan() {
    MedNote_StartNewPlanSection("Chronic Pain", null);

    WriteComment("The pain is in xxx and is better/worse/unchanged compared to previous clinic visit");
    WriteComment("The patient reports the pain affects their functional status - specifically xxx");
    WriteComment("The patient has adverse effects from analgesics - specifically constipation/fatigue/xxx");
    WriteComment("The patient has related substance abuse issues - xxx");
    WriteComment("");
    WriteComment("Patient to complete an objective pain assessment tool - Brief Pain Inventory  (http://www.partnersagainstpain.com/printouts/A7012AS8.pdf)");
    WriteComment("Patient to complete Opioid Risk Tool questionaire (http://iusbirt.org/wp-content/uploads/2012/10/Opioid_Risk_Tool.pdf)");
    WriteComment("The patient has been screened for depression (PHQ-9 score = xxx)");
    WriteComment("");
    WriteComment("I have discussed the goals of pain management (to manage rather than cure the pain) and recommended non-pharmacologic treatments including exercise, local heat, stretching and stress reduction techniques.");
    WriteComment("I have discussed the risks and benefits of analgesics, including dependence, oversedation, and reduced function. The patient has also been instructed to avoid driving and any manual labor while using sedating medications");
    WriteComment("The patient has agreed that their function/activity goals are xxx.");
    WriteComment("The patient has signed a narcotics contract on (xxx) that specified prescribing parameters, drug monitoring, repercussions of aberrant behavior and more");

    WriteAction("Physical therapy");
    WriteAction("Ibuprofen/Napoxen (Cr=xxx)");
    WriteAction("Urine drugs of abuse screen");
    WriteComment("Patient to be reevaluated every 3-4 months to monitor their functional status and medication side effects");
} // WriteChronicPainPlan







////////////////////////////////////////////////////////////////////////////////
//
// [WriteCVVHPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteCVVHPlan() {
    MedNote_StartNewPlanSection("Renal Failure on CVVH", null);

    WriteComment("Access is right IJ Temp dialysis catheter");
    WriteComment("Prescription Fluid: K=4, HCO3=35");
    WriteComment("Prescription Fluid Rate = xxxx mL/hr (30mL/kg/hr, weight xxx kg)");
    WriteComment("Blood flow rate 300 mL/min");
    WriteComment("Ultrafiltration 0 mL/hr");
    WriteComment("Filtration Fraction = xxxxx. Target below 20% to reduce the risk of clotting and losing efficiency (you aren't getting better dialysis)");
    WriteComment("Use Normal Saline as needed to replace losses from drain outputs");
    WriteComment("Do not count any IV fluids given for hypotension in the Intake and Output. You may bolus and not count that fluid volume in the intake/output balance.");
    WriteComment("Anticoag: Heparin x, Protamine x");
    WriteComment("Dialysis Pressures: Venous: x  Arterial: x");
} // WriteCVVHPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteVolumePlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteVolumePlan() {
    MedNote_StartNewPlanSection("Volume Status", null);

    WriteComment("Over the past 24hrs: Intake x mL, Output x mL, Urine output x mL");
    WriteComment("Clinically, appears euvolemic or even hypovolemic, with no rales, JVD or peripheral edema");
    WriteAction("Continue IV volume replacement: xxx");
    WriteAction("Check BNP");
    WriteAction("Check Cardiac Echo");
} // WriteVolumePlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteFreeWaterPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteFreeWaterPlan() {
    MedNote_StartNewPlanSection("Free Water Status", null);

    WriteComment("Na = xxx");
    WriteComment("Free water deficit is xxxx");
} // WriteFreeWaterPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteParathyroidectomyPlan]
//
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
////////////////////////////////////////////////////////////////////////////////
function 
WriteAcidBasePlan() { 
    //LogEvent("Inside WriteAcidBasePlan");
    var planConfigState = null;
    var activeControlPanel = null;
    var str;
    var anionGap = -1;
    var deltaBicarb = -1;
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
    //LogEvent("WriteAcidBasePlan. planConfigState=" + planConfigState);
    if (!planConfigState) {
        return;
    }
    activeControlPanel = planConfigState.activeControlPanel;
    //LogEvent("WriteAcidBasePlan. activeControlPanel=" + activeControlPanel);
    if (!activeControlPanel) {
        return;
    }

    ////////////////////////////////
    // Get all input values
    var currentNa = GetIntInputForControlPanel(activeControlPanel, 'InputNa_CP', null);
    var currentCl = GetIntInputForControlPanel(activeControlPanel, 'InputCl_CP', null);
    var currentBicarb = GetIntInputForControlPanel(activeControlPanel, 'InputBicarb_CP', null);
    var currentAlbumin = GetIntInputForControlPanel(activeControlPanel, 'InputAlbumin_CP', null);
    var currentpH = GetFloatInputForControlPanel(activeControlPanel, 'InputpH_CP', null);
    var currentPaCO2 = GetIntInputForControlPanel(activeControlPanel, 'InputPaCO2_CP', null);
    var currentUrineNa = GetIntInputForControlPanel(activeControlPanel, 'InputUrineNa_CP', null);
    var currentUrineK = GetIntInputForControlPanel(activeControlPanel, 'InputUrineK_CP', null);
    var currentUrineChloride = GetIntInputForControlPanel(activeControlPanel, 'InputUrineCl_CP', null);

    ////////////////////////////////
    // Compute derived values
    if (currentBicarb > 0) {
        deltaBicarb = currentBicarb - 24;
    }
    if ((currentNa > 0) && (currentCl > 0) && (currentBicarb > 0)) {
        anionGap = currentNa - (currentCl + currentBicarb);
        SetStrOutputForControlPanel(activeControlPanel, 'ResultAnionGap_CP', null, 'AnionGap = ' + anionGap);

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
        SetStrOutputForControlPanel(activeControlPanel, 'ResultUrineAnionGap_CP', null, 'Urine Anion Gap = ' + urineAnionGap);
    }


    ////////////////////////////////
    // pH
    if (MedNote_GetCPOptionBool("AcidBaseShowpHOption")) {
        str = AppendNumberToString("The serum pH on an ABG is ", currentpH);
        WriteComment(str);
        if (MedNote_GetCPOptionBool("AcidBaseInterpretpHOption")) {
            if (currentpH < 7.4) {
                WriteComment("This is a primary acidosis, since compensation will only partially restore the pH to 7.35-7.45");
            }
            if (currentpH >= 7.4) {            
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
            str = str + " when adjusted for albimin";
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
        str = "The delta Bicarb is " + deltaBicarb;
        str = str + " and the delta anion gap is " + deltaGap;
        str = str + " (assuming max normal gap is 12)";
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
        var deltaPH = -1;

        str = "The pH is ";
        if (currentpH > 0) {
            str = str + currentpH;
            deltapH = currentpH - 7.4;
        } else {
            str = str + "xxx";
        }
        str = str + AppendNumberToString(", delta pH is ", deltapH);
        str = str + AppendNumberToString(", PaCO2 is ", currentPaCO2);
        str = str + " and delta PaCO2 is ";
        if (currentPaCO2 > 0) {
            str = str + (currentPaCO2 - 40);
        } else {
            str = str + "xxx";
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
            str = str + (predictedPaCO2 - 2) + "-" + (predictedPaCO2 + 2);
        } else {
            str = str + "xxx";
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
        // This estimate only worku to a max PaCO2 is approx 55mm Hg");

        str = AppendNumberToString("The actual PaCO2 is ", currentPaCO2);
        str = str + " and should be approximately ";
        if (deltaBicarb > 0) {
            predictedPaCO2 = 40 + (0.7 * deltaBicarb);
            str = str + predictedPaCO2;
        } else {
            str = str + "xxx";
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
    var optionNameList = [ "AcidBaseDiffIschemiaOption", "AcidBaseDiffUremiaOption", "AcidBaseDiffDKAOption", "AcidBaseDiffEtOHOption", "AcidBaseDiffStarvationOption", "AcidBaseDiffPropofolOption", 
                            "AcidBaseDiffLinezolidOption", "AcidBaseDiffAtivanDripOption", "AcidBaseDiffMetforminOption", "AcidBaseDiffTenofovirOption", "AcidBaseDiffSalicylateOption", 
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
                        "AcidBaseRTAIVDiffTrimethoprimOption", "AcidBaseRTAIVDiffNSAIDsOption", "AcidBaseRTAIVDiffAddisonOption", "AcidBaseRTAIVDiffsickleCellOption", 
                        "AcidBaseRTAIVDiffLupusOption", "AcidBaseRTAIVDiffAmyloidosisOption", "AcidBaseRTAIVDiffPentamidineOption" ];
    WriteListOfSelectedValues(activeControlPanel, "Possible causes of the Renal Tubular Acidosis type IV include: ", false, "", optionNameList, "")

    ////////////////////////////////
    // Metabolic Alkalosis Diff
    optionNameList = [ "AcidBaseDiffDiureticsOption", "AcidBaseDiffVolumeLossOption", "AcidBaseDiffPoorPOOption", "AcidBaseDiffHypercalcemiaOption",
                        "AcidBaseDiffHypokalemiaOption", "AcidBaseDiffHypercapnicCompensationOption", "AcidBaseDiffHyperAldoOption", "AcidBaseDiffCushingsOption",
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
    WriteActionIfSelected(activeControlPanel, "AcidBaseCheckVBGOption");
    WriteActionIfSelected(activeControlPanel, "AcidBaseUrinepHOption");

    ////////////////////////////////
    // Gap Acidosis Workup
    WriteActionIfSelected(activeControlPanel, "AcidBaseCheckLactateOption");
    WriteActionIfSelected(activeControlPanel, "AcidBaseCheckCKOption");
    if (MedNote_GetCPOptionBool("AcidBaseCheckOsmGapOption")) {
        WriteAction("Check volatile alcohol screen (MeOH, Isopropyl, EtOH)");
        WriteAction("Check Osmolar gap: serum Osm to rule out alcohol intoxication");
    }

    ////////////////////////////////
    // Non-Gap Acidosis Workup
    WriteActionIfSelected(activeControlPanel, "AcidBaseCheckUrineLytesOption");
    WriteActionIfSelected(activeControlPanel, "AcidBaseCheckAldoReninOption");

    ////////////////////////////////
    // Metabolic Alkalosis Workup
    WriteActionIfSelected(activeControlPanel, "AcidBaseCheckUClOption");

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
// [NBQuant_ComputeMELD]
//
// MELD = 10 * ((0.957 * ln(Creatinine)) + (0.378 * ln(Bilirubin)) + (1.12 * ln(INR))) + 6.43
// MELD-Na = MELDscore - SerumNa - (0.025 * MELDscore * (140 - SerumNa)) + 140
//
// There may be better scores. See:
// Ming Jiang, Fei Liu, Wu-Jun Xiong, Lan Zhong, and Xi-Mei Chen
// "Comparison of four models for end-stage liver disease in evaluating the prognosis of cirrhosis"
// World J Gastroenterol. 2008 Nov 14; 14(42): 6546–6550.
// https://www.ncbi.nlm.nih.gov/pmc/articles/PMC2773344/
////////////////////////////////////////////////////////////////////////////////
function 
NBQuant_ComputeMELD(INR, sodium, creatinine, Tbili) {
    //LogEvent("NBQuant_ComputeMELD. INR = " + INR);
    //LogEvent("NBQuant_ComputeMELD. sodium = " + sodium);
    //LogEvent("NBQuant_ComputeMELD. creatinine = " + creatinine);
    //LogEvent("NBQuant_ComputeMELD. Tbili = " + Tbili);
    //LogEvent("NBQuant_ComputeMELD. log(10) = " + Math.log(10)); // Used to verify that log() is actually ln()

    if ((INR > 0) && (sodium > 0) && (creatinine > 0) && (Tbili > 0)) {
        var meldScore = 10 * ((0.957 * Math.log(creatinine)) + (0.378 * Math.log(Tbili)) + (1.12 * Math.log(INR)) + 0.643);
        //LogEvent("NBQuant_ComputeMELD. meldScore = " + meldScore);

        meldScore = meldScore - sodium - (0.025 * meldScore * (140 - sodium)) + 140
        //LogEvent("NBQuant_ComputeMELD. meldScore = " + meldScore);

        meldScore = Math.round(meldScore);

        //LogEvent("NBQuant_ComputeMELD. meldScore = " + meldScore);
        return(meldScore);
    }

    return(-1);
} // NBQuant_ComputeMELD






////////////////////////////////////////////////////////////////////////////////
//
// [WriteCHFPlan]
//
// *** Check urine Chloride, daily
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
    LVEF = GetIntInputForControlPanel(activeControlPanel, 'InputLVEF_CP', null);
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
            planStr = planStr + ", " + modifierStr;
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
            planStr = planStr + ", " + modifierStr;
        } else {
            planStr = modifierStr;
        }
    }
    if ((planStr != null) && (planStr != "")) {
        WriteComment(planStr);
    }


    ///////////////////////////////
    // Past Workup
    // Echo
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

    ///////////////////////////////
    // Diuresis
    WriteActionIfSelected(activeControlPanel, 'CHFLasixIVOption');
    WriteActionIfSelected(activeControlPanel, 'CHFLasixPOOption');
    WriteActionIfSelected(activeControlPanel, 'CHFTorsemideOption');
    WriteActionIfSelected(activeControlPanel, 'CHFBumexOption');
    WriteActionIfSelected(activeControlPanel, 'CHFThiazideOption');

    ///////////////////////////////
    // Beta Blockers
    WriteActionIfSelected(activeControlPanel, 'CHFMetoprololTarOption');
    WriteActionIfSelected(activeControlPanel, 'CHFMetoprololSuccOption');
    WriteActionIfSelected(activeControlPanel, 'CHFCarvedilolOption');
    WriteActionIfSelected(activeControlPanel, 'CHFNSBBOption');

    ///////////////////////////////
    // ACE/ARB
    WriteActionIfSelected(activeControlPanel, 'CHFLisinoprilOption');
    WriteActionIfSelected(activeControlPanel, 'CHFLosartanOption');

    planStr = MedNote_GetCPOptionValue("CHFSpironiolactoneOption");
    modifierStr = MedNote_GetCPOptionValue("CHFAldoBlockRestrictionsOption");
    if ((planStr != null) && (planStr != "") && (modifierStr != null) && (modifierStr != "")) {
        planStr = planStr + modifierStr;
    }
    if ((planStr != null) && (planStr != "")) {
        WriteAction(planStr);
    }
    WriteActionIfSelected(activeControlPanel, 'CHFARNIOption');

    ///////////////////////////////
    // SGLT2
    var optionNameList = [ "CHFSGLT2IndicationsDM2Option", "CHFSGLT2IndicationsCKDOption", 
                            "CHFSGLT2IndicationsHFrEFOption", "CHFSGLT2IndicationsUACROver200Option" ]
    WriteListOfSelectedValues(activeControlPanel, "Indications for starting an SGLT2 inhibitor include: ", false, "", optionNameList, "")

    var optionNameList = [ "CHFSGLT2ContraindicationsGFRBelow30Option", "CHFSGLT2ContraindicationsDM1Option",
                            "CHFSGLT2ContraindicationsTransplantOption", "CHFSGLT2ContraindicationsDKAOption",
                            "CHFSGLT2ContraindicationsImunosuppressedOption", "CHFSGLT2ContraindicationsPKDOption",
                            "CHFSGLT2ContraindicationsSLEOption", "CHFSGLT2ContraindicationsANCAOption" ]
    WriteListOfSelectedValues(activeControlPanel, "Do not start an SGLT2 inhibitor due to contraindications: ", false, "", optionNameList, "")
    WriteActionIfSelected(activeControlPanel, "CHFSGLT2EmpagliflozinOption");
    WriteActionIfSelected(activeControlPanel, "CHFSGLT2ReduceInsulinOption");
    WriteActionIfSelected(activeControlPanel, "CHFSGLT2ExplainGFRDropOption");

    ///////////////////////////////
    // ICD
    planStr = MedNote_GetCPOptionValue("CHFICDOption");
    modifierStr = MedNote_GetCPOptionValue("CHFICDIndicationsOption");
    if ((planStr != null) && (planStr != "") && (modifierStr != null) && (modifierStr != "")) {
        planStr = planStr + modifierStr;
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
        LogEvent("WriteOSAPlan. activeControlPanel is null");
        return;
    }

    //////////////////////////
    // Describe the criteria for this diagnosis.
    var optionNameList = [ "SepsisSIRSHROption", "SepsisSIRSTempOption", "SepsisSIRSRROption", "SepsisSIRSWBCOption" ];
    WriteListOfSelectedValues(activeControlPanel, "The patient meets SIRS criteris (", false, "", optionNameList, ")")

    //////////////////////////
    // Describe the possible sources.
    var optionNameList = [ "SepsisUTISourceOption", "SepsisPneumoniaSourceOption", "SepsisCellulitisSourceOption" ];
    WriteListOfSelectedValues(activeControlPanel, "The possible sources of infection include: ", false, "", optionNameList, "")

    // Workup
    WriteActionIfSelected(activeControlPanel, "SepsisWUXRayOption");
    WriteActionIfSelected(activeControlPanel, "SepsisWUBloodCultureOption");
    WriteActionIfSelected(activeControlPanel, "SepsisWUUAOption");
    WriteActionIfSelected(activeControlPanel, "SepsisWUSputumCultureOption");
    WriteActionIfSelected(activeControlPanel, "SepsisWURVPOption");
    WriteActionIfSelected(activeControlPanel, "SepsisWUStoolCultureOption");
    WriteActionIfSelected(activeControlPanel, "SepsisWUStrepUrineAntigenOption");
    WriteActionIfSelected(activeControlPanel, "SepsisWULegionellaUrineAntigenOption");
    WriteActionIfSelected(activeControlPanel, "SepsisWUCDiffOption");
    WriteActionIfSelected(activeControlPanel, "SepsisWUBetaGlucanOption");
    WriteActionIfSelected(activeControlPanel, "SepsisWUGalactomannanOption");
    // Markers
    WriteActionIfSelected(activeControlPanel, "SepsisWUProcalOption");
    WriteActionIfSelected(activeControlPanel, "SepsisWUCRPOption");
    WriteActionIfSelected(activeControlPanel, "SepsisWULactateOption");

    // Imaging
    WriteActionIfSelected(activeControlPanel, "SepsisEchoOption");
    WriteActionIfSelected(activeControlPanel, "SepsisPanorexOption");
    WriteActionIfSelected(activeControlPanel, "SepsisCTAHeadOption");
    WriteActionIfSelected(activeControlPanel, "SepsisCTAAbdomenOption");

    // Fluids/Steroids
    //    WriteAction("IV fluid challenge, starting with 30 mL/Kg initial bolus of crystalloid.");
    planStr = MedNote_GetCPOptionValue("SepsisFluidBolusOption");
    modifierStr = MedNote_GetCPOptionValue("SepsisHighMaintFluidOption");
    if (modifierStr != "") {
        if (planStr != "") {
            planStr = planStr + ", then ";
        }
        planStr = planStr + modifierStr;
    }
    modifierStr = MedNote_GetCPOptionValue("SepsisLowMaintFluidOption");
    if (modifierStr != "") {
        if (planStr != "") {
            planStr = planStr + ", then ";
        }
        planStr = planStr + modifierStr;
    }
    if (planStr != "") {
        WriteAction(planStr);
    }
    WriteActionIfSelected(activeControlPanel, "SepsisStressSteroidsOption");

    // Antibiotics
    var actionNameList = [ "SepsisVancOption", "SepsisPipTazoOption", "SepsisCefepimeOption", "SepsisMetronidazoleOption", "SepsisCeftriaxoneOption"];
    WriteListOfSubActions(activeControlPanel, "Antibiotics", actionNameList);
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

    // Diagnose
    WriteActionIfSelected(activeControlPanel, "OSACheckPFTOption");
    WriteActionIfSelected(activeControlPanel, "OSACheckABGOption");
    WriteActionIfSelected(activeControlPanel, "OSASleepStudyOption");
    WriteActionIfSelected(activeControlPanel, "OSAOvernightOximetryOption");

    // Workup
    WriteActionIfSelected(activeControlPanel, "OSAGetEchoOption");
    WriteActionIfSelected(activeControlPanel, "OSAGetEKGOption");

    // Treat
    WriteActionIfSelected(activeControlPanel, "OSAContinueCPAPOption");
    WriteActionIfSelected(activeControlPanel, "OSAFlonaseOption");
} // WriteOSAPlan



////////////////////////////////////////////////////////////////////////////////
//
// [WriteDyspneaPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteDyspneaPlan() {
    MedNote_StartNewPlanSection("Acute on chronic Hypoxic Respiratory Failure", null);
} // WriteDyspneaPlan




////////////////////////////////////////////////////////////////////////////////
//
// [WriteIllicitDrugsPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteIllicitDrugsPlan() { 
    var planStr = "";
    var planConfigState = null;
    var activeControlPanel = null;
    var problemID = "";
    var problemValue = ""

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
        LogEvent("WriteOSAPlan. activeControlPanel is null");
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
    WriteActionIfSelected(activeControlPanel, "IllicitsCheckUDSOption");
    WriteActionIfSelected(activeControlPanel, "IllicitsCheckHepatitisOption");
    WriteActionIfSelected(activeControlPanel, "IllicitsCheckHIVOption");
    WriteActionIfSelected(activeControlPanel, "IllicitsCheckHepImmpnityOption");

    // Symptoms
    var actionNameList = [ "IllicitsHydroxyzineOption", "IllicitsTrazodoneOption", "IllicitsLoperamideOption", "IllicitsOndansetronOption", "IllicitsMethocarbamolOption", "IllicitsAcetaminophenOption"];
    WriteListOfSubActions(activeControlPanel, "Symptom Management", actionNameList);

    // Consults
    WriteActionIfSelected(activeControlPanel, "IllicitsAddictionMedOption");
    WriteActionIfSelected(activeControlPanel, "IllicitsMusicTherapyOption");
    WriteActionIfSelected(activeControlPanel, "IllicitsNarrativeMedOption");
    WriteActionIfSelected(activeControlPanel, "IllicitsChaplainOption");

    //WriteAction("On discharge, prescribe Narcan");
} // WriteIllicitDrugsPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteGIBleedPlan]
//
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
        LogEvent("WriteOSAPlan. activeControlPanel is null");
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
    WriteActionIfSelected(activeControlPanel, "GIBleedINROption");
    WriteActionIfSelected(activeControlPanel, "GIBleedBUNOption");
    WriteActionIfSelected(activeControlPanel, "GIBleedHemoccultOption");
    WriteActionIfSelected(activeControlPanel, "GIBleedHPyloriOption");

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
        planStr = planStr + modifierStr;
    }
    modifierStr = MedNote_GetCPOptionValue("Diabetes_Uncontrolled_Modifier");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = planStr + " " + modifierStr;
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

    // Workup
    WriteActionIfSelected(activeControlPanel, "DiabetesWorkupGetA1cOption");
    WriteActionIfSelected(activeControlPanel, "DiabetesWorkupGetUrineAlbProtCrOption");

    // Insulin
    WriteActionIfSelected(activeControlPanel, "DiabetesInsulinHoldPOOption");

    // Insulin
    WriteCommentIfSelected(activeControlPanel, "DiabetesInsulinReducedHomeRegimenOption");
    var actionNameList = [ "DiabetesInsulinGlargineOption", "DiabetesInsulinLisproOption", "DiabetesInsulinSlidingScaleOption"];
    WriteListOfSubActions(activeControlPanel, "Insulin", actionNameList);

    // SGLT2
    var optionNameList = [ "DMSGLT2IndicationsDM2Option", "DMSGLT2IndicationsCKDOption", 
                            "DMSGLT2IndicationsHFrEFOption", "DMSGLT2IndicationsUACROver200Option" ]
    WriteListOfSelectedValues(activeControlPanel, "Indications for starting an SGLT2 inhibitor include: ", false, "", optionNameList, "")

    var optionNameList = [ "DMSGLT2ContraindicationsGFRBelow30Option", "DMSGLT2ContraindicationsDM1Option",
                            "DMSGLT2ContraindicationsTransplantOption", "DMSGLT2ContraindicationsDKAOption",
                            "DMSGLT2ContraindicationsImunosuppressedOption", "DMSGLT2ContraindicationsPKDOption",
                            "DMSGLT2ContraindicationsSLEOption", "DMSGLT2ContraindicationsANCAOption" ]
    WriteListOfSelectedValues(activeControlPanel, "Do not start an SGLT2 inhibitor due to contraindications: ", false, "", optionNameList, "")
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
////////////////////////////////////////////////////////////////////////////////
function 
PrintCKDPlan() { 
    var planStr = "";
    var modifierStr = "";
    var activeControlPanel = null;
    var pStr;
    var estGFR = GetLabValue('GFR');

    ///////////////////
    // Start the plan section
    planStr = "Chronic Kidney Disease";
    modifierStr = MedNote_GetCPOptionValue("CKD_Stage_Modifier");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = planStr + ", " + modifierStr;
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


    // Cause
    var optionNameList = [ "CKDCausesDiabetesOption", "CKDCausesHypertensionOption", 
                            "CKDCausesPastAKIOption", "CKDCausesMedicationsOption", "CKDCausesObstructionOption"];
    WriteListOfSelectedValues(activeControlPanel, "Possible original causes include: ", false, "", optionNameList, "")

    // Status
    optionNameList = [ "CKDCausesShowCrOption", "CKDCausesShowGFROption"];
    WriteListOfSelectedFormatStrings(activeControlPanel, optionNameList);
    optionNameList = [ "CKDCausesShowProtCrOption", "CKDCausesShowAlbCrOption"];
    WriteListOfSelectedFormatStrings(activeControlPanel, optionNameList);

    ///////////////////
    // Read Inputs and do Calculations
    var estimatedGFR = GetIntInputForControlPanel(activeControlPanel, 'CKD_INPUT_CP_GFR', null);
    var patientAge = GetIntInputForControlPanel(activeControlPanel, 'CKD_INPUT_CP_AGE', null);
    var urineAlbumin = GetIntInputForControlPanel(activeControlPanel, 'CKD_INPUT_URINE_ALBUMIN', null);
    var urineCr = GetIntInputForControlPanel(activeControlPanel, 'CKD_INPUT_URINE_Cr', null);
    var isMale = 1;
    var sexString = MedNote_GetCPOptionValue("CKD_Male_Modifier");
    if ((sexString != null) && (sexString != "male")) {
        isMale = 0;
    }
    var serumAlbumin = -1;
    var serumCa = -1;
    var serumBicarb = -1;
    var serumPhos = -1;

    // This writes the results in global variables g_2YearESRDRisk and g_5YearESRDRisk
    //LogEvent("Call ComputeRiskOfESRD");
    ComputeRiskOfESRD(patientAge, isMale, estimatedGFR, urineAlbumin, urineCr, serumAlbumin, serumCa, serumBicarb, serumPhos);
    //<>
    if (MedNote_GetCPOptionBool("CKDCausesShow2YrRiskOption")) {
        var est2yrStr = "xxx";
        var est5yrStr = "xxx";
        if (g_2YearESRDRisk > 0) {
            est2yrStr = g_2YearESRDRisk;
        }
        if (g_5YearESRDRisk > 0) {
            est5yrStr = g_5YearESRDRisk;
        }
        WriteComment("The risk of ESRD within two years is " + est2yrStr + " percent, and within five years is " + est5yrStr + " percent");
    }
    WriteCommentIfSelected(activeControlPanel, "CKDCausesRiskPaperCitationOption");
    //optionNameList = [ "CKDCausesDiabetesOption", "CKDStatusTreatHTNOption", "CKDStatusTreatDMOption"];
    //WriteListOfSelectedValues(activeControlPanel, "We will continue to manage the CKD by treating the ", false, "", optionNameList, "")

    ///////////////////////////////
    // Workup
    WriteActionIfSelected(activeControlPanel, "CKDWorkupGetUrineAlbProtCrOption");
    WriteActionIfSelected(activeControlPanel, "CKDWorkupGetPTHOption");
    WriteActionIfSelected(activeControlPanel, "CKDWorkupGetVitDOption");

    ///////////////////////////////
    // General
    WriteActionIfSelected(activeControlPanel, "CKDStatusNoNSAIDsOption");
    WriteActionIfSelected(activeControlPanel, "CKDLisinoprilOption");
    WriteActionIfSelected(activeControlPanel, "CKDLosartanOption");

    ///////////////////////////////
    // SGLT2
    var optionNameList = [ "CKDSGLT2IndicationsDM2Option", "CKDSGLT2IndicationsCKDOption", 
                            "CKDSGLT2IndicationsHFrEFOption", "CKDSGLT2IndicationsUACROver200Option" ]
    WriteListOfSelectedValues(activeControlPanel, "Indications for starting an SGLT2 inhibitor include: ", false, "", optionNameList, "")

    var optionNameList = [ "CKDSGLT2ContraindicationsGFRBelow30Option", "CKDSGLT2ContraindicationsDM1Option",
                            "CKDSGLT2ContraindicationsTransplantOption", "CKDSGLT2ContraindicationsDKAOption",
                            "CKDSGLT2ContraindicationsImunosuppressedOption", "CKDSGLT2ContraindicationsPKDOption",
                            "CKDSGLT2ContraindicationsSLEOption", "CKDSGLT2ContraindicationsANCAOption" ]
    WriteListOfSelectedValues(activeControlPanel, "Do not start an SGLT2 inhibitor due to contraindications: ", false, "", optionNameList, "")
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
    WriteActionIfSelected(activeControlPanel, "CKDFollowupTransplantOption");

    // More General
    WriteActionIfSelected(activeControlPanel, "CKDFollowupRenalOption");

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
    WriteActionIfSelected(activeControlPanel, "CADAtorvaOption");
    WriteActionIfSelected(activeControlPanel, "CADAsaOption");
} // WriteCADPlan






////////////////////////////////////////////////////////////////////////////////
//
// [WriteCOPDPlan]
//
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
    if (MedNote_GetCPOptionBool("COPDExacerbationOption")) {
        MedNote_AddRelatedProblem("Acute Hypoxic and Hypercapnic Respiratory Failure");
    }

    // Exacerbation
    var optionNameList = [ "COPDTriggerDyspneaOption", "COPDTriggerMoreSputumOption", "COPDTriggerPurulentOption"];
    WriteListOfSelectedValues(activeControlPanel, "This is an acute exacerbation with: ", false, "", optionNameList, "")
    //<> WriteComment("The exacerbation is mild(1 criteria) moderate(2 criteria) severe(3 criteria)");

    // Triggers
    var optionNameList = [ "COPDTriggerInfectionOption", "COPDTriggerSmokingOption", "COPDTriggerComplianceOption", "COPDTriggerMedChangesOption"];
    WriteListOfSelectedValues(activeControlPanel, "The possible triggers of this exacerbation include: ", false, "", optionNameList, "")

    // Staging
    var optionNameList = [ "COPDHomeO2Option", "COPDHomeBiPAPOption", "COPDShowFEV1FVC", "COPDShowFEV1", "COPDGOLDGroup", "COPDGOLDClass"];
    WriteListOfSelectedValues(activeControlPanel, "At baseline: ", false, "", optionNameList, "")
    WriteCommentIfSelected(activeControlPanel, "COPDShowEOS");
    //<>WriteComment("BODE Index = (BMI, Obstruction, Dyspnea, Exercise)");

    // Vitals
    var optionNameList = [ "COPDCurrentO2SatsOption", "COPDCurrentO2Option", "COPDCurrentCPAPOption", "COPDO2VBGOption"];
    WriteListOfSelectedValues(activeControlPanel, "Currently: ", false, "", optionNameList, "")

    // Workup
    WriteActionIfSelected(activeControlPanel, "COPDXrayOption");
    WriteActionIfSelected(activeControlPanel, "COPDGetVBGOption");
    WriteActionIfSelected(activeControlPanel, "COPDGetRVPOption");
    WriteActionIfSelected(activeControlPanel, "COPDCultureSputOption");
    WriteActionIfSelected(activeControlPanel, "COPDCultureBloodOption");
    WriteActionIfSelected(activeControlPanel, "COPDUrineAntigensOption");
    WriteActionIfSelected(activeControlPanel, "COPDProcalOption");

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

//        <td><input type="button" id="COPDHomeMedsOption" value="HomeMeds" class="CPOptionDisabledStyle" toggleState="-1" onclick="MedNote_OnCPOptionButton(this)" /></td>
//    WriteActionIfSelected(activeControlPanel, "COPDHomeMedsOption": { "ButtonLabelList" : ["HomeMeds"], "ValueList" : ["Home medications: "], "htmlButton" : null, "toggleBehavior" : "OK/Other/NA", "toggleState" : -1, "InitialToggleState" : -1, "savedToggleState" : 0, "PlanSectionID" : "COPDPlan"},
} // WriteCOPDPlan







////////////////////////////////////////////////////////////////////////////////
//
// [WriteHemodialysisPlan]
//
// Updated 2020-4-3 - combined PD and HD
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
////////////////////////////////////////////////////////////////////////////////
function 
WritePneumoniaPlan() {
    var pStr;    
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
        LogEvent("xxxxx. activeControlPanel is null");
        return;
    }

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
    WriteActionIfSelected(activeControlPanel, "PneumoniaWUBloodCultureOption");
    WriteActionIfSelected(activeControlPanel, "PneumoniaWUSputumCultureOption");
    WriteActionIfSelected(activeControlPanel, "PneumoniaWURVPOption");

    WriteActionIfSelected(activeControlPanel, "PneumoniaWUMRSANaresOption");
    WriteActionIfSelected(activeControlPanel, "PneumoniaWUStrepUrineAntigenOption");
    WriteActionIfSelected(activeControlPanel, "PneumoniaWULegionellaUrineAntigenOption");
    WriteActionIfSelected(activeControlPanel, "PneumoniaWUProcalOption");
    WriteActionIfSelected(activeControlPanel, "PneumoniaWUCRPOption");
    WriteActionIfSelected(activeControlPanel, "PneumoniaWULactateOption");

    WriteActionIfSelected(activeControlPanel, "PneumoniaSwallowStudyOption");
    WriteActionIfSelected(activeControlPanel, "PneumoniaPanorexOption");

    // Antibiotics
    var actionNameList = [ "PneumoniaVancOption", "PneumoniaPipTazoOption", "PneumoniaCefepimeOption", "PneumoniaMetronidazoleOption", "PneumoniaCeftriaxoneOption", "PneumoniaAzithromycinOption"];
    WriteListOfSubActions(activeControlPanel, "Antibiotics", actionNameList);

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
////////////////////////////////////////////////////////////////////////////////
function 
WriteStrokePlan() {
    var pStr;    
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

    WriteActionIfSelected(activeControlPanel, "StrokeGetA1cOption");
    WriteActionIfSelected(activeControlPanel, "StrokeGetLDLOption");
    WriteActionIfSelected(activeControlPanel, "StrokeGetINROption");
    WriteActionIfSelected(activeControlPanel, "StrokeGetSMEAROption");
    WriteActionIfSelected(activeControlPanel, "StrokeGetHaptoglobinsOption");
    WriteActionIfSelected(activeControlPanel, "StrokeGetLDHOption");

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
    var pStr;    
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
        planStr = planStr + modifierStr;
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
////////////////////////////////////////////////////////////////////////////////
function 
WriteAsthmaPlan() {
    var pStr;    
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
    WriteActionIfSelected(activeControlPanel, "AsthmaGetCBCOption"); 
    WriteActionIfSelected(activeControlPanel, "AsthmaGetRVPOption"); 
    WriteActionIfSelected(activeControlPanel, "AsthmaProcalOption"); 
    WriteActionIfSelected(activeControlPanel, "AsthmaCultureSputOption"); 
    WriteActionIfSelected(activeControlPanel, "AsthmaCultureBloodOption"); 
    WriteActionIfSelected(activeControlPanel, "AsthmaUrineAntigensOption"); 
 
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
    var pStr;    
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
////////////////////////////////////////////////////////////////////////////////
function 
WriteNephrolithiasisPlan() {
    var pStr;    
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
////////////////////////////////////////////////////////////////////////////////
function 
WriteNephroticPlan() {
    var pStr;    
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

    if ((urineProtein > 0) && (urineCreatinine > 0)) {
        var urintProtCrRatio = urineProtein / urineCreatinine;
        SetStrOutputForControlPanel(activeControlPanel, 'ResultUPCRCP', null, 'urintProtCrRatio = ' + urintProtCrRatio);
    }
    if ((urineAlbumin > 0) && (urineCreatinine > 0)) {
        var urintAlbCrRatio = urineAlbumin / urineCreatinine;
        SetStrOutputForControlPanel(activeControlPanel, 'ResultNonAlbuminUPCR', null, 'urintAlbCrRatio = ' + urintAlbCrRatio);
    }


    // Labs
    WriteCommentIfSelected(activeControlPanel, "NephroticShowUrineProtOption"); 
    WriteCommentIfSelected(activeControlPanel, "NephroticShowUrineAlbOption"); 
    WriteCommentIfSelected(activeControlPanel, "NephroticShowUrineCrOption"); 
    WriteCommentIfSelected(activeControlPanel, "NephroticShow24hrUrineProtOption"); 
    WriteCommentIfSelected(activeControlPanel, "NephroticShowSerumAlbuminOption"); 
    WriteCommentIfSelected(activeControlPanel, "NephroticExplainRatioOption"); 
 
    // Etiology
    var optionNameList = [ "NephroticDiffDiabetesOption", "NephroticDiffSLEOption", "NephroticDiffHepBOption", "NephroticDiffHepCOption", "NephroticDiffHIVOption", "NephroticDiffAmyloidosis", "NephroticDiffPreeclampsiaOption", "NephroticDiffFSGSOption", "NephroticDiffMembranousOption", "NephroticDiffMinimalChangeOption", "NephroticDiffNSAIDsOption", "NephroticDiffTamoxifenOption", "NephroticDiffLithiumOption"];
    WriteListOfSelectedValues(activeControlPanel, "The differential includes: ", false, "", optionNameList, "");


    // Workup
    WriteActionIfSelected(activeControlPanel, "NephroticWorkupA1cOption");
    WriteActionIfSelected(activeControlPanel, "NephroticWorkupLightChainsOption");
    WriteActionIfSelected(activeControlPanel, "NephroticWorkupSPEPOption");
    WriteActionIfSelected(activeControlPanel, "NephroticWorkupRheumatoidFactorOption");
    WriteActionIfSelected(activeControlPanel, "NephroticWorkupCryoglobulinsOption");
    WriteActionIfSelected(activeControlPanel, "NephroticWorkupANAOption");
    WriteActionIfSelected(activeControlPanel, "NephroticWorkupC3C4Option");
    WriteActionIfSelected(activeControlPanel, "NephroticWorkupAntiGBMOption");
    WriteActionIfSelected(activeControlPanel, "NephroticWorkupPLA2ROption");
    WriteActionIfSelected(activeControlPanel, "NephroticWorkupHIVOption");
    WriteActionIfSelected(activeControlPanel, "NephroticWorkupHepBOption");
    WriteActionIfSelected(activeControlPanel, "NephroticWorkupHepCOption");
    WriteActionIfSelected(activeControlPanel, "NephroticWorkupSyphilisOption");

    // Treat
    WriteActionIfSelected(activeControlPanel, "NephroticTreatLasixPOOption");
    WriteActionIfSelected(activeControlPanel, "NephroticTreatACEOption");
    WriteCommentIfSelected(activeControlPanel, "NephroticTreatExplainACEOption");
    WriteActionIfSelected(activeControlPanel, "NephroticTreatAnticoagulationOption");
    WriteCommentIfSelected(activeControlPanel, "NephroticTreatCriteriaAnticoagulationOption");

    WriteActionIfSelected(activeControlPanel, "NephroticTreatCancerScreenOption");
    WriteActionIfSelected(activeControlPanel, "NephroticTreatCheckTSHOption");
    WriteActionIfSelected(activeControlPanel, "NephroticTreatCheckLDLOption");
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
    var pStr;    
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Alcohol Abuse";
    if (PrintSingleLinePlanAtEnd('EtOHPlan', planStr, "Monitor for withdrawal")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "EtOHPlan");
    if (!activeControlPanel) {
        LogEvent("xxxxx. activeControlPanel is null");
        return;
    }

    var optionNameList = [ "EtOHDailyUseOption", "EtOHLastUseOption"];
    WriteListOfSelectedValues(activeControlPanel, "", false, "", optionNameList, "")

    planStr = MedNote_GetCPOptionValue("EtOHPastWithdrawalsOption");
    if ((planStr != null) && (planStr != "")) {
        modifierStr = MedNote_GetCPOptionValue("EtOHPastSeizuresOption");
        if ((modifierStr != null) && (modifierStr != "")) {
            planStr = planStr + " " + modifierStr;
        }
        WriteComment(planStr);
    }

    WriteActionIfSelected(activeControlPanel, "EtOHCIWAOption");
    WriteActionIfSelected(activeControlPanel, "EtOHThiamineOption");
    WriteActionIfSelected(activeControlPanel, "EtOHVitaminsOption");
    //Chlorthiazepoxide
} // WriteEtOHPlan






////////////////////////////////////////////////////////////////////////////////
//
// [WriteHypokalemiaPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteHypokalemiaPlan() {    
    var pStr;    
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Hypokalemia";
    if (PrintSingleLinePlanAtEnd('HypokalemiaPlan', planStr, "Monitor and replace as needed")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "HypokalemiaPlan");
    if (!activeControlPanel) {
        LogEvent("xxxxx. activeControlPanel is null");
        return;
    }

    WriteCommentIfSelected(activeControlPanel, 'LowPotassiumShowKOption');
    WriteCommentIfSelected(activeControlPanel, 'LowPotassiumShowMgOption');
    WriteCommentIfSelected(activeControlPanel, 'LowPotassiumShowUrClOption');
    WriteCommentIfSelected(activeControlPanel, 'LowPotassiumShowTTKGOption');
    WriteCommentIfSelected(activeControlPanel, 'LowPotassiumTTKGFormulaOption');
    WriteCommentIfSelected(activeControlPanel, 'LowPotassiumExplainLowTTKGOption');
    WriteCommentIfSelected(activeControlPanel, 'LowPotassiumInterpretUrClOption');
    WriteCommentIfSelected(activeControlPanel, 'LowPotassiumExplainUrClOption');

    var optionNameList = [ "LowPotassiumCausesDiarrheaOption", "LowPotassiumCausesRenalOption", "LowPotassiumCausesDiureticsOption", "LowPotassiumCausesLowMgOption", "LowPotassiumCausesHighAldoOption", "LowPotassiumCausesHyperAaldoOption", "LowPotassiumCausesRASOption", "LowPotassiumCausesMalnutritionOption", "LowPotassiumCausesTubeFeedsOption" ];
    WriteListOfSelectedValues(activeControlPanel, "Possible causes include: ", false, "", optionNameList, "");

    WriteActionIfSelected(activeControlPanel, "LowPotassiumCheckMgOption");
    WriteActionIfSelected(activeControlPanel, "LowPotassiumCheckUrChlorideOption");
    WriteActionIfSelected(activeControlPanel, "LowPotassiumCheckULytesOption");
    WriteActionIfSelected(activeControlPanel, "LowPotassiumRepleteKOption");
    WriteActionIfSelected(activeControlPanel, "LowPotassiumRepleteMgOption");
} // WriteHypokalemiaPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteHypERkalemiaPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteHypERkalemiaPlan() {
    var pStr;    
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Hyperkalemia";
    if (PrintSingleLinePlanAtEnd('HyperkalemiaPlan', planStr, "Monitor")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "HyperkalemiaPlan");
    if (!activeControlPanel) {
        LogEvent("xxxxx. activeControlPanel is null");
        return;
    }

    WriteCommentIfSelected(activeControlPanel, 'HighPotassiumShowKOption');
    WriteCommentIfSelected(activeControlPanel, 'HighPotassiumShowEKGOption');
    WriteCommentIfSelected(activeControlPanel, 'HighPotassiumShowTTKGOption');
    WriteCommentIfSelected(activeControlPanel, 'HighPotassiumTTKGFormulaOption');
    WriteCommentIfSelected(activeControlPanel, 'HighPotassiumExplainLowTTKGOption');

    var optionNameList = [ "HighPotassiumEtiologyRTA4Option", "HighPotassiumEtiologySeizuresOption", "HighPotassiumEtiologyTumorLysisOption", "HighPotassiumEtiologySaltSubstituteOption", "HighPotassiumEtiologyDigoxinOption" ];
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
////////////////////////////////////////////////////////////////////////////////
function 
PrintHyperNatremiaPlan() {    
    var pStr;    
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Hypernatremia";
    if (PrintSingleLinePlanAtEnd('HypERnatremiaPlan', planStr, "Continue free water")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "HypERnatremiaPlan");
    if (!activeControlPanel) {
        LogEvent("xxxxx. activeControlPanel is null");
        return;
    }

    WriteCommentIfSelected(activeControlPanel, 'HighNaExplainOption');
    WriteCommentIfSelected(activeControlPanel, 'HighNaShowNaOption');
    WriteCommentIfSelected(activeControlPanel, 'HighNaShowUOsmOption');
    WriteCommentIfSelected(activeControlPanel, 'HighNaExplainUOsmOption');
    WriteCommentIfSelected(activeControlPanel, 'HighNaFreeWaterDeficitOption');
    WriteCommentIfSelected(activeControlPanel, 'HighNaFreewaterClearanceOption');
    WriteCommentIfSelected(activeControlPanel, 'HighNaExplainWaterClearanceOption');

    var optionNameList = [ "HighNaCausesLowIntakeOption", "HighNaCausesDiarreaOption", "HighNaCausesBurnsOption", "HighNaCausesPostATNOption", "HighNaCausesTPNOption", "HighNaCausesLithiumOption", "HighNaCausesCisplatinOption" ];
    WriteListOfSelectedValues(activeControlPanel, "Possible causes include: ", false, "", optionNameList, "");

    WriteActionIfSelected(activeControlPanel, "HighNaGetUOsmOption");
    WriteActionIfSelected(activeControlPanel, "HighNaGetULytesOption");
    WriteActionIfSelected(activeControlPanel, "HighNaGiveD5WOption");
    WriteActionIfSelected(activeControlPanel, "HighNaDDAVPOption");
} // PrintHyperNatremiaPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteHypomagnesemiaPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteHypomagnesemiaPlan() { 
    var pStr;    
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Hypomagnesemia";
    if (PrintSingleLinePlanAtEnd('HypomagnesemiaPlan', planStr, "Monitor and replace as needed")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "HypomagnesemiaPlan");
    if (!activeControlPanel) {
        LogEvent("xxxxx. activeControlPanel is null");
        return;
    }

    WriteCommentIfSelected(activeControlPanel, 'LowMgShowMgOption');

    WriteActionIfSelected(activeControlPanel, "LowMgCheckUrineOption");
    WriteActionIfSelected(activeControlPanel, "LowMgRepleteOption");
} // WriteHypomagnesemiaPlan




////////////////////////////////////////////////////////////////////////////////
//
// [WriteHypoPhosPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteHypoPhosPlan() { 
    var pStr;    
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "HypoPhosphatemia";
    if (PrintSingleLinePlanAtEnd('HypoPhosPlan', planStr, "Monitor and replace as needed")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "HypoPhosPlan");
    if (!activeControlPanel) {
        LogEvent("xxxxx. activeControlPanel is null");
        return;
    }

    WriteCommentIfSelected(activeControlPanel, 'LowPhosShowPhosOption');
    WriteCommentIfSelected(activeControlPanel, 'LowPhosShowCalciumOption');

    WriteActionIfSelected(activeControlPanel, "LowPhosCheckUrineOption");
    WriteActionIfSelected(activeControlPanel, "LowPhosRepleteOption");
    WriteActionIfSelected(activeControlPanel, "LowPhosFixCalOption");
} // WriteHypoPhosPlan




////////////////////////////////////////////////////////////////////////////////
//
// [WriteHypoCalcemiaPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteHypoCalcemiaPlan() { 
    var pStr;    
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "HypoCalcemia";
    if (PrintSingleLinePlanAtEnd('HypoCalcemiaPlan', planStr, "Monitor and replace as needed")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "HypoCalcemiaPlan");
    if (!activeControlPanel) {
        LogEvent("WriteHypoCalcemiaPlan. activeControlPanel is null");
        return;
    }

    WriteCommentIfSelected(activeControlPanel, 'LowCalciumShowCaOption');
    WriteCommentIfSelected(activeControlPanel, 'LowCalciumShowiCalOption');

    WriteActionIfSelected(activeControlPanel, "LowCalciumCheckiCalOption");
    WriteActionIfSelected(activeControlPanel, "LowCalciumCheckVitaminOption");
    WriteActionIfSelected(activeControlPanel, "LowCalciumCheckPTHOption");
    WriteActionIfSelected(activeControlPanel, "LowCalciumCheckUrineOption");
    WriteActionIfSelected(activeControlPanel, "LowCalciumRepleteOption");
} // WriteHypoCalcemiaPlan






////////////////////////////////////////////////////////////////////////////////
//
// [WriteHypERCalcemiaPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteHypERCalcemiaPlan() { 
    var pStr;    
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "HyperCalcemia";
    if (PrintSingleLinePlanAtEnd('HypERCalcemiaPlan', planStr, "IV fluids")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "HypERCalcemiaPlan");
    if (!activeControlPanel) {
        LogEvent("WriteHypERCalcemiaPlan. activeControlPanel is null");
        return;
    }

    WriteCommentIfSelected(activeControlPanel, 'HighCalciumShowCaOption');
    WriteCommentIfSelected(activeControlPanel, 'HighCalciumShowiCalOption');
    WriteCommentIfSelected(activeControlPanel, 'HighCalciumShowPTHOption');

    WriteActionIfSelected(activeControlPanel, "HighCalciumCheckiCalOption");
    WriteActionIfSelected(activeControlPanel, "HighCalciumCheckVitaminOption");
    WriteActionIfSelected(activeControlPanel, "HighCalciumCheckPTHrPOption");
    WriteActionIfSelected(activeControlPanel, "HighCalciumCheckPTHOption");
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
    var pStr;    
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

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
    var pStr;    
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

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

    //if ((!GetLabValue("IsMale")) && (patientAge >= 65) && (patientAge <= 75)) {
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
    var pStr;    
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
        planStr = planStr + modifierStr;
    }
    modifierStr = MedNote_GetCPOptionValue("ONCOLOGY_NEWLY_DIAGNOSED_MODIFIER");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = planStr + modifierStr;
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
    WriteListOfSubActions(activeControlPanel, "Antiemetics", actionNameList);

    var actionNameList = [ "ONCOLOGY_MORPHINE_ER_OPTION", "ONCOLOGY_OXYCODONE_LR_OPTION", "ONCOLOGY_FENTANYL_OPTION", "ONCOLOGY_Prednisone_OPTION", "ONCOLOGY_MORPHINE_IR_OPTION",
                        "ONCOLOGY_Oxycodone_OPTION", "ONCOLOGY_Dilaudid_PO_OPTION", "ONCOLOGY_Dilaudid_IV_OPTION", "ONCOLOGY_PCA_OPTION"];
    WriteListOfSubActions(activeControlPanel, "Pain Control", actionNameList);

    var actionNameList = [ "ONCOLOGY_DOCSENNA_OPTION", "ONCOLOGY_MIRALAX_OPTION", "ONCOLOGY_MgCitrate_OPTION", "ONCOLOGY_Lactulose_OPTION"];
    WriteListOfSubActions(activeControlPanel, "Bowel Regimen", actionNameList);

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
    var pStr;    
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
    WriteListOfSubActions(activeControlPanel, "Antiemetics", actionNameList);

    var actionNameList = [ "PALLIATIVE_MORPHINE_ER_OPTION", "PALLIATIVE_OXYCODONE_LR_OPTION", "PALLIATIVE_FENTANYL_OPTION", "PALLIATIVE_Prednisone_OPTION", 
                        "PALLIATIVE_MORPHINE_IR_OPTION", "PALLIATIVE_Oxycodone_OPTION", "PALLIATIVE_Dilaudid_PO_OPTION", "PALLIATIVE_Dilaudid_IV_OPTION", "PALLIATIVE_PCA_OPTION"];
    WriteListOfSubActions(activeControlPanel, "Pain Control", actionNameList);

    var actionNameList = [ "PALLIATIVE_DOCSENNA_OPTION", "PALLIATIVE_MIRALAX_OPTION", "PALLIATIVE_MgCitrate_OPTION", "PALLIATIVE_Lactulose_OPTION"];
    WriteListOfSubActions(activeControlPanel, "Bowel Regimen", actionNameList);
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
        planStr = planStr + " (" + wordListStr + ") ";
    }
    if (riskStr) {
        planStr = planStr + " which suggests a " + percentRisk + " percent risk of "  + riskStr;
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

        //LogEvent("ComputeScoreFromSelectedValues. Check option: " + currentOptionName);
        //LogEvent("ComputeScoreFromSelectedValues. currentOptionValue: " + currentOptionValue);
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
    var pStr;    
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
    var percentRiskList = [ "0,1", "0.3", "0.5", "1", "2.3", "2.6", "8", "9.8", "14", "17", "19.5", "38.9", "25"];
    WriteScoreFromSelectedValues(
                activeControlPanel, 
                optionNameList, 
                scorePointList, 
                percentRiskList, 
                0,
                "The patient has ", 
                "renal risk factors", 
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
                "renal risk factors", 
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
    var pStr;    
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
////////////////////////////////////////////////////////////////////////////////
function 
WriteHepatitisCPlan() {
    var pStr;    
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

    WriteActionIfSelected(activeControlPanel, "HEPC_CHECK_VIRAL_LOAD_OPTION");
    WriteActionIfSelected(activeControlPanel, "HEPC_CHECK_GENOTYPE_OPTION");
    WriteActionIfSelected(activeControlPanel, "HEPC_CHECK_HIV_OPTION");
    WriteActionIfSelected(activeControlPanel, "HEPC_CHECK_HAV_OPTION");
    WriteActionIfSelected(activeControlPanel, "HEPC_CHECK_HBV_OPTION");

    WriteActionIfSelected(activeControlPanel, "HEPC_TREAT_HAV_VACCINE_OPTION");
    WriteActionIfSelected(activeControlPanel, "HEPC_TREAT_HBV_VACCINE_OPTION");
    WriteActionIfSelected(activeControlPanel, "HEPC_TREAT_GI_CLINIC_OPTION");
} // WriteHepatitisCPlan







////////////////////////////////////////////////////////////////////////////////
//
// [WriteEncephalopathyPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteEncephalopathyPlan() {
    var pStr;    
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

    //WriteComment("The patient has been intubated to protect their airway");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_HEAD_CT_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_Prolactin_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_EEG_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_INTOXICATION_CHECK_EtOH_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_INTOXICATION_CHECK_UDS_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_INTOXICATION_CHECK_Salicylate_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_INTOXICATION_CHECK_acetaminophen_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_INTOXICATION_CHECK_Serum_OSM_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_INTOXICATION_CHECK_Acidosis_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_Blood_CX_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_Urine_CX_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_CXR_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_Glucose_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_A1c_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_CMP_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_SERUM_OSM_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_NH3_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_CPK_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_VMG_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_CO_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_TSH_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_Gabapentin_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_Lithium_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_Digoxin_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_Amitriptylene_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_Thiamine_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_Lorazepam_OPTION");
    WriteActionIfSelected(activeControlPanel, "AMS_CHECK_Haloperidol_OPTION");
} // WriteEncephalopathyPlan






////////////////////////////////////////////////////////////////////////////////
//
// [WriteMBDPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteMBDPlan() {
    var pStr;    
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Metabolic Bone Disease";
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "MBDPlan");
    if (!activeControlPanel) {
        LogEvent("WriteMBDPlan. activeControlPanel is null");
        return;
    }

    var optionNameList = [ "MBD_OPTION_SHOW_Phos", "MBD_OPTION_SHOW_PTH", "MBD_OPTION_SHOW_Ca", "MBD_OPTION_SHOW_Mod_Ca"];
    WriteListOfSelectedValues(activeControlPanel, "", false, "", optionNameList, "")

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
    var pStr;    
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

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
    var pStr;    
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
// Updated 2020-4-19
////////////////////////////////////////////////////////////////////////////////
function 
WriteHepatitisPlan() {
    var pStr;    
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

//    var currentPT = GetIntInputForControlPanel(activeControlPanel, 'InputPT_CP', null);
//    var currentINR = GetIntInputForControlPanel(activeControlPanel, 'InputINR_CP', null);
//    var currentCr = GetIntInputForControlPanel(activeControlPanel, 'InputCreatinine_CP', null);
//    var currentTbili = GetIntInputForControlPanel(activeControlPanel, 'InputTBili_CP', null);
//    var MaddreyScore = NBQuant_ComputeMaddrey(currentPT, currentCr, currentTbili);
//    if (MaddreyScore >= 0) {
        //SetStrOutputForControlPanel(activeControlPanel, 'Maddrey_CP', null, 'Maddrey = ' + MaddreyScore);
//    }


    // Status
    WriteCommentIfSelected(activeControlPanel, "HEPATITIS_ALTAST_OPTION");
    WriteCommentIfSelected(activeControlPanel, "HEPATITIS_Trend_OPTION");
    WriteCommentIfSelected(activeControlPanel, "HEPATITIS_Maddrey_OPTION");
    // Diff
    var optionNameList = [ "HEPATITIS_Diff_Viral_OPTION", "HEPATITIS_Alcohol_OPTION", "HEPATITIS_Dif_Toxicity_OPTION", "HEPATITIS_Autoimmune_OPTION"];
    WriteListOfSelectedValues(activeControlPanel, "Possible causes include: ", false, "", optionNameList, "")

    // Workup
    WriteActionIfSelected(activeControlPanel, "HEPATITIS_CheckHepAIgG_OPTION");
    WriteActionIfSelected(activeControlPanel, "HEPATITIS_CheckHepAIgM_OPTION");
    WriteActionIfSelected(activeControlPanel, "HEPATITIS_CheckHepBIgAg_OPTION");
    WriteActionIfSelected(activeControlPanel, "HEPATITIS_CheckHepBPCR_OPTION");
    WriteActionIfSelected(activeControlPanel, "HEPATITIS_CheckHepDIgG_OPTION");
    WriteActionIfSelected(activeControlPanel, "HEPATITIS_CheckHepEIgG_OPTION");
    WriteActionIfSelected(activeControlPanel, "HEPATITIS_CheckCeruloplasm_OPTION");
    WriteActionIfSelected(activeControlPanel, "HEPATITIS_CheckApap_OPTION");
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
    var pStr;    
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
// [WriteGoutPlan]
//
////////////////////////////////////////////////////////////////////////////////
function 
WriteGoutPlan() {
    var pStr;    
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

    // GOUT
    // Status
    WriteCommentIfSelected(activeControlPanel, "GOUT_FLARING_OPTION");
    WriteCommentIfSelected(activeControlPanel, "GOUT_LAST_FLARE_OPTION");
    WriteCommentIfSelected(activeControlPanel, "GOUT_SHOW_URATE_OPTION");

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
////////////////////////////////////////////////////////////////////////////////
function 
WriteSyncopePlan() {
    var pStr;    
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
    WriteActionIfSelected(activeControlPanel, "SYNCOPE_GET_EKG_OPTION");
    WriteActionIfSelected(activeControlPanel, "SYNCOPE_UDS_OPTION");
    WriteActionIfSelected(activeControlPanel, "SYNCOPE_Interrogate_ICD_OPTION");
    WriteActionIfSelected(activeControlPanel, "SYNCOPE_Telemetry_OPTION");
    WriteActionIfSelected(activeControlPanel, "SYNCOPE_EEG_OPTION");
    WriteActionIfSelected(activeControlPanel, "SYNCOPE_CT_HEAD_OPTION");
    WriteActionIfSelected(activeControlPanel, "SYNCOPE_BLOOD_CULTURES_OPTION");
    WriteActionIfSelected(activeControlPanel, "SYNCOPE_PROCAL_OPTION");
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
    var pStr;    
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Pressure Ulcer";
    modifierStr = MedNote_GetCPOptionValue("PressureUlcer_StageOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = planStr + " " + modifierStr;
    }
    planStr = planStr + " (Present on admission)";

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
    var pStr;    
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

    var optionNameList = [ "DIC_Diagnose_ISTH_PLTS_Option", "DIC_Diagnose_ISTH_PT_Option", "DIC_Diagnose_ISTH_Fibrinogen_Option", "DIC_Diagnose_ISTH_D_DIMER_Option"];
    WriteListOfSelectedValues(activeControlPanel, "ISTH  include: ", false, "", optionNameList, "")

    // Status
    WriteCommentIfSelected(activeControlPanel, "DICHgbTrendOption");
    WriteCommentIfSelected(activeControlPanel, "DICPlateletTrendOption");
    WriteCommentIfSelected(activeControlPanel, "DICINRTrendOption");
    WriteCommentIfSelected(activeControlPanel, "DICFibrinogenOption");
    WriteCommentIfSelected(activeControlPanel, "DICDDimerTrendOption");

    // Monitor
    WriteActionIfSelected(activeControlPanel, "DIC_Check_CBC_Option");
    WriteActionIfSelected(activeControlPanel, "DIC_Check_Fibrinogen_Option");
    WriteActionIfSelected(activeControlPanel, "DIC_Check_INR_Option");
    WriteActionIfSelected(activeControlPanel, "DIC_Check_DDimer_Option");

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
    MedNote_AddRelatedProblem("Acute hypoxic respiratory failure secondary to COVID 19");


    // Get the control panel. 
    // This was set up by the call to MedNote_StartNewPlanSection.
    planConfigState = g_AllPlansDeclaration['CovidPlan'];
    activeControlPanel = planConfigState.activeControlPanel;
    if (!activeControlPanel) {
        LogEvent("WriteCovidPlan. activeControlPanel is null");
        return;
    }

    // Symptoms
    var optionNameList = [ "CovidFeversOption", "CovidCoughOption", "CovidDyspneaOption", "CovidDiarrheaOption", "CovidMyalgiaOption"];
    WriteListOfSelectedValues(activeControlPanel, "Symptoms include: ", false, "", optionNameList, "")

    // History
    WriteCommentIfSelected(activeControlPanel, "CovidSxStartedOption");
    WriteCommentIfSelected(activeControlPanel, "CovidTestPositiveOption");

    // Status
    WriteCommentIfSelected(activeControlPanel, "CovidCRPTrendOption");
    WriteCommentIfSelected(activeControlPanel, "CovidPMNToLymphTrendOption");
    WriteCommentIfSelected(activeControlPanel, "CovidSpO2TrendOption");
    WriteCommentIfSelected(activeControlPanel, "CovidDDimerTrendOption");
    WriteCommentIfSelected(activeControlPanel, "CovidLDHTrendOption");
    //WriteCommentIfSelected(activeControlPanel, "CovidFibrinogenTrendOption");

    // Workup
    WriteActionIfSelected(activeControlPanel, "CovidWUPCROption");
    WriteActionIfSelected(activeControlPanel, "CovidWUXRayOption");
    WriteActionIfSelected(activeControlPanel, "CovidWUProcalOption");
    WriteActionIfSelected(activeControlPanel, "CovidWURVPOption");
    //WriteActionIfSelected(activeControlPanel, "CovidWUBloodCultureOption");
    //WriteActionIfSelected(activeControlPanel, "CovidWUSputumCultureOption");

    // Monitor
    // "CovidWUDDimerOption", "CovidLDHDailyOption",  "CovidFibrinogenDailyOption", "CovidWUFerritinOption", 
    var optionNameList = [ "CovidCRPDailyOption", "CovidCBCDiffPDailyOption", "CovidVBGDailyOption",
                           "CovidVBGDailyOption", "CovidDDimerDailyOption"];
    WriteListOfSelectedActions(activeControlPanel, "Check daily labs: ", false, "", optionNameList, "")

    // Treat
    WriteActionIfSelected(activeControlPanel, "CovidDexamethasoneOption");
    WriteActionIfSelected(activeControlPanel, "CovidMethylpredOption");
    WriteActionIfSelected(activeControlPanel, "CovidRemdesivirOption");
    WriteActionIfSelected(activeControlPanel, "CovidDiureticsOption");
    WriteActionIfSelected(activeControlPanel, "CovidAntibioticsOption");

    // Other treat
    WriteActionIfSelected(activeControlPanel, "CovidO2Option");
    WriteActionIfSelected(activeControlPanel, "CovidPrecautionsOption");
    WriteActionIfSelected(activeControlPanel, "CovidProneOption");

    WriteActionIfSelected(activeControlPanel, "CovidAlbuterolOption");
    WriteActionIfSelected(activeControlPanel, "CovidApapOption");
    WriteActionIfSelected(activeControlPanel, "CovidGuaifenesinOption");
    WriteActionIfSelected(activeControlPanel, "CovidPPIOption");
    WriteActionIfSelected(activeControlPanel, "CovidNoNebsOption");
} // WriteCovidPlan





////////////////////////////////////////////////////////////////////////////////
//
// [WriteAnemiaPlan]
//
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

    //Workup
    ///////////////////////////
    var optionNameList = [ "AnemiaCheckPeripheralSmearOption", "AnemiaCheckLDHOption", "AnemiaCheckHaptoglobinOption", 
                            "AnemiaCheckReticulocyteCountOption" ];
    WriteListOfSelectedActions(activeControlPanel, "Check for hemolysis: ", false, "", optionNameList, "")

    ///////////////////////////
    var optionNameList = [ "AnemiaCheckTIBCOption", "AnemiaCheckIronBindingSaturationOption", "AnemiaCheckFerritinOption"];
    WriteListOfSelectedActions(activeControlPanel, "Check iron levels: ", false, "", optionNameList, "")

    ///////////////////////////
    var optionNameList = [ "AnemiaCheckHemoccultOption", "AnemiaCheckHPyloriOption", "AnemiaCheckCeliacOption", 
                            "AnemiaCheckINROption"];
    WriteListOfSelectedActions(activeControlPanel, "Check GI loss: ", false, "", optionNameList, "")

    ///////////////////////////
    var optionNameList = [ "AnemiaCheckB12Option", "AnemiaCheckFolateOption", "AnemiaCheckZincOption", 
                            "AnemiaCheckCopperOption", "AnemiaCheckVitKOption"];
    WriteListOfSelectedActions(activeControlPanel, "Check nutrients: ", false, "", optionNameList, "")

    ///////////////////////////
    var optionNameList = [ "AnemiaCheckHIVOption", "AnemiaCheckEBVOption", "AnemiaCheckHBVOption", 
                            "AnemiaCheckParvoOption"];
    WriteListOfSelectedActions(activeControlPanel, "Check infectious causes: ", false, "", optionNameList, "")

    ///////////////////////////
    var optionNameList = [ "AnemiaCheckDirectCoombsOption", "AnemiaCheckWarmAgglutininsOption", 
                            "AnemiaCheckColdAgglutininsOption", "AnemiaCheckANAOption"];
    WriteListOfSelectedActions(activeControlPanel, "Check autoimmune causes: ", false, "", optionNameList, "")


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
                            "PEDVTRisksCADOption", "PEDVTHasBLEDStrokeOption", 
                            "PEDVTRisksOCPOption",
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
////////////////////////////////////////////////////////////////////////////////
function 
WriteTobaccoPlan() {
    var pStr;    
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Tobacco Dependance";
    if (PrintSingleLinePlanAtEnd('TobaccoPlan', planStr, "Nicotine replacement (gum, patch)")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "TobaccoPlan");
    if (!activeControlPanel) {
        LogEvent("xxxxx. activeControlPanel is null");
        return;
    }

    WriteCommentIfSelected(activeControlPanel, 'TobaccoPacksPerDayOption');
    WriteCommentIfSelected(activeControlPanel, 'TobaccoStartedSmokingOption');
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
// [WriteWeaknessPlan]
//
// Updated: 2020-5-1
// Updated: 2020-5-30
////////////////////////////////////////////////////////////////////////////////
function 
WriteWeaknessPlan() { 
    var activeControlPanel = null;
    var planStr = "";

    planStr = "Weakness";
    if (PrintSingleLinePlanAtEnd('WeaknessPlan', planStr, "Physical and Occupational therapy")) {
        return
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "WeaknessPlan");
    if (!activeControlPanel) {
        LogEvent("xxxxx. activeControlPanel is null");
        return;
    }
    planStr = MedNote_GetCPOptionValue("WeaknessFallsOption");
    if ((planStr != null) && (planStr != "")) {
        MedNote_AddRelatedProblem(planStr);
    }
    planStr = MedNote_GetCPOptionValue("WeaknessReducedMobilityOption");
    if ((planStr != null) && (planStr != "")) {
        MedNote_AddRelatedProblem(planStr);
    }
    planStr = MedNote_GetCPOptionValue("WeaknessDebilityOption");
    if ((planStr != null) && (planStr != "")) {
        MedNote_AddRelatedProblem(planStr);
    }

    WriteActionIfSelected(activeControlPanel, "WeaknessPTOption");
    WriteActionIfSelected(activeControlPanel, "WeaknessPrecautionsOption");
} // WriteWeaknessPlan




////////////////////////////////////////////////////////////////////////////////
//
// [WriteObesityPlan]
//
// Updated 2020-5-30
////////////////////////////////////////////////////////////////////////////////
function 
WriteObesityPlan() {
    var pStr;    
    var activeControlPanel = null;
    var planStr = "";
    var modifierStr = "";

    planStr = "Obesity";
    modifierStr = MedNote_GetCPOptionValue("ObesityMorbidOption");
    if ((modifierStr != null) && (modifierStr != "")) {
        planStr = modifierStr + " " + planStr;
    }
    if (PrintSingleLinePlanAtEnd('ObesityPlan', planStr, "Counsel weight loss")) {
        return
    }

    activeControlPanel = MedNote_StartNewPlanSection(planStr, "ObesityPlan");
    if (!activeControlPanel) {
        LogEvent("WriteObesityPlan. activeControlPanel is null");
        return;
    }

    WriteCommentIfSelected(activeControlPanel, 'ObesityShowBMIOption');
    WriteCommentIfSelected(activeControlPanel, 'ObesityComplicatesOption');

    WriteActionIfSelected(activeControlPanel, "ObesityConsultNutritionOption");
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
    var pStr;    
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


    WriteCommentIfSelected(activeControlPanel, 'MalnutritionShowBMIOption');
    WriteCommentIfSelected(activeControlPanel, 'MalnutritionShowPrealbuminOption');
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
// Last Updated 7/22-25/2020
////////////////////////////////////////////////////////////////////////////////
function 
PrintAKIPlan() {
    //LogEvent("PrintAKIPlan");
    var activeControlPanel = null;
    var planStr;
    var modifierStr;
    var currentCr = -1;
    var baselineCr = -1;
    var currentNa = -1;
    var currentBUN = -1;
    var currentUCr = -1;
    var currentUNa = -1;
    var currentUUN = -1;
    var currentUProt = -1;
    var baselineGFR = -1;
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
        planStr = planStr + modifierStr;
    }
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "AKIPlan");
    if (!activeControlPanel) {
        return;
    }
    planStr = MedNote_GetCPOptionValue("AKIATNOption");
    if ((planStr != null) && (planStr != "")) {
        MedNote_AddRelatedProblem(planStr);
    }

                    
    ////////////////////////////////////////////////////////////
    // Load the integer values
    currentCr = GetFloatInputForControlPanel(activeControlPanel, 'Creatinine_CP', null);
    currentNa = GetIntInputForControlPanel(activeControlPanel, 'InputNa_CP', null);
    currentUCr = GetIntInputForControlPanel(activeControlPanel, 'InputUrineCr_CP', null);
    currentUNa = GetIntInputForControlPanel(activeControlPanel, 'InputUNa_CP', null);
    currentBUN = GetIntInputForControlPanel(activeControlPanel, 'InputBUN_CP', null);
    currentUUN = GetIntInputForControlPanel(activeControlPanel, 'InputUUN_CP', null);
    currentUProt = GetIntInputForControlPanel(activeControlPanel, 'InputUProt_CP', null);
    recentCrStr = GetStrInputForControlPanel(activeControlPanel, 'Creatinine_CP');
    baselineCrStr = GetStrInputForControlPanel(activeControlPanel, 'InputBaselineCreatinine_CP');
    if (baselineCrStr) {
        baselineCr = parseInt(baselineCrStr);
        if (isNaN(baselineCr)) {
            baselineCr = -1;
        }
    }
    baselineGFRStr = GetStrInputForControlPanel(activeControlPanel, 'InputBaselineGFR_CP');
    if (baselineGFRStr) {
        baselineGFR = parseInt(baselineGFRStr);
        if (isNaN(baselineGFR)) {
            baselineGFR = -1;
        }
    }

    ////////////////////////////////////////////////////////////
    // Calculate values
    //
    //LogEvent("currentCr = " + currentCr)
    //LogEvent("currentNa = " + currentNa)
    //LogEvent("currentUCr = " + currentUCr)
    //LogEvent("currentUNa = " + currentUNa)
    //LogEvent("currentUUN = " + currentUUN)
    //LogEvent("currentBUN = " + currentBUN)
    // FENa - Fractional Excretion Sodium
    if ((currentUNa > 0) && (currentNa > 0) && (currentUCr > 0) && (currentCr > 0)) {
        FENa = ((currentUNa / currentNa) / (currentUCr / currentCr));
        //LogEvent("PrintAKIPlan. raw FENa=" + FENa);
        // Convert to a percentage
        FENa = FENa * 100;
        //LogEvent("PrintAKIPlan. Percent FENa=" + FENa);
        // Round it to 2 decomal places. We add 0.00001 to work around a Javascript bug.
        FENa = Math.round((FENa + 0.00001) * 100) / 100;
        //LogEvent("PrintAKIPlan. FENa=" + FENa);
        SetStrOutputForControlPanel(activeControlPanel, 'ResultFENa_CP', null, "FENa = " + FENa + "%");
    }
    // FEUrea - Fractional Excretion Urea
    if ((currentUUN  > 0) && (currentBUN > 0) && (currentUCr > 0) && (currentCr > 0)) {
        FEUrea = ((currentUUN / currentBUN) / (currentUCr / currentCr));
        // Convert to a percentage
        FEUrea = FEUrea * 100;
        // Round it to 2 decomal places. We add 0.00001 to work around a Javascript bug.
        FEUrea = Math.round((FEUrea + 0.00001) * 100) / 100;
        SetStrOutputForControlPanel(activeControlPanel, 'ResultFEUrea_CP', null, "FEUrea = " + FEUrea + "%");
    }
    // UPCR - Urine Prot/Cr ratio
    if ((currentUProt  > 0) && (currentUCr > 0)) {
        UPCR = (currentUProt / currentUCr);
        // Round it to 2 decomal places. We add 0.00001 to work around a Javascript bug.
        UPCR = Math.round((UPCR + 0.00001) * 100) / 100;
        SetStrOutputForControlPanel(activeControlPanel, 'ResultUPCr_CP', null, "UPCR = " + UPCR);
    }


    ////////////////////////////////////////////////////////////
    planStr = "";
    if (MedNote_GetCPOptionBool("AKITrendCrOption")) {
        planStr = "Recent Creatinine trend: ";
        if (currentCr > 0) {
            planStr = planStr + currentCr;
        } else {
            planStr = planStr + recentCrStr;            
        }
        planStr = planStr + "        ";
    }
    if (MedNote_GetCPOptionBool("AKIBaselineCrOption")) {
        planStr = planStr + "Baseline Creatinine is ";
        if (baselineCrStr) {
            planStr = planStr + baselineCrStr;
        }
        if (baselineGFRStr) {
            planStr = planStr + ", Baseline GFR=" + baselineGFRStr;
        }
    }
    if (planStr != "") {
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
            if (FENa >= 0) {
                if (FENa <= 35.0) {
                    planStr = MedNote_GetCPOptionValueForIndex('AKIFEUreaOption', 0);
                } else {
                    planStr = MedNote_GetCPOptionValueForIndex('AKIFEUreaOption', 1);
                }
            } else {
                planStr = "FEUrea is xxxx";
            }
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
    WriteActionIfSelected(activeControlPanel, 'AKIUrinalysisOption');
    WriteActionIfSelected(activeControlPanel, 'AKILytesOption');
    WriteActionIfSelected(activeControlPanel, 'AKICPKOption');
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
    var actionNameList = [ "AKITitratePipTazoOption", "AKIConvertOpioidsOption", 
                            "AKITitrateGabapentinOption", "AKITitrateColchicineOption"];
    WriteListOfSubActions(activeControlPanel, "Titrate Medications for current estimated eGFR", actionNameList);

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
    WriteActionIfSelected(activeControlPanel, "NSTEMICheckEKGOption");
    WriteActionIfSelected(activeControlPanel, "NSTEMICheckTroponinsOption");
    WriteActionIfSelected(activeControlPanel, "NSTEMIAMEKGOption");
    WriteActionIfSelected(activeControlPanel, "NSTEMIUDSOption");

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
    WriteActionIfSelected(activeControlPanel, "NSTEMIGetLipidOption");
    WriteActionIfSelected(activeControlPanel, "NSTEMIGetA1cOption");

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
// Last Updated 7/30/2020
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
    var currentNa = GetIntInputForControlPanel(activeControlPanel, 'InputNa_CP', null);
    var currentGlc = GetIntInputForControlPanel(activeControlPanel, 'InputGlucose_CP', null);
    var currentBicarb = GetIntInputForControlPanel(activeControlPanel, 'InputBicarb_CP', null);
    var currentUOsm = GetIntInputForControlPanel(activeControlPanel, 'InputUrineOsm_CP', null);
    var currentUrineNa = GetIntInputForControlPanel(activeControlPanel, 'InputUrineNa_CP', null);
    var currentUrineK = GetIntInputForControlPanel(activeControlPanel, 'InputUrineK_CP', null);
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
    }
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
        //var volumeOfUrineThatIsIsPureWater = fractionOfUrineThatIsIsPureWater * GetLabValue("UrineVolume");
        //volumeOfUrineThatIsIsPureWater = Math.round((volumeOfUrineThatIsIsPureWater + 0.00001) * 10) / 10;
        SetStrOutputForControlPanel(activeControlPanel, 'ResultFreeWaterClearance_CP', null, 'Urine is ' + estimatedFreeWaterClearancePercent + '% free water');
    }



    ///////////////////
    // Labs and Current Status
    planStr = MedNote_GetCPOptionValue("HypONaShowCurrentNaOption");
    if ((planStr != null) && (planStr != "")) {
        if (currentNa > 0) {
            planStr = planStr + currentNa
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
            planStr = planStr + currentSOsmStr
        }
        WriteComment(planStr);
    }


    ///////////////////
    // ADH Status
    WriteCommentIfSelected(activeControlPanel, 'HypONaHighADHOption');
    planStr = MedNote_GetCPOptionValue("HypONaShowUOsmOption");
    if ((planStr != null) && (planStr != "")) {
        if (currentUOsm > 0) {
            planStr = planStr + currentUOsm
        }
        WriteComment(planStr);
    }
    WriteCommentIfSelected(activeControlPanel, 'HypONaExplainHighUOsmOption');
    planStr = MedNote_GetCPOptionValue("HypONaShowFreeWaterClearanceOption");
    if ((planStr != null) && (planStr != "")) {
        if (estimatedFreeWaterClearancePercent > 0) {
            planStr = planStr + estimatedFreeWaterClearancePercent + "% free water"
        } else {
            planStr = planStr + "xxxx % free water";
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
    WriteActionIfSelected(activeControlPanel, 'HypONaCheckUOsmOption');
    WriteActionIfSelected(activeControlPanel, 'HypONaCheckULytesOption');

    WriteActionIfSelected(activeControlPanel, 'HypONaCheckTSHOption');
    WriteActionIfSelected(activeControlPanel, "HypONaCheckSOsmOption");
    WriteActionIfSelected(activeControlPanel, 'HypONaCheckUrateOption');
    WriteActionIfSelected(activeControlPanel, 'HypONaCheckLipidsOption');
    WriteActionIfSelected(activeControlPanel, 'HypONaAMcortisolOption');

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
OLD_WritePreventionPlan() {    
    var patientAge = GetLabValue("Age");
    var isMale = GetLabValue("IsMale");

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
    if (!isMale) {
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
    if ((isMale) && (patientAge > 0) && (patientAge >= 50) && (patientAge <= 75)) {
        WriteAction("Prostate cancer Screening PSA Q1yr: Patient declines annual PSA");
    }

    /////////////////////////////
    // Lung Cancer
    if ((patientAge > 0) && (patientAge >= 50) && (patientAge <= 75)) {
        WriteAction("Lung Cancer Screening with low power CT Q1yr if over 30 pack years");
    }

    /////////////////////////////
    // Cervical Cancer
    if (!isMale) {
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
    if ((isMale) && (patientAge > 0) && (patientAge >= 65) && (patientAge <= 75)) {
        WriteAction("AAA Screening");
    }

    /////////////////////////////
    // Bone Density
    if ((!isMale) && (patientAge >= 65) && (patientAge <= 75)) {
        WriteAction("Bone density screening (DEXA Q2yr): Last DEXA ");
    } // Female

    /////////////////////////////
    // Lipids
    if (((isMale) && (patientAge >= 35))   ||    ((!isMale) && (patientAge >= 55))) {
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
// Updated: 2020-5-1
////////////////////////////////////////////////////////////////////////////////
function 
WriteWeaknessPlan() { 
    var activeControlPanel = null;
    var planStr = "";
    var fWrotePlan = false;
    
    // Find all of the possible plans.
    var fallsPlanStr = MedNote_GetCPOptionValue("WeaknessFallsOption");
    var mobilityPlanStr = MedNote_GetCPOptionValue("WeaknessReducedMobilityOption");
    var debilityPlanStr = MedNote_GetCPOptionValue("WeaknessDebilityOption");

    // Pick a primary plan.
    planStr = "";
    if ((planStr == "") && (fallsPlanStr != null) && (fallsPlanStr != "")) {
        planStr = fallsPlanStr;
    }
    if ((planStr == "") && (debilityPlanStr != null) && (debilityPlanStr != "")) {
        planStr = debilityPlanStr;
    }
    if ((planStr == "") && (mobilityPlanStr != null) && (mobilityPlanStr != "")) {
        planStr = mobilityPlanStr;
    }
    if (planStr == "") {
       planStr = "Weakness";
    }

    // Start the problem.
    activeControlPanel = MedNote_StartNewPlanSection(planStr, "WeaknessPlan");
    if (!activeControlPanel) {
        LogEvent("WriteWeaknessPlan. activeControlPanel is null");
        return;
    }

    // Write secondary plans    
    if ((planStr != fallsPlanStr) && (fallsPlanStr != null) && (fallsPlanStr != "")) {
        MedNote_AddRelatedProblem(fallsPlanStr);
    }
    if ((planStr != debilityPlanStr) && (debilityPlanStr != null) && (debilityPlanStr != "")) {
        MedNote_AddRelatedProblem(debilityPlanStr);
    }
    if ((planStr != mobilityPlanStr) && (mobilityPlanStr != null) && (mobilityPlanStr != "")) {
        MedNote_AddRelatedProblem(mobilityPlanStr);
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

    WriteActionIfSelected(activeControlPanel, "WeaknessPTOption");
    WriteActionIfSelected(activeControlPanel, "WeaknessPrecautionsOption");
    WriteActionIfSelected(activeControlPanel, "WeaknessUpInChairOption");
} // WriteWeaknessPlan

