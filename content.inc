% ---------------------------------------------------------------------
% EG author guidelines plus sample file for EG publication using LaTeX2e input
% D.Fellner, v1.17, Sep 23, 2010


\title[Interactive Exploration of Ligand Movements through Multiscale Temporal Tunnels]%
      {Interactive Exploration of Ligand Movements through Multiscale Temporal Tunnels}

% for anonymous conference submission please enter your SUBMISSION ID
% instead of the author's name (and leave the affiliation blank) !!
\author[Furmanov\'{a} et al.]
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

Here, we introduce {\color{red}two} dedicated methods for simplification of the original trajectory.
These methods can simplify the ligand path hierarchically, thus providing several levels of detail (LOD), which can be interactively browsed through.
In the most abstracted view, represented as the top-most LOD, the temporal tunnel shows only the significant shifts of the ligand towards the active site. 
Here, the user can interactively brush time intervals, which automatically reveals and adopts the temporal tunnel to the selected interval.
This abstracted representation, providing the brushing capabilities, is interactively linked with the 3D visualization where the 3D shape of the temporal tunnel for the given temporal window is displayed.
Further, our tool enables to explore the amino acids surrounding the ligand along its path to the active site as well.

Our proposed solution was thoroughly tested and evaluated by the domain experts from protein engineering.
They performed the evaluation on their own simulations and their feedback is described in Section~\ref{discussion}.

%-------------------------------------------------------------------------

\section{Related Work}
Interactive exploration of ligand paths through protein structures is a complex problem that requires elaborate analysis of existing and convenient approaches.
%In this section we present the results we consider to be relevant to our proposed solution. 
As our system addresses several areas, this section will be divided with respect to these areas as well. 
Studying the ligand transport path is tightly related to the analysis of its trajectory.
Thus, the first part will cover the topic related to the trajectory analysis, simplification, and visualization.
Then the existing representations of tunnels and their surrounding amino acids will be mentioned.

\subsection{Trajectory Analysis, Simplification, and Visualization}
When searching for the most appropriate trajectory simplification method, the taxonomy of different movement patterns introduced by Dodge et al.~\cite{Dodge2008} can help to categorize the type of motion of a given data and to propose an appropriate solution for the analysis and simplification.
Then, Andrienko et al.~\cite{andrienko2013} describe a legacy of tools and approaches to analyze the trajectory data.
With respect to the trajectory simplification, they introduce two approaches to data abstraction representing a necessary step to achieve the reduction of the data in order to achieve informative visualizations.
The first approach is characterized by omitting unnecessary positions and segments, while the second exploits data subsampling.
On the other hand, they state that there is no general method to sample trajectories.
Thus the suitability of particular sampling method is deduced from what information is considered important.
A recent work of Vrotsou et. al.~\cite{Vrotsou2015} introduce a systematic stepwise methodology for trajectory simplification with emphasis on visual analysis.
Even though they primarily developed the tool to analyze three dimensional trajectories, it is not limited to them only.

In the field of molecular biology as well as systems biology, there are several examples of methods focusing on the trajectory analysis.
Bidmon et al.~\cite{bidmon2008} present an abstract way of identification and visualization of solvent molecules' pathways within molecular dynamics. 
In comparison to previous solutions, their approach preserves valuable information on the directions and velocities of water molecules routing along these paths. 
Another approach that describes a guidance through a complex simulation trajectories in systems biology is presented by Luboschik et al.~\cite{Luboschik2012}. 
The method addresses biochemical reaction networks and aims to provide the users with a tool for investigating the overall behavior of a modeled system and detailed behavior at the same time.

\subsection{Visualization of Cavity and Tunnel Features}
Phillips et al.~\cite{phillips2010} propose a method to quantitatively estimate the molecular features; e.g., volume and surface areas, via ray-casting technique. This involves computation of cavities.
Lindow et al.~\cite{LindowBH11} introduce a technique that allows to extract significant paths from the molecules. 
In their approach the authors utilize Voronoi diagram of spheres. 
Their final visualization is achieved by means of placing light sources on the extracted paths to enhance the presence of tunnels.
Parulek et al.~\cite{parulek2012} exploit scatterplots to communicate the evolution of protein voids. 
In their later study~\cite{parulek2013} they also suggest to utilize amino acids physico-chemical properties related to cavities to help users to navigate through their occurrences. 
The visualization if then achieved in the focus and context manner.
Lindow et al. \cite{Lindow2013} present an approach for visualization of temporal evolution of cavities in a temporal graph, which, to a certain extent, resembles our temporal tunnel model. 
In this work they focus on the interactive exploration of the dynamics of protein cavities that can form the transportation path for a ligand. 
They calculate and visualize the cavity volume and analyze the time-dependent changes of the cavity structure.
The cavity dynamics is captured by rendering the cavities in a single image. 
The final visualization is achieved through the molecular surface representation colored according to time. 
Krone et al.~\cite{krone2013features} present a similar approach, where they extract and track tunnels in MD simulations. They exploit temporal graphs to communicate the evolution of surface areas of tunnels. In our technique, we go one step further, where in addition, we incorporate the ligand-protein interaction information and provide users with the means to navigate through details of this interaction. Moreover, we analyze sequences of several thousands of frames, which is not the case in aforementioned approaches.
Kozlikova et al.~\cite{kozlikova2014vcbm} propose a way to seamlessly visualize the geometry and shape of tunnels across MD simulation. Here, they aim at 3D visualization solely, which is not suitable way of exploring and understanding of thousands of simulation time-steps.
Byska et al.~\cite{byska2016} introduce an approach to interactively explore the tunnel objects in MD simulations. Similarly to our approach they visualize the time-varying tunnel as a profile graph that includes information on surrounding amino acids. Nevertheless, they focus on a single tunnel instance and do not provide the means to explore the ligand-protein interaction.

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
\end{figure*}

Even though the detected parts are usually much shorter in comparison with the length of the original simulation, it is still nearly impossible to comprehend the ligand movement. 
This is caused by ligand jittering which makes the perception of the significant ligand movements very hard to follow.
This is clearly visible in Figure~\ref{fig:temporal} a)) which shows the whole ligand trajectory in case when the ligand entered the solvent excluded surface and entered the active site.
The same holds true for cases when the user is watching the animated motion of the ligand. 
Hence we suggest the solution based on a multi-scale simplification model which introduces the concept of so called \textit{temporal tunnel}.  

