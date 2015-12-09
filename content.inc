% ---------------------------------------------------------------------
% EG author guidelines plus sample file for EG publication using LaTeX2e input
% D.Fellner, v1.17, Sep 23, 2010


\title[Interactive Exploration of Ligand Movements through Multiscale Temporal Tunnels]%
      {Interactive Exploration of Ligand Movements through Multiscale Temporal Tunnels}

% for anonymous conference submission please enter your SUBMISSION ID
% instead of the author's name (and leave the affiliation blank) !!
\author[K. Furmanov\'{a} et al.]
       {K. Furmanov\'{a}$^{1}$, M. Jare\v{s}ov\'{a}$^{1}$, J. By\v{s}ka$^{1,2}$, A. Jur\v{c}\'{i}k$^{1}$, J. Parulek$^{2}$, H. Hauser$^{2}$, and B. Kozl\'{i}kov\'{a}$^{1}$
%        S. Spencer$^2$\thanks{Chairman Siggraph Publications Board}
        				\\
% For Computer Graphics Forum: Please use the abbreviation of your first name.
         $^1$Faculty of Informatics, Masaryk University, Czech Republic\\
         $^2$Department of Informatics, University of Bergen, Norway
%        $^2$ Another Department to illustrate the use in papers from authors
%             with different affiliations
       }

% ------------------------------------------------------------------------

% if the Editors-in-Chief have given you the data, you may uncomment
% the following five lines and insert it here
%
% \volume{27}   % the volume in which the issue will be published;
% \issue{1}     % the issue number of the publication
% \pStartPage{1}      % set starting page


%-------------------------------------------------------------------------
\begin{document}

% \teaser{
%  \includegraphics[width=\linewidth]{eg_new}
%  \centering
%   \caption{New EG Logo}
% \label{fig:teaser}
% }

\maketitle

\begin{abstract}
Protein structures and their interaction with ligands have been in the focus of biochemistry and structural biology research for decades.
%Traditionally the interaction is represented by a ligand that follows a path (tunnel) from the outer solvent to the active site where it can react.
%The transportation of ligand into the protein active site where it can react can be very lengthy and complex process that is influenced and driven by both geometric and physico-chemical properties of the ligand and the amino acids surrounding its path.
The transportation of ligand into the protein active site is often complex process, driven by geometric and physico-chemical properties, which renders the ligand path full of jitter and impasses. Therefore, answering also the domain expert needs, we design an explorative visualization solution based on a multi-scale simplification model. This allows to emphasize the main direction of the ligand motion while providing geometric and physico-chemical descriptors available at each hierarchical level by user interaction.  
%These interesting time sequences are revealed by interacting with our representation.
This approach could easily guide users to choose simulation frames containing important ligand movements that drive the ligand to the active site. 
Additionally, our simplified representation decreases the length of molecular dynamics simulation, which significantly reduces the time spent on this analysis.
The proposed method was applied on simulations captured by the biochemists who also evaluated the method.

\begin{classification} % according to http://www.acm.org/class/1998/
\CCScat{Computer Graphics}{I.3.3}{Picture/Image Generation}{Line and curve generation}
\end{classification}

\end{abstract}



%-------------------------------------------------------------------------
\section{Introduction}
The study of reaction processes between different types of molecules has been an important research problem already for decades.
A proper understanding of the processes occurring when two or more molecules react helps in the design of new chemical matters, e.g., in drug design or protein engineering.
Here, the researchers aim to combine a protein with a given ligand in order to design a new drug or to change protein properties and their function.
In these particular cases the ligand has to be transported from the outer solvent to the protein active site where the chemical reaction between the ligand and the amino acids surrounding the active site takes place.
The consecutive reaction then changes the composition and properties of both molecules. 
In protein engineering, for example, the goal is to alter the protein properties so that the new protein is, e.g., more stable and resistant to organic cosolvents~\cite{Koudelakova2013}.

The design complexity of such reactions lies namely in the transportation of the ligand to the protein active site.
As the active site is usually buried deeply in the protein structure and thus inaccessible directly from its surface, the ligand has to find a suitable transportation path through the protein structure.
This process, called molecular docking, is very complex, lengthy, and heavy on computational resources. 
Therefore, researchers aim at solutions that simplify and ease the analysis for proper ligand binding.
Currently available solutions often focus on detection of possible ligand transportation paths through the protein, called tunnels.
These solutions are mostly based on the geometric analysis, which lead to the tunnel detection in the end; e.g., CAVER~\cite{Chovancova2012}, MOLE~\cite{Sehnal2013}, or MolAxis~\cite{Yaffe2008}.
Other approaches, such as MoMA-LigPath~\cite{Devaurs}, aim at simulating the ligand transportation itself.
Nevertheless, simulating the ligand docking using current computational approaches is still a challenging problem.
There are several available variants of molecular simulation methods devised specifically to this problem. 
Among these Steered Molecular Dynamics~\cite{Isralewitz} and Random Acceleration Molecular Dynamics~\cite{Ludemann} are able to simulate the ligand binding. 
Such simulations produce a large amount of data containing the ligand movements that are to be explored by the domain expert.
As the length of these simulations reaches often hundreds of thousands of time steps, it becomes impossible for the domain experts to visualize and observe the ligand movement in a frame-by-frame manner.
Moreover, the simulation often contains movements that are irrelevant to the ligand binding.
For example, a significant portion of the simulation the ligand usually spends outside the protein searching for a proper tunnel gorge to enter the molecule. 
It also often happens that the ligand enters the molecule via a wrong tunnel and is then evicted from the molecule and searches for the entrance repeatedly.
Therefore, the "true" active site entering can be in fact captured in a smaller subset of the original sequence.

In this paper, we propose a new visual analysis system that addresses the aforementioned challenges; i.e.,  the transportation of a ligand to the active site. 
We aim to provide the domain experts with a tool for intuitive and interactive exploration of already captured molecular dynamics simulation containing the process of ligand binding. 
Using our proposed solution the users are able to distinguish between the parts of the simulation where the ligand searches for the proper path to the active site (searches the tunnel gorge or enters the wrong tunnel) and the part where the ligand finally leads to and reaches the active site.
%In the part of such annotated data when the ligand travels to the active site we provide the users with our newly introduced concept of so called temporal tunnel.
%The centerline of this tunnel is represented by the ligand trajectory and in the original data is very jittered.
%Thus it is hard to follow determine the time steps when the ligand made a significant shift towards the active site.

Here, we introduce two dedicated methods for simplification of the original trajectory.
These methods can simplify the ligand path hierarchically, thus providing several levels of detail (LOD), which can be interactively browsed through.
In the most abstracted view, represented as the top-most LOD, the temporal tunnel shows only the significant shifts of the ligand towards the active site. 
Here, the user can interactively brush time intervals, which automatically reveals and adopts the temporal tunnel to the selected interval.
This abstracted representation, providing the brushing capabilities, is interactively linked with the 3D visualization where the 3D shape of the temporal tunnel for the given temporal window is displayed.
Further, our tool enables to explore the amino acids surrounding the ligand along its path to the active site as well.

Our proposed solution was thoroughly tested and evaluated by the domain experts from protein engineering.
They performed the evaluation on their own simulations and their feedback is described in Section~\ref{discussion}.

%-------------------------------------------------------------------------

\section{Related Work}
Interactive exploration of ligand paths through protein structures is a complex problem that requires elaborate analysis of existing and suitable approaches to its subtasks.
%In this section we present the results we consider to be relevant to our proposed solution. 
As our system addresses several areas, this section will be divided with respect to these areas as well. 
Studying the ligand transport path is tightly related to the analysis of its trajectory.
Thus, the first part will cover the topic related to the trajectory analysis, simplification, and visualization.
Then the existing representations of tunnels and their surrounding amino acids will be mentioned.

\subsection{Trajectory Analysis, Simplification, and Visualization}
When searching for an inspiration in this field, one of the best starting points is the book by Andrienko et al. \cite{andrienko2013}.
Concerning the trajectory simplification, they proposed two different approaches to the data abstraction, which is a necessary step to achieve the reduction of the data and clarity of visualizations.
First approach is characterized by omitting unnecessary positions and segments.
The other is based on sampling the data.
Andrienko et al. also claim that there are no general methods for sampling trajectories.
Thus the suitability of particular sampling method is deduced from what information is considered important.
A recent work of Vrotsou et. al. \cite{Vrotsou2015} introduced a systematic stepwise methodology for trajectory simplification with emphasis on visual analysis.
Even though they primarily developed the tool to analyze three dimensional trajectories (aircraft flights), it is not limited to them.

In the field of molecular biology as well as systems biology, there are several examples of methods focusing on the trajectory analysis.
Bidmon et al.~\cite{bidmon2008} presented an abstract way of identification and visualization of solvent molecules' pathways within a molecular dynamics. 
In comparison to previous solutions, their approach preserves valuable information on the directions and velocities of water molecules routing along these paths. 
Another approach to the guidance through a complex simulation trajectories in systems biology was presented by Luboschik et al.~\cite{Luboschik2012}. 
Their method was proposed for biochemical reaction networks and aims to provide the users with a tool for investigating the overall behavior of a modeled system and subtle, detail behavior at the same time.

\subsection{Visualization of Tunnels}
Our notion about the temporal tunnel in the protein resembles the approach of Lindow et al. \cite{Lindow2013}.
In this work they focus on the interactive exploration of the dynamics of protein cavities which can form the transportation path for a ligand. 
They are able to calculate and visualize the cavity volume and to analyze the time-dependent changes of the cavity structure.
The cavity dynamics is captured by rendering the cavities in a single image. 
The resulting image is visualized using molecular surface representation colored according to time. 

TODO!!!!!!

%\cite{bidmon2008}, \cite{lampe2011}, \cite{turkay2011}, and this is new 

%-------------------------------------------------------------------------
\section{Problem Description and Input Data}
\textcolor[rgb]{1,0,0}{Each section should have at least two subsections or none, some info repeats itself, questions is whether to put it here from intro or reduce this part and move it to intro. let's discuss it on skype.}
When studying long molecular dynamics simulations, the researchers have to face namely the following high-level tasks:
\begin{itemize}
\item Detect the part of the simulation where the ligand enters the protein and finally reaches the active site.
\item Explore this route in detail and detect its bottlenecks.
\end{itemize}
In consequence, these steps are performed in order to reveal the parts of the trajectory where the ligand gets stuck.
It means that in such parts there are some obstacles made by the surrounding amino acids.
These obstacles can be geometric (the empty space between these amino acids is too narrow) or physico-chemical (the properties of the amino acids are incompatible with the ligand properties), or their combination.
The geometric obstacles can be detected by using an algorithm for tunnel computation in molecular dynamics (e.g., CAVER~\cite{Chovancova2012} or MOLE~\cite{Sehnal2013}).
These tools are able to produce the information about time evolution of individual tunnels and for each tunnel detect its bottleneck -- the narrowest part limiting the size of the ligand aiming to pass through this tunnel.
Figure~\ref{fig:tunnel} shows an example of small ligand passing through a tunnel computed by CAVER algorithm and visualized using CAVER Analyst~\cite{Kozlikova2014}. 
The tunnel is colored with respect to the hydrophobicity of the surrounding amino acids and the geometric bottleneck of the tunnel is clearly visible.

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/tunnel.png}
  \caption{\label{fig:tunnel} Small ligand (green) passing through a tunnel represented by the transparent surface. The surface encloses the available empty space along the tunnel centerline and is colored with respect to the hydrophobicity of the surrounding amino acids (hydrophobic -- red, hydrophylic -- blue, neutral -- violet). The active site is located in the left ending of the tunnel.}
\end{figure}

However, this bottleneck can be to some extent influenced by the passing ligand and this influence is also determined by the physico-chemical properties of the ligand and the bottleneck-lining amino acids (e.g., hydrophobicity or partial charges of individual atoms).
To reveal such dependencies, it requires the involvement and experience of the domain expert who has to study the ligand trajectory captured in the molecular dynamics simulation.
And for such task a proper visual representation and guidance through such large data is substantial.

In protein engineering, all these effort can finally lead to the detection of amino acids along the ligand trajectory which caused problems, i.e., were the key players in situations when the ligand got stuck.
Such amino acids are then the best candidates for subsequent mutation of the protein chain when these amino acids are replaced by more suitable ones wrt. their size and properties.
On the other hand, in drug design the aim is to propose modifications of the ligand to increase its binding and so design a better drug produced from this ligand.

\subsection{Input Data}
As already mentioned, the input data are formed by the simulations of molecular dynamics which contains the movements of the protein and one or more ligands.
Ligands can follow two main routes -- they can be transported from the outside environment to the protein active site or vice versa (after the desired reaction the product leaves the protein).
Our proposed tool is suitable for both cases.

The length of the simulations may vary from few hundreds to hundreds of thousands of time steps.  
This depends namely on the ligand speed and its ability to find the proper path to the active site.
Figure \ref{fig:lig_movement} shows an example of a ligand trajectory consisting of 10.000 time steps. 

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/lig_movement.png}
  \caption{\label{fig:lig_movement} Ligand trajectory for a simulation containing 10.000 time steps. TODO change image, add molecule}
