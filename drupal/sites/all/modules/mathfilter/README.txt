Module written by David Wees
Credits to: Walter Zorn (for the Javascript graphing), John Forkosh (for the equation rendering)
Lambert Strether (Documentation)
Upgraded to be Drupal 5.0 compatible on 28/01/07

This module includes two filters, each of which allows additional mathematical equations and graphs to be included in your posts.  You can post mathematical equations between [tex] and [/tex] tags, and function graphs between [graph] and [/graph] tags.

However, read INSTALL.txt for more information about both of these capabilities.

You will need to add this filter to one of your existing filter types, or create a new filter type for Mathematical equations.  Note that this will not work with the filter_html filter as the html created by this module will be removed by the filter_html.

Note that the TeX filter uses the mimetex engine, stored where the server can find it (for example, in cgi-bin). However, the graph filter uses
Walter Zorn’s JavaScript graph library, stored in mathfilter/js. So, if the module is properly configured for [tex], it may not be for [graph], and
vice versa.

If you want to make sure that the mimetex engine is being called from inside Drupal try something like this:
<img src="cgi-bin/mimetex.cgi?f(x)=\int_{-\infty}^xe^{-t^2}dt" />

But make sure that the paths in admin/settings/mathbuilder are configured for whatever works in this test.

I put anything with square bracket tags (mathfilter, mapbuilder) highest on the filter list (like -10). And I put linebreak and smarkypants lowest
(like 10). Then HTML goes in the middle. That strategy seems to work OK, since the square bracket tags should be converted to HTML before any other 
HTML is generated.