\subsection{Temporal Tunnel}
The bottom part of our visualization consists of three tightly related sections (detailed description in Section~\ref{visualization}) showing the properties of so called temporal tunnel. 
We define the temporal tunnel as a set of spheres positioned on the centerline representing the trajectory of ligand. 
The centers of these spheres correspond to points computed in the following way.
In each ligand position we find the $N$ closest atoms to the ligand ($N$ was experimentally set to $10$).
Then we compute the center of mass of these closest atoms which forms the center of the corresponding sphere of the temporal tunnel.
The diameter of the spheres is then computed as the maximal empty space around the computed center point. 
This approach was selected because it covers the void space around the ligand sufficiently.

The main contribution of the temporal tunnel is to give the user the information about the geometric bottlenecks (narrowest parts) along the ligand trajectory.
Note that applying the temporal tunnel to the original data provides us only with an approximation of the exact trajectory (Fig. \ref{fig:temporal}).
Still when the ligand trajectory is simplified using one of the methods described below, it gives the user an important overview of the bottlenecks that can be subsequently explored in more detail.

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/temporal.png}
  \caption{\label{fig:temporal} Left: selected part of the whole trajectory when the ligand enters the active site. Right: visualization of the corresponding temporal tunnel. TODO change images!}
\end{figure}