\end{figure}

Long simulations can often contain many time steps when the ligand followed an impasse -- it tried to find the proper entrance point to the protein (tunnel gorge) or entered a wrong tunnel and had to return.
Such parts of the simulation could be of less interest so the user should be provided with a possibility to filter them out and focus only on the interesting parts.

%-------------------------------------------------------------------------
%\section{Design and Implementation}
\section{Visualization Design}
In this section we describe the design rationale of our proposed approach to interactive exploration of ligand trajectory coming from the above described simulations of molecular dynamics.
The design is tightly related to the problems posed by the biochemists, namely:
\begin{itemize}
\item The length of the simulations and impossibility to distinguish between different parts based on the type of ligand movement (outside protein, inside a wrong or correct tunnel).
\item The scattered nature of the original movement making it impossible to easily follow the overall direction of the ligand movement.
\end{itemize}

To tackle the aforementioned challenges, we propose a visualization system illustrated in Figure~\ref{fig:overview}.
The first problem is addressed by the simple visualization on the top of the window.
Its goal is to provide the users with the general overview of the whole simulation and highlight individual parts of the ligand movement.
We classify ligand motion into three basic categories, which are represented in the following way.
In each time step we check the position of the ligand with respect to the protein solvent excluded surface~\cite{Richards}. 
Whenever the ligand passes through the surface, we store the corresponding time step and ligand position.
If the ligand is outside the protein surface, it means that it still tries to find the entrance point to enter the protein through a tunnel gorge on the surface. 
When the ligand enters the protein inner space, we can distinguish between two cases.
In the first case the ligand enters a tunnel but there is an obstacle preventing it to get to the active site and the ligand is expelled from the inner space back to the outer environment.
The second case enables the ligand to reach the active site. 
Very similar solution can be adopted for the opposite direction when the ligand aims to leave the active site and reach the outer solvent.

