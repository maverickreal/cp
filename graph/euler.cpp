bool dgHasEulerPath(const vi(vi(ll))&g) { // graph must be connected
   ll n=g.size(), u = 0, v = 0;
   vi(ll)in(n), out(n);
   for(ll i=0;i<n;i++) {
      for(ll j:g[i]) {
        ++in[j];
      }
      out[i]=g[i].size();
   }
   if(in==out){ // eulerian circuit found
    return 1;
   }
   for(ll i=0;i<n;i++) {
      if(in[i]==out[i]){
        continue;
      }
      if(in[i]==out[i]-1){
        ++u;
      }
      else if(out[i]==in[i]-1){
        ++v;
      }
   } // perform a postorder on u to trace the path
   return (u==1 && v==1);
}

bool undgHasEulerPath(const vi(vi(ll))&g) { // graph must be connected
   ll oddDeg=0;
   for(ll i=0;i<g.size();i++) {
      oddDeg+=g[i].size()&1;
   } // perform a postorder over either of the odd degree nodes to trace the path
   return (oddDeg==0 || oddDeg==2 /* eulerian circuit found */);
}