\subsection{Trajectory Simplification}
In order to reveal significant ligand motion patterns, we introduce a hierarchical simplification model that, in addition, allows us to emphasize several important aspects related to the mutual protein-ligand interaction.
These aspects are represented by i) the main direction of the ligand motion, ii) the sections of the simulation where the ligand got stuck and iii) the geometrical and physico-chemical properties on sites where the ligand got stuck. 

As already mentioned, the main source of the visual clutter (Fig. \ref{fig:temporal}a) is the ligand motion itself, which resembles the random Brownian motion. Here, the removal of this jittery motion would allow us to reveal more dominant ligand motion patterns. 
Nevertheless, this also means to approximate the initial trajectory, which on the other hand is a trade-off for providing a good overview of entire ligand motion instead.
As a standard solution, to reduce this jittering and also to simplify the trajectory, the Hermite (or similar) interpolation technique can be used. 
However, such an interpolation simplification would still not suffice since the spatial distance between two neighboring time steps is usually very small, thus the interpolation scheme still contains a lot of jitter. 
Another interpolation scheme we tested for ligand trajectory simplification was the Ramer~-~Douglas~-~Peucker algorithm.
It reduces the number of points in a curve by starting from the line segment between the first and last point of the trajectory. 
For each segment it adds a point from the original trajectory which is the furthest one from this segment.
This process is repeated until the desired resolution of the trajectory is reached.
In case of ligand trajectory, this method keeps only the extreme points on the trajectory which has no significant meaning from the biochemical point of view.
Therefore we come with other solutions designed specifically for the ligand trajectory simplification.{\color{red}(TODO mame obrazok?)}
{\color{red} TODO so which  interpolation is the best?JP: Nemusime ak ukazeme nejaku interpolation scheme a tiez ukazeme ze vieme lepsie}

%Except for a lot of jitter, the trajectory often contains sequences that form the so-called \textit{loops}.
%The loop is thought of as a portion of the trajectory in which the ligand got stuck in a given position $p$ (time step $t_i$), then follows an alternative route, i.e., not heading towards the active site, and finally returns to a position $q$ lying close to $p$ where it got stuck (in time step $t_j$). We define this condition as follows:
%\begin{equation}
%|p,q| < d,
%\label{eq:loop}
%\end{equation}
%where $d$ is a given distance threshold defining the similarity between two ligand positions (experimentally set to {\color{red}TODO}), and $t_i \neq t_j$, $i << j$. 

%\subsubsection{Simplification of the path}

To explore the aforementioned patterns of the original trajectory, we proposed {\color{red}two} interchangeable simplification methods, which the user can interactively switch between. 
{\color{red}Both} methods sub-sample the original trajectory and aggregate the protein-ligand interaction in a distinct manner. 


\subsubsection{Simplification Based on Zero-Crossings}
Here we employ the position of the active site that can be either user defined or obtained directly from the simulation, e.g., as the final position of the ligand.
%{\color{red}(The automatic active site detection is currently supported only for input data in which the ligand is in the active site by the end of the simulation.)}.
% I guess it could be done for reentry simulation as well using the most distant place from entery point. But here we face the problem how to evalueate whether the ligand go stuck and lefet before actually reaching the active site (ever).  
Thus, in each time step $i$ the distance $d_i$ from the active site to the ligand center of mass can be evaluated, i.e., we define a set $D=\{d_1,d_2, \ldots, d_n\}$ where $n$ is the number of time steps in the scrutinized part of the simulation. 
%We define ligand trajectory as a set $T = {t_i : 0 < i <=n}$ 
By means of this distance, one can easily detect time steps when the ligand changes its motion with respect to the active site, i.e., towards to or away from the active site. Using $d$ notation we represent these time steps as follows:
\begin{equation}
T_B=\{t_i:\Delta d_i\cdot \Delta d_{i+1} <0\}. 
\label{eq:zc}
\end{equation}
The method operates with the concept of zero-crossing by which we mean the situation when the ligand changes its direction.
It means that, e.g., the ligand heading towards the active site changed its direction and traveled back to the outer solvent.
With another zero-crossing the ligand starts to approach the active site again.
So one pair of zero-crossings defines a so-called \textit{loop}.
These loops emerge when the ligand got stuck.
When two zero-crossings forming the loop are located in two time steps which are more distant with respect to time, it means that the ligand got stuck for the time portion between these time steps.
When referring to each entry of $T_B$ as a zero-crossing, we aggregate the user-defined amount $k$ of zero-crossings to form a temporal block $T_{B_j}$ such that $|T_{B_j}|=k$, i.e., when $k=2$ and $|T_B|=20$ we acquire $10$ temporal blocks. 