As a result, we obtain three different types of movements which are highlighted in the overview representation (Fig. \ref{fig:overview} a)).
Yellow parts represent the ligand movements outside the molecule, red parts show the parts where the ligand entered a wrong tunnel and had to return, and green parts depict the situation where the ligand finally took the correct tunnel and reached the active site.
The user can interactively select an arbitrary part and the remaining parts of our proposed solution (Fig.~\ref{fig:overview} b)) are interactively updated in order to present only the information for a selected part.
So the biochemists are easily navigated to a selected time span they want to explore in more detail.

\begin{figure*}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/overview.png}
  \caption{\label{fig:overview} Illustration of our proposed technique. Section a) gives an overview of the individual parts of the simulation (yellow = ligand is outside the protein, red = ligand entered a wrong tunnel, green = ligand entered a correct tunnel and reached the active site). Section b) shows the detailed information about a selected part. TODO}
0\end{figure*}

Even though the detected parts are usually much shorter in comparison with the length of the original simulation, it is still nearly impossible to comprehend the ligand movement. 
This is caused by ligand jittering which makes the perception of the significant ligand movements very hard to follow.
This is clearly visible in Figure~\ref{fig:temporal} a)) which shows the whole ligand trajectory in case when the ligand entered the solvent excluded surface and entered the active site.
The same holds true for cases when the user is watching the animated motion of the ligand. 
Hence we suggest the solution based on a multi-scale simplification model which introduces the concept of so called \textit{temporal tunnel}.  

