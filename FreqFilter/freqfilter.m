function freqfilter()
%prepare a blur and noisy image
pkg load image %load image package if necessary
I=imread('lake.jpg');% read an image
I=rgb2gray(I); % convert to grayscale

% show the original image in grayscale
figure;
imshow(I); 
title('Original');

I=im2double(I); % convert to double type
F=fft2(I); % discrete fourier transform
%show the Fourier spectrum
figure;
imshow(log(abs(fftshift(F))+1),[ ]); 
title('Fourier spectrum');

[ih iw]=size(I);%get size
H=Gaussian(ih,iw,30,0);  %get Gaussian filter 
%H=Butterworth(ih,iw,50,2,0); %get Butterworth filter

%show the filter
figure;
imshow(abs(H),[ ]); 
title('Filter');

%show the mesh grid of the filter
figure;
ih=abs(H);
mesh(ih(1:10:end,1:10:end))
%colormap([0 0 0]);
grid off;
axis off;

G=F.*fftshift(H); %filter in freq domain
g=ifft2(G); % inverse discrete fourier transform

img=abs(g); % get the absolute value
img=imnoise(img,'gaussian',0,0.01); % add gaussian noise
imgn=im2uint8(img); % convert double to grayscale

% show the resulting blurred and noisy image
figure;
imshow(imgn); 
title('After filtering');  

imwrite(imgn,'blur.jpg');% save the image  

end

function H=Gaussian(ih,iw,s,filterType)
    %Gaussian_Filter performs high-pass or low-pass Gaussian filtering
    % ih,iw= height and width, 
    % s= CutOff frequency (standard deviation), 
    % filterType= 0- Low-pass and 1- High-pass
    %produce u and v coordinate
    u1=(0:1:ih-1)-floor(ih/2);
    v1=(0:1:iw-1)-floor(iw/2);
    [V,U]=meshgrid(v1,u1);
    %produce filter for low pass
    H=e.^(-(U.^2+V.^2)./(2*(s^2)));    
    if (filterType==1) %if high-pass
        H=1-H;
    end    
end

function H=Butterworth(ih,iw,Do,n,filterType)
    %Butterworth_Filter performs high-pass or low-pass butterworth filtering
    % ih,iw= height and width,  
    % Do= CutOff frequency, 
    % n= order, 
    % filterType= 0- Low-pass and 1- High-pass    
    %produce u and v coordinate
    % u1=(-floor(ih/2):1:(ceil(ih/2)-1));
    % v1=(-floor(iw/2):1:(ceil(iw/2)-1));
    u1=(0:1:ih-1)-floor(ih/2);
    v1=(0:1:iw-1)-floor(iw/2);
    [V,U]=meshgrid(v1,u1);
    fra=(U.^2+V.^2)./(Do^2); % for low pass
    if (filterType==1) % if high pass
        fra=1./fra;
    end        
    H=1./(1+fra.^n); %get mask
end