For the given parameter $k$, we denote the last time step of this temporal block as $E_k(j)=\{t_{j_k}:T_{B_j}=\{t_{j_1},\ldots,t_{j_k}\}\}$. 
In this manner, we extract a set of time steps $E_k=\{E_k(1),\ldots ,E_k(m)\}$ representing $m$ temporal blocks of a trajectory simplification that reflects the $k$~parameter. 
It is important to mention that the corresponding temporal tunnel is formed by ligand positions in $E_k$ solely. 

%Now, for a given 

%For instance, on the top-most level, the temporal tunnel contains no loops neither.
%The multi-scale model of the temporal tunnel is then built where on the highest level all loops are omitted.
%In other words, the top-level temporal tunnel contains only the time steps when the ligand headed towards the active site.
%The intermediate levels start to contain a certain number of loops with respect to the following rule.

Each block $T_{B_j}$ represents an aggregated unit for which the ligand has to make a given number of loops before a new block is created. 
Note that the last block could potentially contain a smaller number of zero-crossings.
As a consequence, if the ligand moves constantly in the same direction, it takes more time steps to accumulate before $k$ number of zero-crossings is reached. Therefore, the number of time steps in each block reveals either the parts of trajectory where the ligand was moving mostly in a single direction or the sections where it got stuck and thus was unable continue towards the active site. 
Nevertheless, this information needs to be combined with the overall distance the ligand crossed within the block to avoid the misinterpretation of longer loops. Additionally, the user has the possibility to alter parameter $k$ to adjust the granularity of block decomposition. 
Figure~\ref{fig:loops} demonstrates different results for altering the $k$ value.
%Even though this multi-scale model enables to switch between individual levels by increasing (or decreasing) the number of loops in cluster by one, we suggest that the current value should be multiplied (or divided) by a natural number. 
%This way clusters will be merged or divided uniformly, e.g, if the current number of loops in cluster is multiplied by two the two adjacent cluster will be merge into the single one and vice versa.

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/zero_degradation.pdf}
  \caption{\label{fig:loops} Example of resulting trajectories for different values of the parameter $k$ which influences the granularity of block decomposition.}
\end{figure}

This type of trajectory simplification is beneficial mainly because it prevents the main bottlenecks of the temporal tunnel which are the most interesting and important sites of the simulation.
These sites where the ligand got stuck for a significant portion of time correspond to parts of the trajectory which is worthwhile to explore in more detail and find out the reason why the ligand was not able to pass through the tunnel. 

\subsubsection{Simplification Using Uniform Sampling}
Here, we uniformly divide the whole simulation into a given number of time intervals, i.e, temporal blocks. 
Each temporal block is of a fixed length given by the user-defined granularity of time represented by the size of the temporal span.
In this case, we define $T_i$ as $|T_i|=l$, where $l$ represents the given number of time steps per temporal block. 
The value represented in this aggregate is the number of zero-crossings in this time interval. This can be seen as an orthogonal simplification strategy to the aforementioned one.