\subsection{Temporal Tunnel}
The bottom part of our visualization consists of three tightly related sections (detailed description in Section~\ref{visualization}) showing the properties of so called temporal tunnel. 
We define the temporal tunnel as a set of spheres positioned onto the centerline representing the trajectory of ligand. 
The centers of these spheres correspond to the center of mass of the ligand in each of its positions and the diameter of the spheres is computed as the maximal empty space around the ligand in a given time step. 
The main contribution of the temporal tunnel is to give the user the information about the geometric bottlenecks (narrowest parts) along the ligand trajectory.
Note that applying the temporal tunnel to the original data provides us only with an approximation of the exact trajectory (Fig. \ref{fig:temporal}).
Still when the ligand trajectory is simplified using one of the methods described below, it gives the user an important overview of the bottlenecks that can be subsequently explored in more detail.

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/temporal.png}
  \caption{\label{fig:temporal} Left: selected part of the whole trajectory when the ligand enters the active site. Right: visualization of the corresponding temporal tunnel. TODO change images!}
\end{figure}

\subsection{Trajectory Simplification}
In order to reveal significant ligand motion patterns, we introduce a hierarchical simplification model that, in addition, allows us to emphasize several important aspects related to the mutual protein-ligand interaction. These aspects are represented by i) the main direction of the ligand motion, ii) the sections of the simulation where the ligand got stuck and iii) the geometrical and physico-chemical properties on sites where the ligand got stuck. 

