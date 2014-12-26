/*-- SetLayerTransform aus RdW --*/

#strict 2

global func SetLayerTransform(iLayer,iR,iXCon,iYCon,iXPos,iYPos,pTarget)
{  
  SetObjDrawTransform(iXCon*10, 0, 1000*iXPos,
                      0, iYCon*10, 1000*iYPos,
                      pTarget, iLayer);
  return 1;
}