Such a model can help to evaluate to which extent the ligand was stuck for a given amount of time.
The advantage of this approach is its uniformity that allows easily transfer from one level to another.
Moreover, this concept is commonly used by the biochemists in cases when they have to deal with large amount of data or information, such as in computation of protein cavities and tunnels.
Here the user selects a sampling step and only in these regularly selected steps the cavities are computed. 
This gives the user the rough idea of the presence of cavities within the whole simulation.

Nevertheless, the given granularity can cause that important time steps with respect to the ligand motion will be skipped \textcolor[rgb]{1,0,0}{(TODO figure and explanation!!!!)}. 

Figure~\ref{fig:uniform} shows an example of uniform simplification results on different levels. 

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/uniform_degradation.pdf}
  \caption{\label{fig:uniform} Example of uniformly sampled trajectories for different values of the parameter $l$ which influences the granularity of block decomposition (number of samples in each level).}
\end{figure}


\subsubsection{Simplification Based on Surrounding Amino Acids}
%{\color{red}TODO BK leave it here?}
The geometric properties of the temporal tunnel are very important mainly because of the presence of geometric bottlenecks.
However, the physico-chemical properties of the amino acids surrounding the ligand trajectory are similarly important.
When the properties of the ligand and the amino acids are not compatible, it can prevent the ligand to pass through such site even when the tunnel is wide enough. 
Therefore we utilize this information and aggregate all the ligand positions into a single temporal block when they are surrounded by given amino acids
On the lowest level of our hierarchical model, we aggregate the ligand positions where the ligand was surrounded by the same set of amino acids (the set can be defined, e.g., as the three closest amino acids or amino acids in a given distance).
The other levels allow some changes in properties of the surroundings, i.e., the number of allowed differences in the surrounding amino acids directly corresponds to the selected levels. 
%{\color{red} Note that these levels are limited to three since for each time step we compute only three closest amino acids.}.
Figure~\ref{fig:aa} shows examples of the resulting trajectories on different levels simplified by this method.

%As a result, on the lowest level the model aggregates only the smallest loops located in the same area. 
%While all the loops (longer or shorter) on the border between two ligand positions surrounded by different amino acids and hence different properties are preserved.  
%This applies also for higher levels, however, the change there would have to be more significant.

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/residue_degradation.pdf}
  \caption{\label{fig:aa} Example of trajectories sampled using the surrounding amino acids.}
\end{figure}

Such model allows to evaluate how long the ligand was stuck with respect to the surroundings consisting of a particular set of amino acids. 
It can provide the users with the suggestion of amino acids along the ligand trajectory which caused the problems and should be possibly replaced (mutated).


\subsubsection{Simplification Based on Loop Degradation}
This method is based on a user-defined variable $X$ that divides the selected part of ligand trajectory into consecutive temporal blocks.
We define the whole ligand trajectory as a set of time steps $T = \{t_i : 0 < i \leq n\}$ where $n$ is the length of the selected part.
Let $B_{r,s}$ be particular temporal block of the trajectory and $(t_r, t_s)$ its boundary points.
The Euclidean distance of the boundary points of each block is at least $X$.
The whole block is then defined as $B_{r,s} = \{t_j : r \leq j \leq s \land |t_r, t_j| < X \}$.
The information about the length of the trajectory in every block is stored and utilized in the visualization.
The maximum value of $X$ corresponds to the Euclidean distance between $t_1$ and $t_n$. 

Figure~\ref{fig:ld} shows the results for several different values of $X$.

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/loop_degradation.pdf}
  \caption{\label{fig:ld} Example of trajectory simplification using the loop degradation approach.  }
\end{figure}

The reasoning behind this method is based on the idea of removing those parts of the trajectory where the ligand moved only slightly and "shaked" around in a small area (within a sphere of radius $X$). 
So the method is able to show only the dominant ligand motions.
%{\color{red} TODO: add few sentences about what should be accomplished by this method.}




