As already mentioned, the main source of the visual clutter (Fig. \ref{fig:temporal}a) is the ligand motion itself, which resembles the random Brownian motion. Here, the removal of this jittery motion would allow us to reveal more dominant ligand motion patterns. Nevertheless, this also means to approximate the initial trajectory, which on the other hand is a trade-off for providing a good overview of entire ligand motion instead.
As a standard solution, to reduce this jittering and also to simplify the trajectory, the Hermite (or similar) interpolation technique can be used. However, such an interpolation simplification would still not suffice since the spatial distance between two neighboring time steps is usually very small, thus the interpolation scheme still contains a lot of jitter. {\color{red}(TODO mame obrazok?)}
{\color{red} TODO so which  interpolation is the best?JP: Nemusime ak ukazeme nejaku interpolation scheme a tiez ukazeme ze vieme lepsie}

Except for a lot of jitter, the trajectory often contains sequences that form the so-called \textit{loops}.
The loop is thought of as a portion of the trajectory in which the ligand got stuck in a given position $p$ (time step $t_i$), then follows an alternative route; i.e., not heading towards the active site, and finally returns to a position $q$ lying close to $p$ where it got stuck (in time step $t_j$). We define this condition as follows:
\begin{equation}
|p,q| < d,
\label{eq:loop}
\end{equation}
where $d$ is a given distance threshold defining the similarity between two ligand positions (experimentally set to {\color{red}TODO}), and $t_i \neq t_j$, $i << j$. 

To explore the aforementioned patterns of the original trajectory, we proposed two interexchangeable simplification methods, which the user can interactively switch between. Both methods sub-sample the original trajectory and aggregate the protein-ligand interaction in a distinct manner. 

\subsubsection{Simplification Avoiding Loops}
%When exploring the ligand path in more details the biochemist are interested mostly in the parts where the ligand get suck for some reason.
Here we employ the position of active site that can be either user defined or obtained directly from the simulation; e.g., as the final position of the ligand.
%{\color{red}(The automatic active site detection is currently supported only for input data in which the ligand is in the active site by the end of the simulation.)}.
% I guess it could be done for reentry simulation as well using the most distant place from entery point. But here we face the problem how to evalueate whether the ligand go stuck and lefet before actually reaching the active site (ever).  
Thus, in each time step $i$ the distance $d_i$ from the active site to the ligand center of mass can be evaluated; i.e., we define a set $D=\{d_1,d_2, \ldots, d_n\}$. By means of this distance, one can easily detect time steps when the ligand changes its motion with respect to the active site; i.e., towards to or away from the active site. Using $d$ notation we represent these time steps as follows:
\begin{equation}
T_B=\{t_i:\Delta d_i\cdot \Delta d_{i+1} <0\}. 
\label{eq:zc}
\end{equation}
When referring to each entry of $T_B$ as a zero-crossing, we aggregate the user-defined amount $k$ of zero-crossings to form a temporal block $T_{B_j}$ such that $|T_{B_j}|=k$; i.e., when $k=2$ and $|T_B|=20$ we acquire $10$ temporal blocks. For the given parameter $k$, let us denote first time step of these temporal block as $S_k(j)=\{t_{j_1}:T_{B_j}=\{t_{j_1},\ldots\}\}$. In this manner, we extract a set of time steps $S_k=\{S_k(1),\ldots ,S_k(m)\}$ representing $m$ temporal blocks of a trajectory simplification that reflects $k$ parameter. It is important to mention that the corresponding temporal tunnel is formed by means of ligand positions in $S_k$ solely. 
%For instance, on the top-most level, the temporal tunnel contains no loops neither.
%The multi-scale model of the temporal tunnel is then built where on the highest level all loops are omitted.
%In other words, the top-level temporal tunnel contains only the time steps when the ligand headed towards the active site.
%The intermediate levels start to contain a certain number of loops with respect to the following rule.

