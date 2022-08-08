#include "RiceStyle.h"
using namespace std;
double sigma_sartre_elect[]={2.62E+4,3.56E+3,128.};
void plotPhi(){

	TFile* file[2];
	file[0] = new TFile("../rootfiles/sartre_phi_bnonsat_PID_0_minPt_0.15_smear_0.root");
	file[1] = new TFile("../rootfiles/sartre_rho_bnonsat_PID_0_minPt_0.15_smear_0.root");
	
	/*
	Getting the number of events automatically
	*/
	TH1D* h_count_sig=(TH1D*) file[0]->Get("h_xbj_truth");
	TH1D* h_count_bkg=(TH1D*) file[1]->Get("h_xbj_truth");

	int numberOfSignalEvents=h_count_sig->GetEntries();
	int numberOfBackgroundEvents=h_count_bkg->GetEntries();

	double lumi_to_apply_signal = numberOfSignalEvents / sigma_sartre_elect[1];
	double lumi_to_apply_background = numberOfBackgroundEvents / sigma_sartre_elect[0];
	//end constant

	TH2D*h_phi_sig = (TH2D*) file[0]->Get("h_VM_t_mass_0_2_1");//coherent,Method-L,assume phi->KK mass
	TH2D*h_phi_bkg = (TH2D*) file[1]->Get("h_VM_t_mass_0_2_1");//coherent,Method-L,assume phi->K mass

	TH1D* h_mass_sig = (TH1D*) h_phi_sig->ProjectionX("h_phi_sig_mass",1,100);
	TH1D* h_mass_bkg = (TH1D*) h_phi_bkg->ProjectionX("h_phi_bkg_mass",1,100);

	// h_mass_sig->Draw("");
	// h_mass_bkg->SetLineColor(kRed);
	// h_mass_bkg->Draw("same");

	double masslow=1.019-0.02;
	double masshigh=1.019+0.02;
	int masslowbin=h_mass_sig->FindBin(masslow);
	int masshighbin=h_mass_sig->FindBin(masshigh);
	TH1D* h_t_sig = (TH1D*) h_phi_sig->ProjectionY("h_phi_sig_t",masslowbin,masshighbin);
	TH1D* h_t_bkg = (TH1D*) h_phi_bkg->ProjectionY("h_phi_bkg_t",masslowbin,masshighbin);

	double binwidth = h_t_sig->GetBinWidth(1);
	h_t_sig->Scale(1./(lumi_to_apply_signal * binwidth));
	h_t_bkg->Scale(1./(lumi_to_apply_background * binwidth));
	h_t_bkg->SetLineColor(kRed);

	h_t_sig->Draw("hist");
	h_t_bkg->Draw("hist same");







}