\subsection{Temporal Tunnel Compound Views} \label{visualization}
Each simplification scheme provides a detailed information aggregated within the acquired temporal blocks, which asks for a meaningful visual representation. Therefore, we propose a compound visualization system (Fig.~\ref{fig:overview}b) composed of dedicated charts representing information provided by the corresponding temporal tunnel. 
This information should assist users to quickly explore interesting sites on the ligand trajectory.
Our compound view is divided into three parts.

The top part shows the bar chart that captures the aggregated information about individual blocks obtained via the user-selected simplification method.
Each temporal block is represented by a single bar and its height corresponds to the actual aggregated value; i.e., either the number of zero-crossings or the number of time steps. 
Additionally, the user can choose between two ligand-distance related values. 
First, the total distance the ligand passed through between each neighboring time steps of the temporal block. 
Secondly, a relative distance the ligand passed between the first and the last time step of the temporal block.  \textcolor[rgb]{1,0,0}{(TODO Figure to compare both)}

The basic coloring scheme of the individual bars encodes the direction of the ligand in the corresponding temporal blocks (Fig.~\ref{fig:bars}). 
Here, yellow color represents the direction towards the active site, while red color means that the ligand moved in the opposite direction.
{\color{red}TODO what else?}

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/bars.png}
  \caption{\label{fig:bars} Coloring scheme used for individual bars which encodes the direction of the ligand with respect to the active site position. Yellow color corresponds to the motion towards the active site, red color corresponds to the opposite direction.}
\end{figure}

The middle part gives the user the context of the width of the temporal tunnel in a given temporal block.
The width corresponds to the diameter of the sphere enclosing the empty space around the ligand that is taken from the last time step of a given block. Here, the motivation being that ligand leaves the block in the last time step and enters the subsequent one. 
In combination with the information obtained from the bar representation, the user can easily reveal if the bottlenecks detected from the ligand motion correspond to the geometric bottlenecks of the temporal tunnel.
In other words, such a combination provides the users with the possibility to explore the correspondence between the geometrical bottlenecks and parts the ligand got stuck.
These parts form another type of bottlenecks -- those defined by the physico-chemical properties of the surrounding amino acids. 
In general, the geometric and phys-chem bottlenecks are considered as equal. 
Nevertheless, a case that the tunnel is relatively wide enough and yet the ligand gets stuck reflects the situation when the properties of the ligand are not compatible with the properties of the amino acids interacting with the ligand.

To explore both types of bottlenecks and their corresponding amino acids in more detail, we propose the third part of the proposed visualization (Fig.~\ref{fig:aacids}).
Here, we provide visual representation containing the list of all amino acids surrounding the temporal tunnel.
Each amino acid defines one line in the list. 
The line is colored with respect to a selected physico-chemical property~---~our representation supports switching between hydrophobicity, partial charges, and donors and acceptors.
The interruption in some of these lines is caused by the fact that the given amino acid is not present around the ligand in the corresponding temporal block.

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/aacids.png}
  \caption{\label{fig:aacids} Representation of amino acids surrounding the temporal tunnel and their physico-chemical properties. Coloring corresponds to a selected property, the line interruption means that this amino acid was not detected around the ligand in the corresponding temporal block.{\color{red}TODO change image!!!}}
\end{figure}

The proposed abstracted visualization is interactively linked with the 3D view where the temporal tunnel is represented in the following way.

TODO
------------------------------

\textcolor[rgb]{0.65,0.16,0}{TODO where are all the figures - For each scheme we need 1) different granurality, selections, comparissons, infographs, 3D trajectories, tunnels?}