Each block represents an aggregated unit for which the ligand has to make a given number of loops (each loop is defined by two zero-crossings) before a new block is created. Note that the last block could potentially contain a less number of zero-crossings.
As a consequence, if the ligand moves constantly in the same directions, it takes more time steps to accumulate before $k$ number of zero-crossings is reached. Therefore, the number of time steps in each block reveals either the parts of trajectory where the ligand was moving mostly in a single direction or the sections where it was osculating and thus is unable to move on. Nevertheless, this information needs to be combined with the overall distance the ligand crossed within the block to avoid misinterpretation of the longer loops. Additionally, the user has the possibility to alter parameter $k$ to adjust the granularity of block decomposition. Figure~\ref{fig:todo} demonstrates different results for altering the $k$ value.
%Even though this multi-scale model enables to switch between individual levels by increasing (or decreasing) the number of loops in cluster by one, we suggest that the current value should be multiplied (or divided) by a natural number. 
%This way clusters will be merged or divided uniformly, e.g, if the current number of loops in cluster is multiplied by two the two adjacent cluster will be merge into the single one and vice versa.

\subsubsection{Simplification Using Uniform Sampling}
Here, we uniformly divide the whole simulation into the given number of time intervals, temporal blocks. Each temporal block is of a fixed length given by the user-defined granularity of time represented by the size of the temporal span.
In this case, we define $T_i$ as $|T_i|=n$, where $n$ represents the given number of time steps per temporal block. The value represented in this aggregate is the number of zero-crossings in this time interval.
Such a model can help to evaluate to which extent the ligand was stuck for a given amount of time.
The advantage of this approach is its uniformity that allows easily transfer from one level to another.

\subsubsection{Simplification Based on Surrounding Amino Acids}
The biochemical and geometrical aspects along the ligand path plays an important role during its exploration. 
Note that both these properties are defined by surrounding amino acids. 
Therefore we utilize this information and aggregate all the ligand positions into a single temporal block if they have similar surroundings regarding the amino acids properties. Naturally, this property cannot be kept as an exact number, therefore, the number of allowed differences in surrounding amino acids directly corresponds to the selected levels in our hierarchical model. 
{\color{red} Note that these levels are limited to three since for each time step we compute only three closes amino acids.}.

At lowest level (when no amino acids can be changed in single cluster) the model aggregate only the smallest loops in the same area. 
While all the loops (longer or smaller) on border between two places with different amino acids and hence different properties are preserved.  
This applies also for higher levels, however, the change there would have to be more significant.

Such model also allows to evaluate how long the ligand was stuck in surroundings of some particular amino acids. 
Which provides useful hints when detecting which amino acids along the ligand trajectory caused problems and should be possibly replaced.

{\color{red} TODO: reason about / and implement the time flow independence}

\subsection{Trajectory Visualization} \label{visualization}
The trajectory is visualized in two manners which are interactively linked together.
First is the abstracted visualization shown in Figure~\ref{fig:overview} b) where the visualization of the temporal tunnel and its surroundings is divided into three parts. TODO

The second type of visualization shows the trajectory as a tube in 3D. TODO

%\subsection{Jan's part, will probably not fit to the current version at all.}
%General outline of the section:
% - detection of the ligand entering tunnel
%   - sphere, problems
%	  - surface, computed using LSMS 
% - results in overview
%	  - enables select the appropriate time range
% - once the range is selected the aggregation is done
%   - why aggregation
%	 - how it is done
%      - two or three methods - all?
%   - bar char + 3D line as the results
% - what can be important with respect why the tunnel get stuck
%   - geometrical properties = radius chart
%	    - how we compute radius
%	 - biochemical properties = AA chart
%		  - how we compute surrounding AA





%\textbf{Fourth:} ... based on threshold for maximum backtracking of the ligand on its path. This is not good approach since I don't even know how to justify it with respect to previous three.

\subsection{Visualization}

{\color{red} Just some random sentences I come up with but then in the end did not fit in:}

In order to communicate all the information obtained from previous models to the user we proposed a visualization as shown in Figure \ref{fig:overview}.

Each cluster is here represented by a single bar where its height corresponds to the amount at which the ligand was stuck.

Each cluster is represented by the last time step it contains.
This helps to revel the conditions such as tunnel radius which enabled to the ligand proceed further towards the active site.


%-------------------------------------------------------------------------
\section{Results}
The results will be demonstrated on one or two case studies.

%-------------------------------------------------------------------------
\section{Discussion} \label{discussion}
Here will be the summary of feedback from biochemists.

%-------------------------------------------------------------------------
\section{Conclusion and Future Work}


%-------------------------------------------------------------------------

%\bibliographystyle{eg-alpha}
\bibliographystyle{eg-alpha-doi}

\bibliography{refs}

\end{document}