%-------------------------------------------------------------------------
\section{Results and Discussion} \label{discussion}
The proposed techniques were tested on several ligand trajectories with different scenarios -- ligand travelled from the outer solvent to the active site, ligand left the active site as well as the molecule, or ligand entered the active site, then left and reentered the site again.
The length of the tested trajectories spanned from $50.000$ to $100.000$ time steps.
Here we describe the integration of our approach to the traditional workflow of biochemists and the contribution of this new approach.
When exploring the molecular dynamics simulation capturing the ligand motion, the biochemists currently observe the ligand animation using some of the widely used molecular visualization tools.
Additionally, they often plot line charts showing different properties, such as geometric bottlenecks along the ligand path. 
The exploration process is iterative so the users are manually selecting interesting parts of the trajectory according to the information extracted from the plotted graphs. 
These parts are then again plotted.
This process is repeated and under the best of conditions it helps to reveal the interesting amino acids around the bottlenecks of the trajectory.
These amino acids are then the best candidates for protein mutations serving for a given purpose, e.g., removing the bottleneck or closing this path completely. 
This process is usually very lengthy and requires a lot of effort from the user.

Our proposed tool removes the main limitations of the traditional approach.
The overview visualization helps the biochemists to immediately distinguish between individual parts of the trajectory -- when ligand was inside and travelled from or towards the active site, or it was outside the molecule. 
By selecting the part of interest in the overview visualization, the user is automatically navigated to the corresponding time sequence.

In order to show the process of exploration of the selected part in more detail, we will describe one case performed on the real data obtained from the biochemists.
It demonstrates how the biochemists can interact with the tool and how it helps them to understand the ligand trajectory much faster and in more comprehensible way than before.

The scrutinized trajectory first captures the ligand movement outside the protein and then its transportation to the active site.
The overview visualization automatically distinguishes between these two states and divides the trajectory to two parts (see Figure~ref{fig:case}).

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/aacids.png}
  \caption{\label{fig:case} TODO!!!!}
\end{figure}

The user can select the part of the trajectory when the ligand entered the molecule and aimed to get to the active site.
As the original trajectory is very scattered (see Figure~\ref{fig:cross} a)), the user can use one of the simplification methods to see the significant motions of the ligand.
When using the simplification based on zero-crossings, the user should be able to distinguish between parts where the ligand got stuck and parts where its progress towards the active site was substantial (see Figure~\ref{fig:cross} b)).

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/cross.png}
  \caption{\label{fig:cross} TODO!!!!}
\end{figure}

This information is easily readable from the bar chart accumulating the information about the ligand progress (see~Figure\ref{fig:casebar} top).
The highest bar shows the part of the trajectory when the ligand did not change its direction.
The yellow color additionally says that the ligand travelled towards the active site. 
This bar further divides the trajectory to three parts which can be further explored by interactive selection of their corresponding bars (see~Figure\ref{fig:casebar} bottom).

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/casebar.png}
  \caption{\label{fig:cross} TODO!!!!}
\end{figure}

Then the user can focus on details of this part of the trajectory by decreasing the level of simplification until reaches the lowest level where all original time steps of this part are displayed.
At this level we can easily detect the bottleneck from the visualization part showing the radii of empty sphere around in each ligand position (see~Figure\ref{fig:radius}.
The bottom part of the visualization shows the amino acids in the closest neighborhood for each ligand position.
So the user can easily reveal the amino acids forming the bottleneck and by selecting them, they are automatically highlighted in the 3D visualization.

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/radius.png}
  \caption{\label{fig:radius} TODO!!!!}
\end{figure}

In all levels, the trajectory in the context of the 3D representation of the molecule can be observed as a tube which gives the user the idea of the spatial orientation of the trajectory with respect to the protein.
When hovering over individual bars, the corresponding part of the tube is highlighted (red section in Figure\ref{fig:tube} a)).
By selecting the amino acids surrounding the trajectory the user can observe the interacting atoms from the ligand and the amino acids (Figure\ref{fig:tube} b)).

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/tube.png}
  \caption{\label{fig:tube} TODO!!!!}
\end{figure}

\section{Conclusion and Future Work}


%-------------------------------------------------------------------------

%\bibliographystyle{eg-alpha}
\bibliographystyle{eg-alpha-doi}

\bibliography{refs}

\end{document}
